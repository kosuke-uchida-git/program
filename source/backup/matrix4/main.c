#include "matrix.h"

int main(void) {
  Matrix A, B;

  // 行列 A: 2x3
  constructMatrix(&A, 2, 3);
  *elementMatrix(&A, 0, 0) = 1;
  *elementMatrix(&A, 0, 1) = 2;
  *elementMatrix(&A, 0, 2) = 3;
  *elementMatrix(&A, 1, 0) = 4;
  *elementMatrix(&A, 1, 1) = 5;
  *elementMatrix(&A, 1, 2) = 6;

  // 行列 B: 3x2
  constructMatrix(&B, 3, 2);
  *elementMatrix(&B, 0, 0) = 7;
  *elementMatrix(&B, 0, 1) = 8;
  *elementMatrix(&B, 1, 0) = 9;
  *elementMatrix(&B, 1, 1) = 10;
  *elementMatrix(&B, 2, 0) = 11;
  *elementMatrix(&B, 2, 1) = 12;

  printf("Matrix A:\n");
  printMatrix(&A);
  printf("Matrix B:\n");
  printMatrix(&B);

  // A = A × B（productMatrix は破壊的）
  productMatrix(&A, &B);

  printf("A x B:\n");
  printMatrix(&A);

  transposeMatrix(&B);
  printMatrix(&B);

  destructMatrix(&A);
  destructMatrix(&B);

  return 0;
}
