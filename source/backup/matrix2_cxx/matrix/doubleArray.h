#ifndef DOUBLE_ARRAY
#define DOUBLE_ARRAY

#include "header.h"

class DoubleArray {
protected:
  int Size;
  double *Elements;

public:
  // constructors
  DoubleArray();
  DoubleArray(const int size_);
  DoubleArray(const int size_, const double initial);
  // copy constructor
  DoubleArray(const DoubleArray &doubleArray);
  // move constructor
  DoubleArray(DoubleArray &&doubleArray) noexcept;

  // destructor
  ~DoubleArray();

  // getters and setters
  int size() const;
  int &size();
  double *elements() const;
  double *&elements();
  double &operator[](const int index) const;
  double &operator[](const int index);

  // assignment operators
  // copy assignment operator
  DoubleArray &operator=(const DoubleArray &doubleArray);
  // move assignment operator
  DoubleArray &operator=(DoubleArray &&doubleArray) noexcept;

  // comparison operators
  bool operator==(const DoubleArray &doubleArray) const;
  bool operator!=(const DoubleArray &doubleArray) const;

  // print
  void print() const;

  // add and remove
  void add(const double a);
  void remove(const int index);
};

#endif
