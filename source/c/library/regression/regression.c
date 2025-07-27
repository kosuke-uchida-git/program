#include "regression.h"

Regression *regression_construct(Matrix *dataset) {
#ifdef DEBUG
  if (!dataset || dataset->column <= 1) {
    fprintf(
        stderr,
        "regression_construct: dataset is NULL or has insufficient columns\n");
    exit(EXIT_FAILURE);
  }
#endif
  Regression *result = malloc(sizeof(Regression));
  if (!result) {
    fprintf(stderr, "regression_construct: malloc failed\n");
    exit(EXIT_FAILURE);
  }
  result->dataCount = dataset->row;
  result->dimension = dataset->column - 1;
  result->explanatory = matrix_construct(result->dataCount, result->dimension);
  result->objective = matrix_construct(result->dataCount, 1);
  for (size_t r = 0; r < result->dataCount; r++) {
    // copy explanatory variable
    memcpy(result->explanatory->elements + r * result->dimension,
           dataset->elements + r * dataset->column,
           result->dimension * sizeof(double));
    // copy objective variable
    *matrix_element(result->objective, r, 0) =
        *matrix_element(dataset, r, result->dimension);
  }
  return result;
}

Regression *regression_constructFromFile(const char *filename) {
#ifdef DEBUG
  if (!filename) {
    fprintf(stderr, "regression_constructFromFile: NULL pointer argument\n");
    exit(EXIT_FAILURE);
  }
#endif
  Matrix *dataset = matrix_constructFromFile(filename);
  Regression *result = regression_construct(dataset);
  matrix_destruct(dataset);
  return result;
}

void regression_destruct(Regression *r) {
  if (!r) {
    return;
  }
  matrix_destruct(r->explanatory);
  matrix_destruct(r->objective);
  free(r);
}