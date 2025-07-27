#ifndef MATRIX
#define MATRIX

#include "doubleArray.h"
#include "header.h"
#include "intArray.h"

class IntArray;
class DoubleArray;

class Matrix {
protected:
  int Row, Column, Size;
  double *Elements;

public:
  // constructors
  Matrix();
  // zero matrix
  Matrix(const int row_, const int column_);
  // identity matrix
  Matrix(const int row_);
  // all initial matrix
  Matrix(const int row_, const int column_, const double initial);
  // construct from a text file
  Matrix(const std::string filename);
  // copy constructor
  Matrix(const Matrix &matrix);
  // move constructor
  Matrix(Matrix &&matrix) noexcept;

  // destructor
  ~Matrix();

  // getters and setters
  int row() const;
  int &row();
  int column() const;
  int &column();
  int size() const;
  int &size();
  double *elements() const;
  double *&elements();
  double operator()(const int row_, const int column_) const;
  double &operator()(const int row_, const int column_);
  double operator[](const int i) const;
  double &operator[](const int i);

  // assignment operators
  // copy assignment operator
  Matrix &operator=(const Matrix &matrix);
  // move assignment operator
  Matrix &operator=(Matrix &&matrix) noexcept;

  // comparixon operators
  bool operator==(const Matrix &matrix) const;
  bool operator!=(const Matrix &matrix) const;

  // cast
  operator double() const;

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
  double l2NormSquare() const;
  double l2Norm() const;
  double elementwiseMaxNorm() const;
};

// returns Matrix [a|b]
Matrix concatenate(const Matrix &a, const Matrix &b);
Matrix operator*(const double a, const Matrix &matrix);

#endif