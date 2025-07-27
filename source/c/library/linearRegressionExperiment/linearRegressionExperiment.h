#ifndef LINEAR_REGRESSION_EXPERIMENT
#define LINEAR_REGRESSION_EXPERIMENT

#include "../linearRegression/linearRegression.h"

typedef struct {
  Matrix *data;
  unsigned int seed;
  double trainingDataRate, lassoRegularizer, ridgeRegularizer, rmse;
} LinearRegressionExperiment;

LinearRegressionExperiment *
linearRegressionExperiment_construct(Matrix *m, unsigned int seed_,
                                     double trainingDataRate_, double lasso,
                                     double ridge);
void linearRegressionExperiment_destruct(LinearRegressionExperiment *lre);
void linearRegressionExperiment_execute(LinearRegressionExperiment *lre);

#endif