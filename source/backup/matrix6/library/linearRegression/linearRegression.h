#ifndef LINEAR_REGRESSION
#define LINEAR_REGRESSION

#include "../regression/regression.h"

typedef struct {
  double lassoRegularizer, ridgeRegularizer, bias;
  Matrix *coefficient, *intermediate;
  Regression *regression;
} LinearRegression;

LinearRegression *linearRegression_construct(Regression *r, double lasso,
                                             double ridge);
void linearRegression_destruct(LinearRegression *l);

void linearRegression_optimize(LinearRegression *l);
void linearRegression_revise(LinearRegression *l);
void linearRegression_reviseBias(LinearRegression *l);
void linearRegression_reviseCoefficient(LinearRegression *l);
void linearRegression_reviseIntermediate(LinearRegression *l);

#endif