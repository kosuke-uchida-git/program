#ifndef LINEAR_REGRESSION
#define LINEAR_REGRESSION

#include "regression.h"
class Regression;

class LinearRegression : public virtual Regression {
protected:
  double Bias;
  Matrix Coefficient;
  Matrix Intermediate;
  double LassoRegularizer;
  double RidgeRegularizer;
  // For reviseIntermediate() : transposedExplanatory=Explanatory.transpose()
  Matrix transposedExplanatory;

public:
  // constructors
  LinearRegression();
  LinearRegression(const Matrix explanatory_, const Matrix objective_);
  LinearRegression(const Matrix dataset);
  LinearRegression(const std::string filename);
  LinearRegression(const Matrix explanatory_, const Matrix objective_,
                   const double ridgeRegularizer_,
                   const double lassoRegularizer_);
  LinearRegression(const Matrix dataset, const double ridgeRegularizer_,
                   const double lassoRegularizer_);
  LinearRegression(const std::string filename, const double ridgeRegularizer_,
                   const double lassoRegularizer_);
  // copy constructor
  LinearRegression(const LinearRegression &regression);
  // move constructor
  LinearRegression(LinearRegression &&regression) noexcept;

  // destructor
  ~LinearRegression();

  // getters and setters
  double bias() const;
  double &bias();
  Matrix coefficient() const;
  Matrix &coefficient();
  Matrix intermediate() const;
  Matrix &intermediate();
  double ridgeRegularizer() const;
  double &ridgeRegularizer();
  double lassoRegularizer() const;
  double &lassoRegularizer();

  // assienment operators
  //  copy assignment operator
  LinearRegression &operator=(const LinearRegression &regression);
  // move assignment operator
  LinearRegression &operator=(LinearRegression &&regression) noexcept;

  // print
  virtual void print() const; // override

  // output a file
  virtual void output(const std::string filename) const; // override

  // calculate
  virtual void optimize();   // override
  virtual void initialize(); // override
  virtual void revise();     // override
  virtual void reviseBias();
  virtual void reviseCoefficient(const int dimensionIndex);
  virtual void reviseIntermediate();
  virtual double objectiveValue() const;
};

#endif