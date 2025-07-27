#ifndef MATRIX
#define MATRIX

#include "header.h"
#include "vector.h"
class Vector;

class Matrix {
protected:
  int Row;
  int Column;
  Vector *Vectors;

public:
  // constructors
  Matrix();
  // zero matrix
  Matrix(const int row_, const int column_);
  // identity matrix
  Matrix(const int row_);
  // all initial matrix
  Matrix(const int row_, const int column_, const double initial);
  // copy constructor
  Matrix(const Matrix &matrix);
  // construct from a text file
  Matrix(const std::string filename);

  // destructor
  ~Matrix();

  // getters and setters
  int row() const;
  int &row();
  int column() const;
  int &column();
  Vector *vectors() const;
  Vector *&vectors();
  Vector &operator[](const int row_) const;
  Vector &operator[](const int row_);
  Vector columnVector(const int column_) const;

  // assignment operators
  // copy assignment operator
  Matrix &operator=(const Matrix &matrix);
  // move assignment operator
  Matrix &operator=(Matrix &&matrix) noexcept;

  // comparison operators
  bool operator==(const Matrix &matrix) const;
  bool operator!=(const Matrix &matrix) const;

  // cast
  operator Vector() const;

  // print
  void print() const;

  // output a file
  void output(const std::string filename) const;

  // calculate
  void operator+=(const Matrix &matrix);
  Matrix operator+(const Matrix &matrix) const;
  void operator-=(const Matrix &matrix);
  Matrix operator-(const Matrix &matrix) const;
  void operator*=(const Matrix &matrix);
  Matrix operator*(const Matrix &matrix) const;
  Matrix transpose() const;
  double elementwiseMaxNorm() const;
  // returns Matrix [a|b]
  Matrix concatenate(const Matrix &a, const Matrix &b) const;
};

Matrix operator*(const double a, const Matrix &matrix);

#endif