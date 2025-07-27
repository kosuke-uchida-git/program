#include "linearRegressionExperiment.h"

LinearRegressionExperiment *
linearRegressionExperiment_construct(Matrix *m, unsigned int seed_,
                                     double trainingDataRate_, double lasso,
                                     double ridge) {
  LinearRegressionExperiment *result =
      malloc(sizeof(LinearRegressionExperiment));
  if (!result) {
    fprintf(stderr, "linearRegressionExperiment_construct: malloc failed\n");
    exit(EXIT_FAILURE);
  }

  result->data = m;
  result->seed = seed_;
  result->trainingDataRate = trainingDataRate_;
  result->lassoRegularizer = lasso;
  result->ridgeRegularizer = ridge;
  result->rmse = -1.0;

  return result;
}

void linearRegressionExperiment_destruct(LinearRegressionExperiment *lre) {
  if (!lre) {
    return;
  }
  free(lre);
}

void linearRegressionExperiment_execute(LinearRegressionExperiment *lre) {
  // Construct
  size_t dataCount = lre->data->row;
  size_t dimensionCount = lre->data->column - 1;
  size_t trainingDataCount = (size_t)(lre->trainingDataRate * dataCount);
  size_t testDataCount = dataCount - trainingDataCount;
  IntArray *trainingDataIndex = intArray_construct();
  IntArray *testDataIndex = intArray_construct();
  Matrix *trainingData =
      matrix_construct(trainingDataCount, dimensionCount + 1);
  Matrix *testData = matrix_construct(testDataCount, dimensionCount + 1);

  // Make trainingDataIndex and testDataIndex
  for (int i = 0; i < dataCount; i++) {
    intArray_add(testDataIndex, i);
  }
  srand(lre->seed);
  intArray_shuffle(testDataIndex);
  for (int i = 0; i < trainingDataCount; i++) {
    intArray_add(trainingDataIndex,
                 testDataIndex->elements[testDataIndex->size - 1]);
    intArray_remove(testDataIndex, testDataIndex->size - 1);
  }

  // Make trainingData
  for (int i = 0; i < trainingDataCount; i++) {
    // Copy the (trainingDataIndex->elements[i])-th row of lre->data to the
    // i-th row of trainingData
    matrix_copyRow(trainingData, lre->data, i, trainingDataIndex->elements[i]);
  }
  Regression *r1 = regression_construct(trainingData);

  // Make testData
  for (int i = 0; i < testDataCount; i++) {
    // Copy the (testDataIndex->elements[i])-th row of lre->data to the i-th
    // row of testData
    matrix_copyRow(testData, lre->data, i, testDataIndex->elements[i]);
  }
  Regression *r2 = regression_construct(testData);

  // Train
  LinearRegression *l = linearRegression_construct(r1, lre->lassoRegularizer,
                                                   lre->ridgeRegularizer);
  linearRegression_optimize(l);

  // Predict
  linearRegression_changeData(l, r2);
  lre->rmse = linearRegression_rmse(l);

  // Destruct
  intArray_destruct(trainingDataIndex);
  intArray_destruct(testDataIndex);
  matrix_destruct(trainingData);
  matrix_destruct(testData);
  regression_destruct(r1);
  regression_destruct(r2);
  linearRegression_destruct(l);
}