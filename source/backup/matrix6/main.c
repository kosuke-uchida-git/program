#include "library/library.h"

int main(void) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  //===========================WRITE HERE===========================
  Matrix *m = matrix_constructFromFile("red.txt");
  Regression *r = regression_construct(m);
  LinearRegression *l = linearRegression_construct(r, 0.0, 0.0);

  linearRegression_optimize(l);

  matrix_print(l->coefficient);
  printf("bias=%f\n", l->bias);

  linearRegression_destruct(l);
  regression_destruct(r);
  matrix_destruct(m);
  //================================================================

  clock_gettime(CLOCK_MONOTONIC, &end);
  uint64_t elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 +
                        (end.tv_nsec - start.tv_nsec) / 1000000;

  printf("Execution time: %lu ms\n", elapsed_ms);
  return 0;
}
