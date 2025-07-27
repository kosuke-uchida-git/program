#ifndef MATRIX
#define MATRIX

#include "../doubleArray/doubleArray.h"

typedef struct {
  size_t row, column, size;
  double *elements;
} Matrix;

Matrix *matrix_construct(size_t row_, size_t column_);
Matrix *matrix_constructFromMatrix(Matrix *m);
Matrix *matrix_constructFromFile(const char *filename);
void matrix_destruct(Matrix *m);
void matrix_output(const Matrix *m, const char *filename);

// *m1 = *m2 (copy *m2 to *m1)
void matrix_copy(Matrix *m1, const Matrix *m2);
void matrix_move(Matrix *m1, Matrix *m2);

void matrix_print(const Matrix *m);

// *m1 += *m2
void matrix_add(Matrix *m1, const Matrix *m2);
// *m1 -= *m2
void matrix_subtract(Matrix *m1, const Matrix *m2);
// *m *= d
void matrix_multiply(Matrix *m, const double d);
// (*m1) *= (*m2)
void matrix_product(Matrix *m1, Matrix *m2);
void matrix_transpose(Matrix *m);
void matrix_transposeVector(Matrix *m);

double matrix_l2NormSquare(const Matrix *m);
double matrix_l2Norm(const Matrix *m);
double matrix_maxNorm(const Matrix *m);
double matrix_sumElements(const Matrix *m);
double matrix_meanElements(const Matrix *m);

#ifdef DEBUG
double *matrix_element(Matrix *m, size_t row_, size_t column_);
#else
static inline double *matrix_element(Matrix *m, size_t row_, size_t column_) {
  return m->elements + (row_ * m->column + column_);
}
#endif

static inline double sign(double x) { return (x > 0) - (x < 0); }

#endif