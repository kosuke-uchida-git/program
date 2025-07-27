#include "matrix.h"

void constructMatrix(Matrix *m, int row_, int column_) {
  m->row = row_;
  m->column = column_;
  m->size = row_ * column_;
  m->elements = (double *)malloc(sizeof(double) * m->size);
  for (int i = 0; i < m->size; i++) {
    m->elements[i] = 0.0;
  }
}

void destructMatrix(Matrix *m) {
  if (m->elements != NULL) {
    free(m->elements);
    m->elements = NULL;
  }
}

void copyMatrix(Matrix *m1, Matrix *m2) {
  if (m1 == m2) {
    return;
  }
  if (m1->size != m2->size) {
    destructMatrix(m1);
    constructMatrix(m1, m2->row, m2->column);
  }
  for (int i = 0; i < m1->size; i++) {
    m1->elements[i] = m2->elements[i];
  }
}

void moveMatrix(Matrix *m1, Matrix *m2) {
  if (m1 == m2) {
    return;
  }

  destructMatrix(m1);
  m1->row = m2->row;
  m1->column = m2->column;
  m1->size = m2->size;
  m1->elements = m2->elements;

  m2->elements = NULL;
}

void printMatrix(Matrix *m) {
  int k = 0;
  printf("(");
  for (int i = 0; i < m->row; i++) {
    for (int j = 0; j < m->column; j++) {
      printf("%f ", m->elements[k++]);
    }
    if (i != m->row - 1) {
      printf("\n");
    }
  }
  printf(")\n");
}

double *elementMatrix(Matrix *m, int row_, int column_) {
  return m->elements + (row_ * m->column + column_);
}

void addMatrix(Matrix *m1, Matrix *m2) {
  for (int i = 0; i < m1->size; i++) {
    m1->elements[i] += m2->elements[i];
  }
}

void subtractMatrix(Matrix *m1, Matrix *m2) {
  for (int i = 0; i < m1->size; i++) {
    m1->elements[i] -= m2->elements[i];
  }
}

void multiplyMatrix(Matrix *m, double d) {
  for (int i = 0; i < m->size; i++) {
    m->elements[i] *= d;
  }
}

void productMatrix(Matrix *m1, Matrix *m2) {
  Matrix result;
  constructMatrix(&result, m1->row, m2->column);

  for (int i = 0; i < m1->row; i++) {
    for (int j = 0; j < m2->column; j++) {
      double sum = 0.0;
      for (int k = 0; k < m1->column; k++) {
        sum += *elementMatrix(m1, i, k) * (*elementMatrix(m2, k, j));
      }
      *elementMatrix(&result, i, j) = sum;
    }
  }
  moveMatrix(m1, &result);
}

void transposeMatrix(Matrix *m) {
  Matrix result;
  constructMatrix(&result, m->column, m->row);
  for (int i = 0; i < m->row; i++) {
    for (int j = 0; j < m->column; j++) {
      *elementMatrix(&result, j, i) = *elementMatrix(m, i, j);
    }
  }
  moveMatrix(m, &result);
}

double l2NormSquareMatrix(Matrix *m) {
  double result = 0.0;
  for (int i = 0; i < m->size; m++) {
    result += m->elements[i] * m->elements[i];
  }
  return result;
}

double l2NormMatrix(Matrix *m) { return sqrt(l2NormSquareMatrix(m)); }

double maxNormMatrix(Matrix *m) {
  double result = 0.0;
  for (int i = 0; i < m->size; i++) {
    if (result < fabs(m->elements[i])) {
      result = fabs(m->elements[i]);
    }
  }
  return result;
}