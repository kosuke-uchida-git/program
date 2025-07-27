#ifndef VECTOR
#define VECTOR

#include "header.h"
#include "matrix.h"
class Matrix;

class Vector {
protected:
  int Size;
  double *Elements;

public:
  // constructors
  Vector();
  Vector(const int size_);
  Vector(const int size_, const double initial);
  // copy constructor
  Vector(const Vector &vector);
  // move constructor
  Vector(Vector &&vector) noexcept;

  // destructor
  ~Vector();

  // getters and setters
  int size() const;
  int &size();
  double *elements() const;
  double *&elements();
  double &operator[](const int index) const;
  double &operator[](const int index);

  // assignment operators
  // copy assignment operator
  Vector &operator=(const Vector &vector);
  // move assignment operator
  Vector &operator=(Vector &&vector) noexcept;

  // comparixon operators
  bool operator==(const Vector &vector) const;
  bool operator!=(const Vector &vector) const;

  // cast
  operator Matrix() const;

  // print
  void print() const;
  void print_() const;

  // add and remove
  void add(const double a);
  void remove(const int index);

  // calculate
  void operator+=(const Vector &vector);
  Vector operator+(const Vector &vector) const;
  void operator-=(const Vector &vector);
  Vector operator-(const Vector &vector) const;
  double l1Norm() const;
  double l2Norm() const;
  double l2NormSquare() const;
  double maxNorm() const;
};

Vector operator*(const double a, const Vector &vector);
double innerProduct(const Vector &vector1, const Vector &vector2);

#endif