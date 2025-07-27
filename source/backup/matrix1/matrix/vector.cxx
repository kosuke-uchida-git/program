#include "vector.h"

// constructors
Vector::Vector() : Size(0), Elements(nullptr) {}

Vector::Vector(const int size_) : Vector(size_, 0.0) {}

Vector::Vector(const int size_, const double initial) : Size(size_) {
#ifdef DEBUG
  if (Size < 0) {
    throw std::runtime_error(
        "Vector::Vector(const int size_, const double initial)");
  }
#endif
  if (Size == 0) {
    Elements = nullptr;
  } else {
    Elements = new double[Size];
#pragma omp simd
    for (int i = 0; i < Size; i++) {
      (*this)[i] = initial;
    }
  }
}

Vector::Vector(const Vector &vector) : Size(vector.size()) {
  if (Size == 0) {
    Elements = nullptr;
  } else {
    Elements = new double[Size];
#pragma omp simd
    for (int i = 0; i < Size; i++) {
      (*this)[i] = vector[i];
    }
  }
}

Vector::Vector(Vector &&vector) noexcept
    : Size(vector.Size), Elements(vector.Elements) {
  vector.Size = 0;
  vector.Elements = nullptr;
}

// destructor
Vector::~Vector() {
  if (Elements != nullptr) {
    delete[] Elements;
  }
}

// getters and setters
int Vector::size() const { return Size; }

int &Vector::size() { return Size; }

double *Vector::elements() const { return Elements; }

double *&Vector::elements() { return Elements; }

double &Vector::operator[](const int index) const {
#ifdef DEBUG
  if (index < 0 || Size <= index) {
    throw std::runtime_error(
        "double Vector::operator[](const int index) const");
  }
#endif
  return Elements[index];
}

double &Vector::operator[](const int index) {
#ifdef DEBUG
  if (index < 0 || Size <= index) {
    throw std::runtime_error("double &Vector::operator[](const int index)");
  }
#endif
  return Elements[index];
}

// assign
Vector &Vector::operator=(const Vector &vector) {
  if (this == &vector) {
    return *this;
  }

  if (Size != vector.size()) {
    Size = vector.size();
    if (Elements != nullptr) {
      delete[] Elements;
    }
    Elements = new double[Size];
  }
#pragma omp simd
  for (int i = 0; i < Size; i++) {
    (*this)[i] = vector[i];
  }

  return *this;
}

Vector &Vector::operator=(Vector &&vector) noexcept {
  if (this == &vector) {
    return *this;
  }

  delete[] Elements;
  Size = vector.Size;
  Elements = vector.Elements;

  vector.Size = 0;
  vector.Elements = nullptr;

  return *this;
}

// comparison operators
bool Vector::operator==(const Vector &vector) const {
  if (Size != vector.Size)
    return false;
  for (int i = 0; i < Size; i++) {
    if ((*this)[i] != vector[i])
      return false;
  }
  return true;
}

bool Vector::operator!=(const Vector &vector) const {
  return !(*this == vector);
}

// cast
Vector::operator Matrix() const {
  Matrix result(1, Size);
  result[0] = *this;
  return result;
}

// print
void Vector::print() const {
  if (Size == 0) {
    return;
  }
  std::cout << "(";
  print_();
  std::cout << ")" << std::endl;
}

void Vector::print_() const {
  for (int i = 0; i < Size; i++) {
    std::cout << (*this)[i];
    if (i != Size - 1) {
      std::cout << ", ";
    }
  }
}

// add and remove
void Vector::add(const double a) {
  double *newElements = new double[Size + 1];
  for (int i = 0; i < Size; i++) {
    newElements[i] = (*this)[i];
  }
  newElements[Size] = a;
  delete[] Elements;
  Elements = newElements;
  Size++;
}

void Vector::remove(const int index) {
#ifdef DEBUG
  if (index < 0 || index >= Size) {
    throw std::runtime_error("void Vector::remove(const int index)");
  }
#endif
  double *newElements = new double[Size - 1];
  for (int i = 0, j = 0; i < Size; i++) {
    // skip index
    if (i == index) {
      continue;
    }
    newElements[j++] = (*this)[i];
  }
  delete[] Elements;
  Elements = newElements;
  Size--;
}

// calculate
void Vector::operator+=(const Vector &vector) {
#ifdef DEBUG
  if (Size != vector.size()) {
    throw std::runtime_error("void Vector::operator+=(const Vector &vector)");
  }
#endif
#pragma omp simd
  for (int i = 0; i < Size; i++) {
    (*this)[i] += vector[i];
  }
}

Vector Vector::operator+(const Vector &vector) const {
#ifdef DEBUG
  if (Size != vector.size()) {
    throw std::runtime_error(
        "Vector Vector::operator+(const Vector &vector) const");
  }
#endif
  Vector result(Size);
#pragma omp simd
  for (int i = 0; i < Size; ++i) {
    result[i] = (*this)[i] + vector[i];
  }
  return result;
}

void Vector::operator-=(const Vector &vector) {
#ifdef DEBUG
  if (Size != vector.size()) {
    throw std::runtime_error("void Vector::operator-=(const Vector &vector)");
  }
#endif
#pragma omp simd
  for (int i = 0; i < Size; i++) {
    (*this)[i] -= vector[i];
  }
}

Vector Vector::operator-(const Vector &vector) const {
#ifdef DEBUG
  if (Size != vector.size()) {
    throw std::runtime_error(
        "Vector Vector::operator-(const Vector &vector) const");
  }
#endif
  Vector result(Size);
#pragma omp simd
  for (int i = 0; i < Size; ++i) {
    result[i] = (*this)[i] - vector[i];
  }
  return result;
}

double Vector::l1Norm() const {
#ifdef DEBUG
  if (Size <= 0) {
    throw std::runtime_error("double Vector::l1Norm() const");
  }
#endif
  double result = 0.0;
#pragma omp simd reduction(+ : result)
  for (int i = 0; i < Size; i++) {
    result += std::abs((*this)[i]);
  }
  return result;
}

double Vector::l2NormSquare() const {
#ifdef DEBUG
  if (Size <= 0) {
    throw std::runtime_error("double Vector::l2NormSquare() const");
  }
#endif
  double result = 0.0;
#pragma omp simd reduction(+ : result)
  for (int i = 0; i < Size; i++) {
    result += (*this)[i] * (*this)[i];
  }
  return result;
}

double Vector::l2Norm() const { return sqrt(l2NormSquare()); }

double Vector::maxNorm() const {
#ifdef DEBUG
  if (Size <= 0) {
    throw std::runtime_error("double Vector::maxNorm() const");
  }
#endif
  double result = 0.0;
#pragma omp simd reduction(max : result)
  for (int i = 0; i < Size; i++) {
    if (result < std::abs((*this)[i])) {
      result = std::abs((*this)[i]);
    }
  }
  return result;
}

Vector operator*(const double a, const Vector &vector) {
  Vector result = vector;
#pragma omp simd
  for (int i = 0; i < result.size(); i++) {
    result[i] *= a;
  }
  return result;
}

double innerProduct(const Vector &vector1, const Vector &vector2) {
#ifdef DEBUG
  if (vector1.size() != vector2.size()) {
    throw std::runtime_error(
        "double innerProduct(const Vector &vector1, const Vector &vector2)");
  }
#endif
  double result = 0.0;
#pragma omp simd reduction(+ : result)
  for (int i = 0; i < vector1.size(); i++) {
    result += vector1[i] * vector2[i];
  }
  return result;
}