#include "linearRegression.h"

LinearRegression *linearRegression_construct(Regression *r, double lasso,
                                             double ridge) {
#ifdef DEBUG
  if (!r) {
    fprintf(stderr, "linearRegression_construct: NULL Regression pointer\n");
    exit(EXIT_FAILURE);
  }
#endif
  LinearRegression *result = malloc(sizeof(LinearRegression));
  if (!result) {
    fprintf(stderr, "linearRegression_construct: malloc failed\n");
    exit(EXIT_FAILURE);
  }
  result->lassoRegularizer = lasso;
  result->ridgeRegularizer = ridge;
  result->bias = 0.0;
  result->coefficient = matrix_construct(1, r->dimension);
  result->intermediate = matrix_construct(r->dataCount, 1);
  result->regression = r;
  return result;
}

void linearRegression_destruct(LinearRegression *l) {
  if (!l) {
    return;
  }
  matrix_destruct(l->coefficient);
  matrix_destruct(l->intermediate);
  free(l);
}

void linearRegression_optimize(LinearRegression *l) {
  int count = 0;
  while (1) {
    count++;
    double tmpBias = l->bias;
    linearRegression_revise(l);
    double difference = fabs(l->bias - tmpBias);
    if (count % 10000 == 0) {
      printf("difference=%.16f\n", difference);
    }
    if (difference < 1.0E-32) {
      break;
    }
  }
}

void linearRegression_revise(LinearRegression *l) {
  linearRegression_reviseIntermediate(l);
  linearRegression_reviseBias(l);
  linearRegression_reviseCoefficient(l);
}

void linearRegression_reviseBias(LinearRegression *l) {
  l->bias = matrix_meanElements(l->intermediate);
}

void linearRegression_reviseCoefficient(LinearRegression *l) {
  // revise coefficient_i (i: dimension index)
  for (size_t i = 0; i < l->regression->dimension; i++) {
    double before = l->coefficient->elements[i];
    double numerator = 0.0, denominator = l->ridgeRegularizer;
    // n: data index
    for (size_t n = 0; n < l->regression->dataCount; n++) {
      double tmp = *matrix_element(l->regression->explanatory, n, i);
      // add numerator
      numerator += tmp * (l->intermediate->elements[n] +
                          l->coefficient->elements[i] * tmp - l->bias);
      // add denominator
      denominator += tmp * tmp;
    }

    // lasso regularization
    if (fabs(numerator) > l->lassoRegularizer) {
      numerator -= l->lassoRegularizer * sign(l->coefficient->elements[i]);
    } else {
      numerator = 0.0;
    }

    l->coefficient->elements[i] =
        before + 3.5 * (numerator / denominator - before);
  }
}

void linearRegression_reviseIntermediate(LinearRegression *l) {
  // l->intermediate = l->regression->objective - (l->regression->explanatory *
  // l->coefficient ^T);

  // m=l->regression->explanatory * l->coefficient ^T
  Matrix *m = matrix_constructFromMatrix(l->regression->explanatory);
  Matrix *transposedCoefficient = matrix_constructFromMatrix(l->coefficient);
  matrix_transposeVector(transposedCoefficient);
  matrix_product(m, transposedCoefficient);
  matrix_destruct(transposedCoefficient);

  // l->intermediate = l->regression->objective
  matrix_copy(l->intermediate, l->regression->objective);
  // l->intermediate = l->regression->objective-m
  matrix_subtract(l->intermediate, m);

  matrix_destruct(m);
}