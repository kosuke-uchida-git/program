#ifndef INT_ARRAY
#define INT_ARRAY

#include "header.h"

class IntArray {
protected:
  int Size;
  int *Elements;

public:
  // constructors
  IntArray();
  IntArray(const int size_);
  IntArray(const int size_, const int initial);
  // copy constructor
  IntArray(const IntArray &intArray);
  // move constructor
  IntArray(IntArray &&intArray) noexcept;

  // destructor
  ~IntArray();

  // getters and setters
  int size() const;
  int &size();
  int *elements() const;
  int *&elements();
  int &operator[](const int index) const;
  int &operator[](const int index);

  // assignment operators
  // copy assignment operator
  IntArray &operator=(const IntArray &intArray);
  // move assignment operator
  IntArray &operator=(IntArray &&intArray) noexcept;

  // comparixon operators
  bool operator==(const IntArray &intArray) const;
  bool operator!=(const IntArray &intArray) const;

  // print
  void print() const;

  // add and remove
  void add(const int a);
  void remove(const int index);
};

#endif