#include "matrix.h"

int main(void) {
  Matrix A, B;

  // A: 2x3 行列
  constructMatrix(&A, 2, 3);
  setElementMatrix(&A, 0, 0, 1);
  setElementMatrix(&A, 0, 1, 2);
  setElementMatrix(&A, 0, 2, 3);
  setElementMatrix(&A, 1, 0, 4);
  setElementMatrix(&A, 1, 1, 5);
  setElementMatrix(&A, 1, 2, 6);

  // B: 3x2 行列
  constructMatrix(&B, 3, 2);
  setElementMatrix(&B, 0, 0, 7);
  setElementMatrix(&B, 0, 1, 8);
  setElementMatrix(&B, 1, 0, 9);
  setElementMatrix(&B, 1, 1, 10);
  setElementMatrix(&B, 2, 0, 11);
  setElementMatrix(&B, 2, 1, 12);

  // 結果表示（productMatrix が in-place なので注意）
  printf("A =\n");
  printMatrix(&A);

  printf("B =\n");
  printMatrix(&B);

  // 結果を保存する行列 C を用意
  Matrix C;
  constructMatrix(&C, A.row, B.column);
  copyMatrix(&C, &A);
  productMatrix(&C, &B);

  printf("A x B =\n");
  printMatrix(&C);

  // メモリ解放
  destructMatrix(&A);
  destructMatrix(&B);
  destructMatrix(&C);

  return 0;
}