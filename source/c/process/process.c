#include "process.h"

void process() {
  Matrix *m = matrix_constructFromFile("wineQuality/redWine.txt");

  double bestRmse = DBL_MAX;
  double bestLasso = -1.0;
  double bestRidge = -1.0;

  int seed = 1;
  for (double lasso = 0.001; lasso <= 0.01; lasso += 0.001) {
    for (double ridge = 0.01; ridge <= 0.1; ridge += 0.01) {
      LinearRegressionExperiment *lre =
          linearRegressionExperiment_construct(m, seed, 0.1, lasso, ridge);
      linearRegressionExperiment_execute(lre);
      printf("(%f,%f): rmse=%f\n", lasso, ridge, lre->rmse);

      if (lre->rmse < bestRmse) {
        bestRmse = lre->rmse;
        bestLasso = lasso;
        bestRidge = ridge;
      }

      linearRegressionExperiment_destruct(lre);
    }
  }
  printf("rmse=%f\n", bestRmse);
  printf("(lasso, ridge)=(%f,%f)\n", bestLasso, bestRidge);

  matrix_destruct(m);
}
