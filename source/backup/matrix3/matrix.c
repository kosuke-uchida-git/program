#include "matrix.h"

void constructMatrix(Matrix *m, int row_, int column_) {
  m->row = row_;
  m->column = column_;
  m->size = row_ * column_;
  m->elements = malloc(sizeof(double) * m->size);
  for (int i = 0; i < m->size; i++) {
    m->elements[i] = 0.0;
  }
}

void destructMatrix(Matrix *m) {
  if (m->elements != NULL) {
    free(m->elements);
    m->elements = NULL;
  }
}

void copyMatrix(Matrix *m1, Matrix *m2) {
  if (m1 == m2) {
    return;
  }
  if (m1->size != m2->size) {
    destructMatrix(m1);
    constructMatrix(m1, m2->row, m2->column);
  }
  for (int i = 0; i < m1->size; i++) {
    m1->elements[i] = m2->elements[i];
  }
}

void moveMatrix(Matrix *m1, Matrix *m2) {
  if (m1 == m2) {
    return;
  }

  destructMatrix(m1);
  m1->row = m2->row;
  m1->column = m2->column;
  m1->size = m2->size;
  m1->elements = m2->elements;

  m2->elements = NULL;
}

void printMatrix(Matrix *m) {
  int k = 0;
  printf("(");
  for (int i = 0; i < m->row; i++) {
    for (int j = 0; j < m->column; j++) {
      printf("%f ", m->elements[k++]);
    }
    if (i != m->row - 1) {
      printf("\n");
    }
  }
  printf(")\n");
}

double getElementMatrix(Matrix *m, int row_, int column_) {
  return m->elements[row_ * m->column + column_];
}

void setElementMatrix(Matrix *m, int row_, int column_, double d) {
  m->elements[row_ * m->column + column_] = d;
}

void addMatrix(Matrix *m1, Matrix *m2) {
  for (int i = 0; i < m1->size; i++) {
    m1->elements[i] += m2->elements[i];
  }
}

void subtractMatrix(Matrix *m1, Matrix *m2) {
  for (int i = 0; i < m1->size; i++) {
    m1->elements[i] -= m2->elements[i];
  }
}

void multiplyMatrix(Matrix *m, double d) {
  for (int i = 0; i < m->size; i++) {
    m->elements[i] *= d;
  }
}

void productMatrix(Matrix *m1, Matrix *m2) {
  Matrix *result = malloc(sizeof(Matrix));
  constructMatrix(result, m1->row, m2->column);

  for (int i = 0; i < m1->row; i++) {
    for (int j = 0; j < m2->column; j++) {
      double sum = 0.0;
      for (int k = 0; k < m1->column; k++) {
        sum += getElementMatrix(m1, i, k) * getElementMatrix(m2, k, j);
      }
      setElementMatrix(result, i, j, sum);
    }
  }
  moveMatrix(m1, result);
  free(result);
}