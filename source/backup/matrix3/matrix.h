#ifndef MATRIX
#define MATRIX

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int row;
  int column;
  int size;
  double *elements;
} Matrix;

void constructMatrix(Matrix *m, int row_, int column_);
void destructMatrix(Matrix *m);
// *m1 = *m2 (copy *m2 to *m1)
void copyMatrix(Matrix *m1, Matrix *m2);
void moveMatrix(Matrix *m1, Matrix *m2);

void printMatrix(Matrix *m);
double getElementMatrix(Matrix *m, int row_, int column_);
void setElementMatrix(Matrix *m, int row_, int column_, double d);

// *m1 += *m2
void addMatrix(Matrix *m1, Matrix *m2);
// *m2 -= *m2
void subtractMatrix(Matrix *m1, Matrix *m2);
// *m *= a
void multiplyMatrix(Matrix *m, double d);
// (*m1) *= (*m2)
void productMatrix(Matrix *m1, Matrix *m2);

#endif