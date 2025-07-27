#include "matrix.h"

Matrix *matrix_construct(size_t row_, size_t column_) {
#ifdef DEBUG
  if (row_ == 0 || column_ == 0) {
    fprintf(stderr, "matrix_construct: invalid dimensions\n");
    exit(EXIT_FAILURE);
  }
#endif
  Matrix *m = malloc(sizeof(Matrix));
  if (!m) {
    fprintf(stderr, "matrix_construct: malloc failed\n");
    exit(EXIT_FAILURE);
  }

  m->row = row_;
  m->column = column_;
  m->size = row_ * column_;
  m->elements = calloc(m->size, sizeof(double));
  if (!m->elements) {
    fprintf(stderr, "matrix_construct: calloc failed (elements)\n");
    free(m);
    exit(EXIT_FAILURE);
  }

  return m;
}

Matrix *matrix_constructFromMatrix(Matrix *m) {
#ifdef DEBUG
  if (!m) {
    fprintf(stderr, "matrix_constructFromMatrix: NULL pointer argument\n");
    exit(EXIT_FAILURE);
  }
#endif

  Matrix *result = malloc(sizeof(Matrix));
  if (!result) {
    fprintf(stderr, "matrix_construct: malloc failed\n");
    exit(EXIT_FAILURE);
  }

  result->row = m->row;
  result->column = m->column;
  result->size = m->size;
  result->elements = malloc(result->size * sizeof(double));
  if (!result->elements) {
    fprintf(stderr, "matrix_constructFromMatrix: malloc failed (elements)\n");
    free(result);
    exit(EXIT_FAILURE);
  }
  memcpy(result->elements, m->elements, result->size * sizeof(double));

  return result;
}

Matrix *matrix_constructFromFile(const char *filename) {
#ifdef DEBUG
  if (!filename) {
    fprintf(stderr, "matrix_constructFromFile: NULL pointer argument\n");
    exit(EXIT_FAILURE);
  }
#endif
  // Open the file for reading
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "matrix_constructFromFile: failed to open %s\n", filename);
    exit(EXIT_FAILURE);
  }

  char *line = NULL; // Line buffer (allocated dynamically by getline)
  size_t len = 0;    // Buffer size used by getline (initially 0)
  ssize_t read;      // Number of characters read by getline
  size_t row = 0;    // Row counter
  size_t column = 0; // Column count (determined from the first row)

  // Temporary dynamic array to store all elements
  DoubleArray *data = doubleArray_construct();

  // Read the file line by line
  while ((read = getline(&line, &len, fp)) != -1) {
    size_t columnCount = 0;

    // Split the line into tokens (space/tab/newline-delimited)
    char *token = strtok(line, " \t\n");
    while (token) {
      // Convert token to double and add to dynamic array
      double value = strtod(token, NULL);
      doubleArray_add(data, value);
      token = strtok(NULL, " \t\n");
      columnCount++;
    }

    // Skip empty lines
    if (columnCount == 0) {
      continue;
    }

    // Set column count on the first row
    if (row == 0) {
      column = columnCount;
    }
    // Ensure consistent column count across all rows
    else if (columnCount != column) {
      fprintf(
          stderr,
          "matrix_constructFromFile: inconsistent column count on line %zu\n",
          row + 1);
      free(line);
      doubleArray_destruct(data);
      fclose(fp);
      exit(EXIT_FAILURE);
    }

    row++;
  }

  // Clean up resources
  free(line);
  fclose(fp);

  // Construct Matrix with collected dimensions
  Matrix *m = matrix_construct(row, column);

  // Copy elements into Matrix
  memcpy(m->elements, data->elements, data->size * sizeof(double));

  // Free temporary dynamic array
  doubleArray_destruct(data);

  return m;
}

void matrix_destruct(Matrix *m) {
  if (!m) {
    return;
  }
  free(m->elements);
  m->elements = NULL;
  free(m);
}

void matrix_output(const Matrix *m, const char *filename) {
#ifdef DEBUG
  if (!m || !m->elements) {
    fprintf(stderr, "matrix_writeToFile: NULL matrix\n");
    exit(EXIT_FAILURE);
  }
#endif

  FILE *fp = fopen(filename, "w");
  if (!fp) {
    fprintf(stderr, "matrix_writeToFile: failed to open %s for writing\n",
            filename);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < m->row; i++) {
    for (size_t j = 0; j < m->column; j++) {
      fprintf(fp, "%.16g",
              m->elements[i * m->column + j]); // compact and precise
      if (j != m->column - 1) {
        fputc(' ', fp); // separate columns with a space
      }
    }
    fputc('\n', fp); // separate rows with newline
  }

  fclose(fp);
}

void matrix_copy(Matrix *m1, const Matrix *m2) {
  if (!m1 || !m2 || m1 == m2) {
    return;
  }
  if (m1->size != m2->size) {
    double *newElements = realloc(m1->elements, sizeof(double) * m2->size);
    if (!newElements) {
      fprintf(stderr, "matrix_copy: realloc failed\n");
      exit(EXIT_FAILURE);
    }
    m1->elements = newElements;
    m1->size = m2->size;
  }
  m1->row = m2->row;
  m1->column = m2->column;

  memcpy(m1->elements, m2->elements, m1->size * sizeof(double));
}

void matrix_copyRow(Matrix *m1, Matrix *m2, size_t r1, size_t r2) {
#ifdef DEBUG
  if (!m1 || !m2 || r1 >= m1->row || r2 >= m2->row ||
      m1->column != m2->column) {
    fprintf(stderr, "matrix_copy: invalid arguments\n");
    exit(EXIT_FAILURE);
  }
#endif
  memcpy(m1->elements + r1 * m1->column, m2->elements + r2 * m2->column,
         m1->column * sizeof(double));
}

void matrix_move(Matrix *m1, Matrix *m2) {
  if (m1 == m2) {
    return;
  }
#ifdef DEBUG
  if (!m1 || !m2) {
    fprintf(stderr, "matrix_move: NULL pointer argument\n");
    exit(EXIT_FAILURE);
  }
#endif
  if (m1->elements) {
    free(m1->elements);
  }
  m1->row = m2->row;
  m1->column = m2->column;
  m1->size = m2->size;
  m1->elements = m2->elements;
  m2->row = 0;
  m2->column = 0;
  m2->size = 0;
  m2->elements = NULL;
}

void matrix_print(const Matrix *m) {
  if (!m) {
    return;
  }
  size_t k = 0;
  printf("(");
  for (size_t i = 0; i < m->row; i++) {
    for (size_t j = 0; j < m->column; j++) {
      printf("%f ", m->elements[k++]);
    }
    if (i != m->row - 1) {
      printf("\n");
    }
  }
  printf(")\n");
}

void matrix_add(Matrix *m1, const Matrix *m2) {
#ifdef DEBUG
  if (!m1 || !m2 || m1->row != m2->row || m1->column != m2->column) {
    fprintf(stderr, "matrix_add: incompatible dimensions\n");
    return;
  }
#endif
#pragma omp simd
  for (size_t i = 0; i < m1->size; i++) {
    m1->elements[i] += m2->elements[i];
  }
}

void matrix_subtract(Matrix *m1, const Matrix *m2) {
#ifdef DEBUG
  if (!m1 || !m2 || m1->row != m2->row || m1->column != m2->column) {
    fprintf(stderr, "matrix_subtract: incompatible dimensions\n");
    return;
  }
#endif
#pragma omp simd
  for (size_t i = 0; i < m1->size; i++) {
    m1->elements[i] -= m2->elements[i];
  }
}

void matrix_multiply(Matrix *m, double d) {
#ifdef DEBUG
  if (!m || !m->elements) {
    fprintf(stderr, "matrix_multiply: incompatible dimensions\n");
    exit(EXIT_FAILURE);
  }
#endif
#pragma omp simd
  for (size_t i = 0; i < m->size; i++) {
    m->elements[i] *= d;
  }
}

void matrix_product(Matrix *m1, Matrix *m2) {
#ifdef DEBUG
  if (!m1 || !m2 || m1->column != m2->row) {
    fprintf(stderr, "matrix_product: incompatible dimensions\n");
    fprintf(stderr, "\tm1(%ld,%ld) * m2(%ld,%ld)\n", m1->row, m1->column,
            m2->row, m2->column);
    exit(EXIT_FAILURE);
  }
#endif
  Matrix *result = matrix_construct(m1->row, m2->column);
  for (size_t i = 0; i < result->row; i++) {
    for (size_t j = 0; j < result->column; j++) {
      double sum = 0.0;
#pragma omp simd reduction(+ : sum)
      for (size_t k = 0; k < m1->column; k++) {
        sum +=
            m1->elements[i * m1->column + k] * m2->elements[k * m2->column + j];
      }
      result->elements[i * result->column + j] = sum;
    }
  }

  matrix_move(m1, result);
  matrix_destruct(result);
}

void matrix_transpose(Matrix *m) {
#ifdef DEBUG
  if (!m || !m->elements) {
    fprintf(stderr, "matrix_transpose: incompatible dimensions\n");
    exit(EXIT_FAILURE);
  }
#endif
  Matrix *result = matrix_construct(m->column, m->row);
  for (size_t i = 0; i < m->row; i++) {
#pragma omp simd
    for (size_t j = 0; j < m->column; j++) {
      result->elements[j * m->row + i] = m->elements[i * m->column + j];
    }
  }
  matrix_move(m, result);
  matrix_destruct(result);
}

void matrix_transposeVector(Matrix *m) {
#ifdef DEBUG
  if (!m || !m->elements || !(m->row == 1 || m->column == 1)) {
    fprintf(stderr, "matrix_transposeVector: incompatible dimensions\n");
    exit(EXIT_FAILURE);
  }
#endif
  size_t tmp = m->row;
  m->row = m->column;
  m->column = tmp;
}

double matrix_l1Norm(const Matrix *m) {
  if (!m || !m->elements) {
    return 0.0;
  }
  double result = 0.0;
#pragma omp simd reduction(+ : result)
  for (size_t i = 0; i < m->size; i++) {
    result += fabs(m->elements[i]);
  }
  return result;
}

double matrix_l2NormSquare(const Matrix *m) {
  if (!m || !m->elements) {
    return 0.0;
  }
  double result = 0.0;
#pragma omp simd reduction(+ : result)
  for (size_t i = 0; i < m->size; i++) {
    result += m->elements[i] * m->elements[i];
  }
  return result;
}

double matrix_l2Norm(const Matrix *m) { return sqrt(matrix_l2NormSquare(m)); }

double matrix_maxNorm(const Matrix *m) {
  if (!m || !m->elements) {
    return 0.0;
  }
  double result = 0.0;
  for (size_t i = 0; i < m->size; i++) {
    double value = fabs(m->elements[i]);
    if (value > result) {
      result = value;
    }
  }
  return result;
}

double matrix_sumElements(const Matrix *m) {
  double result = 0.0;
  for (size_t i = 0; i < m->size; i++) {
    result += m->elements[i];
  }
  return result;
}

double matrix_meanElements(const Matrix *m) {
  double result = 0.0;
  for (size_t i = 0; i < m->size; i++) {
    result += m->elements[i];
  }
  result /= m->size;
  return result;
}

#ifdef DEBUG
double *matrix_element(Matrix *m, size_t row_, size_t column_) {
  if (!m || !m->elements || row_ >= m->row || column_ >= m->column) {
    fprintf(stderr, "matrix_element: invalid index access\n");
    exit(EXIT_FAILURE);
  }
  return m->elements + (row_ * m->column + column_);
}
#endif