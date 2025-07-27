#include "regression.h"

// constructors
Regression::Regression()
    : Explanatory(), Objective(), DataCount(0), Dimension(0) {}

Regression::Regression(const Matrix explanatory_, const Matrix objective_)
    : Explanatory(explanatory_), Objective(objective_) {
  DataCount = Explanatory.row();
  Dimension = Explanatory.column();
}

Regression::Regression(const Matrix &dataset) {
  DataCount = dataset.row();
  Dimension = dataset.column() - 1;
  Matrix explanatory_(DataCount, Dimension);
  Matrix objective_(DataCount, 1);
  for (int r = 0; r < explanatory_.row(); r++) {
    for (int c = 0; c < explanatory_.column(); c++) {
      explanatory_(r, c) = dataset(r, c);
    }
  }
  for (int r = 0; r < objective_.row(); r++) {
    objective_(r, 0) = dataset(r, dataset.column() - 1);
  }
  Explanatory = explanatory_;
  Objective = objective_;
}

Regression::Regression(const std::string filename)
    : Regression(Matrix(filename)) {}

// copy constructor
Regression::Regression(const Regression &regression)
    : Explanatory(regression.explanatory()), Objective(regression.objective()),
      DataCount(regression.dataCount()), Dimension(regression.dimension()) {}

// move constructor
Regression::Regression(Regression &&regression) noexcept
    : Explanatory(regression.explanatory()), Objective(regression.objective()),
      DataCount(regression.dataCount()), Dimension(regression.dimension()) {
  Matrix *dummy = new Matrix();
  regression.explanatory() = *dummy;
  regression.objective() = *dummy;
  delete dummy;

  regression.dataCount() = 0;
  regression.dimension() = 0;
}

// destructor
Regression::~Regression() {}

// getters and setters
Matrix Regression::explanatory() const { return Explanatory; }

Matrix &Regression::explanatory() { return Explanatory; }

Matrix Regression::objective() const { return Objective; }

Matrix &Regression::objective() { return Objective; }

int Regression::dataCount() const { return DataCount; }

int &Regression::dataCount() { return DataCount; }

int Regression::dimension() const { return Dimension; }

int &Regression::dimension() { return Dimension; }

// assignment operators
// copy assignment operator
Regression &Regression::operator=(const Regression &regression) {
  Explanatory = regression.explanatory();
  Objective = regression.objective();
  DataCount = regression.dataCount();
  Dimension = regression.dimension();
  return *this;
}

// move assignment operator
Regression &Regression::operator=(Regression &&regression) noexcept {
  if (this == &regression) {
    return *this;
  }

  Explanatory = regression.explanatory();
  Objective = regression.objective();
  DataCount = regression.dataCount();
  Dimension = regression.dimension();

  Matrix *dummy = new Matrix();
  regression.explanatory() = *dummy;
  regression.objective() = *dummy;
  delete dummy;

  regression.dataCount() = 0;
  regression.dimension() = 0;

  return *this;
}