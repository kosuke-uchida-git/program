#include "matrix.h"

// constructors
Matrix::Matrix() : Row(0), Column(0), Vectors(nullptr) {}

Matrix::Matrix(const int row_, const int column_)
    : Matrix(row_, column_, 0.0) {}

Matrix::Matrix(const int row_) : Matrix(row_, row_) {
  for (int r = 0; r < Row; r++) {
    (*this)[r][r] = 1.0;
  }
}

Matrix::Matrix(const int row_, const int column_, const double initial)
    : Row(row_), Column(column_) {
#ifdef DEBUG
  if (Row < 0 || Column < 0) {
    throw std::runtime_error(
        "Matrix::Matrix(int row_, int column_, double initial)");
  }
#endif
  if (Row == 0) {
    Vectors = nullptr;
  } else {
    Vectors = new Vector[Row];
    Vector dummy(Column, initial);
    for (int r = 0; r < Row; r++) {
      (*this)[r] = dummy;
    }
  }
}

Matrix::Matrix(const Matrix &matrix)
    : Row(matrix.row()), Column(matrix.column()), Vectors(new Vector[Row]) {
  for (int r = 0; r < Row; ++r) {
    Vectors[r] = matrix.Vectors[r];
  }
}

Matrix::Matrix(const std::string filename) {
  // read file
  std::ifstream ifs(filename);
#ifdef DEBUG
  if (!ifs.is_open()) {
    throw std::runtime_error("Matrix::Matrix(const std::string filename)");
  }
#endif
  std::string line;
  Vector values;
  Row = 0;
  Column = 0;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    double value;
    int tmpColumn = 0;
    while (iss >> value) {
      tmpColumn++;
      values.add(value);
    }
    if (tmpColumn > 0) {
      Row++;
      if (tmpColumn > Column) {
        Column = tmpColumn;
      }
    }
  }
  ifs.close();
  // edit Matrix
  Vectors = new Vector[Row];
  Vector dummy(Column);
  for (int i = 0; i < Row; i++) {
    (*this)[i] = dummy;
  }
  int t = 0;
  for (int i = 0; i < Row; i++) {
    for (int j = 0; j < Column; j++) {
      (*this)[i][j] = values[t];
      t++;
    }
  }
}

// destructor
Matrix::~Matrix() {
  if (Vectors != nullptr) {
    delete[] Vectors;
  }
}

// getters and setters
int Matrix::row() const { return Row; }

int &Matrix::row() { return Row; }

int Matrix::column() const { return Column; }

int &Matrix::column() { return Column; }

Vector *Matrix::vectors() const { return Vectors; }

Vector *&Matrix::vectors() { return Vectors; }

Vector &Matrix::operator[](const int row_) const { return Vectors[row_]; }

Vector &Matrix::operator[](const int row_) {
#ifdef DEBUG
  if (row_ < 0 || row_ >= Row) {
    throw std::runtime_error("Matrix::operator[] out of range");
  }
#endif
  return Vectors[row_];
}

Vector Matrix::columnVector(const int column_) const {
  Vector result(Row);
  for (int r = 0; r < Row; r++) {
    result[r] = (*this)[r][column_];
  }
  return result;
}

// assignment operators
// copy assignment operator
Matrix &Matrix::operator=(const Matrix &matrix) {
  if (this == &matrix) {
    return *this;
  }

  if (Row != matrix.row()) {
    Row = matrix.row();
    if (Vectors != nullptr) {
      delete[] Vectors;
    }
    Vectors = new Vector[Row];
  }

  Column = matrix.column();
#pragma omp simd
  for (int r = 0; r < Row; r++) {
    (*this)[r] = matrix[r];
  }
  return *this;
}

// move assignment operator
Matrix &Matrix::operator=(Matrix &&matrix) noexcept {
  if (this == &matrix) {
    return *this;
  }
  delete[] Vectors;
  Row = matrix.Row;
  Column = matrix.Column;
  Vectors = matrix.Vectors;
  matrix.Row = 0;
  matrix.Column = 0;
  matrix.Vectors = nullptr;
  return *this;
}

// comparison operators
bool Matrix::operator==(const Matrix &matrix) const {
  if (Row != matrix.Row || Column != matrix.Column) {
    return false;
  }
  for (int r = 0; r < Row; ++r) {
    if ((*this)[r] != matrix[r]) {
      return false;
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix &matrix) const {
  return !(*this == matrix);
}

// cast
Matrix::operator Vector() const {
#ifdef DEBUG
  if (Row != 1 || Column < 1) {
    throw std::runtime_error("Matrix::operator Vector() const");
  }
#endif
  return (*this)[0];
}

// print
void Matrix::print() const {
  if (Row == 0 || Column == 0) {
    return;
  }
  std::cout << "(";
  for (int r = 0; r < Row; r++) {
    (*this)[r].print_();
    if (r != Row - 1) {
      std::cout << std::endl;
    }
  }
  std::cout << ")" << std::endl;
}

// output a file
void Matrix::output(const std::string filename) const {
  // convert Matrix to std::string
  std::string text = "";
  for (int r = 0; r < Row; r++) {
    for (int c = 0; c < Column; c++) {
      if (isInteger((*this)[r][c])) {
        text += std::to_string(int((*this)[r][c]));
      } else {
        text += std::to_string((*this)[r][c]);
      }
      text += " ";
    }
    text += "\n";
  }

  // make a file
  std::ofstream ofs(filename);
#ifdef DEBUG
  if (!ofs) {
    throw std::runtime_error(
        "void Matrix::output(const std::string filename) const");
  }
#endif
  ofs << text;
  ofs.close();
}

// calculate
void Matrix::operator+=(const Matrix &matrix) {
#ifdef DEBUG
  if (Row != matrix.row() || Column != matrix.column()) {
    throw std::runtime_error("void Matrix::operator+=(const Matrix &matrix)");
  }
#endif
  for (int r = 0; r < Row; r++) {
#pragma omp simd
    for (int c = 0; c < Column; c++) {
      (*this)[r][c] += matrix[r][c];
    }
  }
}

Matrix Matrix::operator+(const Matrix &matrix) const {
  Matrix result = *this;
  result += matrix;
  return result;
}

void Matrix::operator-=(const Matrix &matrix) {
#ifdef DEBUG
  if (Row != matrix.row() || Column != matrix.column()) {
    throw std::runtime_error("void Matrix::operator-=(const Matrix &matrix)");
  }
#endif
  for (int r = 0; r < Row; r++) {
#pragma omp simd
    for (int c = 0; c < Column; c++) {
      (*this)[r][c] -= matrix[r][c];
    }
  }
}

Matrix Matrix::operator-(const Matrix &matrix) const {
  Matrix result = *this;
  result -= matrix;
  return result;
}

void Matrix::operator*=(const Matrix &matrix) { *this = *this * matrix; }

Matrix Matrix::operator*(const Matrix &matrix) const {
#ifdef DEBUG
  if (Column != matrix.row() || Row <= 0 || Column <= 0 || matrix.row() <= 0 ||
      matrix.column() <= 0) {
    throw std::runtime_error(
        "Matrix Matrix::operator*(const Matrix &matrix) const");
  }
#endif
  Matrix result(Row, matrix.column());
  for (int r = 0; r < result.row(); r++) {
    for (int c = 0; c < result.column(); c++) {
      double sum = 0.0;
#pragma omp simd reduction(+ : sum)
      for (int k = 0; k < Column; k++) {
        sum += (*this)[r][k] * matrix[k][c];
      }
      result[r][c] = sum;
    }
  }
  return result;
}

Matrix Matrix::transpose() const {
  Matrix result(Column, Row);
  for (int r = 0; r < Row; ++r) {
#pragma omp simd
    for (int c = 0; c < Column; ++c) {
      result[c][r] = (*this)[r][c];
    }
  }
  return result;
}

double Matrix::elementwiseMaxNorm() const {
  double result = 0.0;
  for (int r = 0; r < Row; r++) {
    if (result < (*this)[r].maxNorm()) {
      result = (*this)[r].maxNorm();
    }
  }
  return result;
}

Matrix Matrix::concatenate(const Matrix &a, const Matrix &b) const {
#ifdef DEBUG
  if (a.row() != b.row()) {
    throw std::runtime_error(
        "Matrix Matrix::concatenate(const Matrix &a, const Matrix &b) const");
  }
#endif

  Matrix result(a.row(), a.column() + b.column());
  for (int r = 0; r < result.row(); r++) {
#pragma omp simd
    for (int c = 0; c < a.column(); c++) {
      result[r][c] = a[r][c];
    }
#pragma omp simd
    for (int c = 0; c < b.column(); c++) {
      result[r][c + a.column()] = b[r][c];
    }
  }
  return result;
}

Matrix operator*(const double a, const Matrix &matrix) {
  Matrix result = matrix;
#pragma omp simd
  for (int r = 0; r < result.row(); r++) {
    result[r] = a * result[r];
  }
  return result;
}