#ifndef REGRESSION
#define REGRESSION

#include "../matrix/matrix.h"
class Matrix;

class Regression {
protected:
  Matrix Explanatory;
  Matrix Objective;
  int DataCount;
  int Dimension;

public:
  // constructors
  Regression();
  Regression(const Matrix explanatory_, const Matrix objective_);
  Regression(const Matrix &dataset);
  Regression(const std::string filename);
  // copy constructor
  Regression(const Regression &regression);
  // move constructor
  Regression(Regression &&regression) noexcept;

  // destructor
  ~Regression();

  // getters and setters
  Matrix explanatory() const;
  Matrix &explanatory();
  Matrix objective() const;
  Matrix &objective();
  int dataCount() const;
  int &dataCount();
  int dimension() const;
  int &dimension();

  // assignment operators
  // copy assignment operator
  Regression &operator=(const Regression &regression);
  // move assignment operator
  Regression &operator=(Regression &&regression) noexcept;

  // The folllowing functions aren't implemented
  // print
  virtual void print() const {}

  // output a file
  virtual void output(const std::string filename) const {}

  // calculate
  virtual void optimize() {}
  virtual void initialize() {}
  virtual void revise() {}
};

#endif