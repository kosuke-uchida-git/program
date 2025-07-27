#ifndef REGRESSION
#define REGRESSION

#include "../matrix/matrix.h"

typedef struct {
  Matrix *explanatory, *objective;
  size_t dataCount, dimension;
} Regression;

Regression *regression_construct(Matrix *dataset);
Regression *regression_constructFromFile(const char *filename);
void regression_destruct(Regression *r);

#endif