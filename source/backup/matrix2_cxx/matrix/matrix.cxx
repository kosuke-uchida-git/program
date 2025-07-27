#include "matrix.h"

// constructors
Matrix::Matrix() : Row(0), Column(0), Size(0), Elements(nullptr) {}

Matrix::Matrix(const int row_, const int column_)
    : Matrix(row_, column_, 0.0) {}

Matrix::Matrix(const int row_) : Matrix(row_, row_) {
  for (int r = 0; r < Row; r++) {
    (*this)(r, r) = 1.0;
  }
}

Matrix::Matrix(const int row_, const int column_, const double initial)
    : Row(row_), Column(column_), Size(row_ * column_) {
#ifdef DEBUG
  if (Row < 0 || Column < 0) {
    throw std::runtime_error(
        "Matrix::Matrix(int row_, int column_, double initial)");
  }
#endif
  if (Row == 0 || Column == 0) {
    Elements = nullptr;
  } else {
    Elements = new double[Size];
  }
  for (int i = 0; i < Size; i++) {
    Elements[i] = initial;
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
  DoubleArray values;
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
  Size = Row * Column;
  Elements = new double[Size];
  for (int i = 0; i < Size; i++) {
    Elements[i] = values[i];
  }
}

// copy constructor
Matrix::Matrix(const Matrix &matrix)
    : Row(matrix.row()), Column(matrix.column()), Size(matrix.size()) {
  Elements = new double[Size];
  for (int i = 0; i < Size; i++) {
    Elements[i] = matrix.Elements[i];
  }
}

// move constructor
Matrix::Matrix(Matrix &&matrix) noexcept
    : Row(matrix.Row), Column(matrix.Column), Size(matrix.Size),
      Elements(matrix.Elements) {
  matrix.Row = 0;
  matrix.Column = 0;
  matrix.Size = 0;
  matrix.Elements = nullptr;
}

// destructor
Matrix::~Matrix() {
  if (Elements != nullptr) {
    delete[] Elements;
  }
}

// getters and setters
int Matrix::row() const { return Row; }

int &Matrix::row() { return Row; }

int Matrix::column() const { return Column; }

int &Matrix::column() { return Column; }

int Matrix::size() const { return Size; }

int &Matrix::size() { return Size; }

double *Matrix::elements() const { return Elements; }

double *&Matrix::elements() { return Elements; }

double Matrix::operator()(const int row_, const int column_) const {
#ifdef DEBUG
  if (row_ < 0 || row_ >= Row || column_ < 0 || column_ >= Column) {
    throw std::runtime_error(
        "double Matrix::operator()(const int row_,const int column_) const");
  }
#endif
  return Elements[Column * row_ + column_];
}

double &Matrix::operator()(const int row_, const int column_) {
#ifdef DEBUG
  if (row_ < 0 || row_ >= Row || column_ < 0 || column_ >= Column) {
    throw std::runtime_error(
        "double &Matrix::operator()(const int row_,const int column_)");
  }
#endif
  return Elements[Column * row_ + column_];
}

double Matrix::operator[](const int i) const { return Elements[i]; }

double &Matrix::operator[](const int i) { return Elements[i]; }

// assignment operators
// copy assignment operator
Matrix &Matrix::operator=(const Matrix &matrix) {
  if (this == &matrix) {
    return *this;
  }

  Row = matrix.row();
  Column = matrix.column();
  if (Size != matrix.size()) {
    Size = matrix.size();
    if (Elements != nullptr) {
      delete[] Elements;
    }
    Elements = new double[Size];
  }

#pragma omp simd
  for (int i = 0; i < Size; i++) {
    Elements[i] = matrix[i];
  }
  return *this;
}

// move assignment operator
Matrix &Matrix::operator=(Matrix &&matrix) noexcept {
  if (this == &matrix) {
    return *this;
  }

  Row = matrix.row();
  Column = matrix.column();
  Size = matrix.size();
  Elements = matrix.elements();
  matrix.row() = 0;
  matrix.column() = 0;
  matrix.size() = 0;
  matrix.elements() = nullptr;
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
Matrix::operator double() const {
#ifdef DEBUG
  if (Size != 1) {
    throw std::runtime_error("Matrix::operator double() const");
  }
#endif
  return Elements[0];
}

// print
void Matrix::print() const {
  if (Row == 0 || Column == 0) {
    return;
  }
  int k = 0;
  std::cout << "(";
  for (int i = 0; i < Row; i++) {
    for (int j = 0; j < Column; j++) {
      std::cout << Elements[k++] << " ";
    }
    if (i != Row - 1) {
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
      if (isInteger((*this)(r, c))) {
        text += std::to_string(int((*this)(r, c)));
      } else {
        text += std::to_string((*this)(r, c));
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
      (*this)(r, c) += matrix(r, c);
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
      (*this)(r, c) -= matrix(r, c);
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
        sum += (*this)(r, k) * matrix(k, c);
      }
      result(r, c) = sum;
    }
  }
  return result;
}

Matrix Matrix::transpose() const {
  Matrix result(Column, Row);
  for (int r = 0; r < Row; ++r) {
#pragma omp simd
    for (int c = 0; c < Column; ++c) {
      result(c, r) = (*this)(r, c);
    }
  }
  return result;
}

double Matrix::l2NormSquare() const {
  double result = 0.0;
  for (int i = 0; i < Size; i++) {
    result += Elements[i] * Elements[i];
  }
  return result;
}

double Matrix::l2Norm() const { return std::sqrt(l2NormSquare()); }

double Matrix::elementwiseMaxNorm() const {
  double result = 0.0;
  for (int i = 0; i < Size; i++) {
    if (result < std::abs(Elements[i])) {
      result = std::abs(Elements[i]);
    }
  }
  return result;
}

Matrix concatenate(const Matrix &a, const Matrix &b) {
#ifdef DEBUG
  if (a.row() != b.row()) {
    throw std::runtime_error(
        "Matrix concatenate(const Matrix &a, const Matrix &b)");
  }
#endif

  Matrix result(a.row(), a.column() + b.column());
  for (int r = 0; r < result.row(); r++) {
#pragma omp simd
    for (int c = 0; c < a.column(); c++) {
      result(r, c) = a(r, c);
    }
#pragma omp simd
    for (int c = 0; c < b.column(); c++) {
      result(r, c + a.column()) = b(r, c);
    }
  }
  return result;
}

Matrix operator*(const double a, const Matrix &matrix) {
  Matrix result = matrix;
#pragma omp simd
  for (int i = 0; i < matrix.size(); i++) {
    result[i] = a * result[i];
  }
  return result;
}