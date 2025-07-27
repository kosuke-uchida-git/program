#include "linearRegression.h"

// constructors
LinearRegression::LinearRegression()
    : Regression(), Bias(0), Coefficient(), Intermediate() {}

LinearRegression::LinearRegression(const Matrix explanatory_,
                                   const Matrix objective_)
    : Regression(explanatory_, objective_), Bias(0),
      Coefficient(1, explanatory_.column()),
      Intermediate(explanatory_.row(), 1) {}

LinearRegression::LinearRegression(const Matrix dataset)
    : Regression(dataset), Bias(0) {
  Matrix dummy1(1, Explanatory.column());
  Coefficient = dummy1;
  Matrix dummy2(Explanatory.row(), 1);
  Intermediate = dummy2;
}

LinearRegression::LinearRegression(const std::string filename)
    : Regression(filename), Bias(0) {
  Matrix dummy1(1, Explanatory.column());
  Coefficient = dummy1;
  Matrix dummy2(Explanatory.row(), 1);
  Intermediate = dummy2;
}

LinearRegression::LinearRegression(const Matrix explanatory_,
                                   const Matrix objective_,
                                   const double ridgeRegularizer_,
                                   const double lassoRegularizer_)
    : LinearRegression(explanatory_, objective_) {
  LassoRegularizer = lassoRegularizer_;
  RidgeRegularizer = ridgeRegularizer_;
}

LinearRegression::LinearRegression(const Matrix dataset,
                                   const double ridgeRegularizer_,
                                   const double lassoRegularizer_)
    : LinearRegression(dataset) {
  LassoRegularizer = lassoRegularizer_;
  RidgeRegularizer = ridgeRegularizer_;
}

LinearRegression::LinearRegression(const std::string filename,
                                   const double ridgeRegularizer_,
                                   const double lassoRegularizer_)
    : LinearRegression(filename) {
  LassoRegularizer = lassoRegularizer_;
  RidgeRegularizer = ridgeRegularizer_;
}

// copy constructor
LinearRegression::LinearRegression(const LinearRegression &regression)
    : Regression(regression), Bias(0),
      LassoRegularizer(regression.lassoRegularizer()),
      RidgeRegularizer(regression.ridgeRegularizer()) {
  Matrix dummy1(1, Explanatory.column());
  Coefficient = dummy1;
  Matrix dummy2(Explanatory.row(), 1);
  Intermediate = dummy2;
}

// move constructor
LinearRegression::LinearRegression(LinearRegression &&regression) noexcept
    : Regression(regression), Bias(0),
      LassoRegularizer(regression.lassoRegularizer()),
      RidgeRegularizer(regression.ridgeRegularizer()) {
  Matrix dummy1(1, Explanatory.column());
  Coefficient = dummy1;
  Matrix dummy2(Explanatory.row(), 1);
  Intermediate = dummy2;

  regression.explanatory() = Matrix();
  regression.objective() = Matrix();
  regression.coefficient() = Matrix();
  regression.intermediate() = Matrix();
  regression.dataCount() = 0;
  regression.dimension() = 0;
  regression.bias() = 0.0;
  regression.lassoRegularizer() = 0.0;
  regression.ridgeRegularizer() = 0.0;
}

// destructor
LinearRegression::~LinearRegression() {}

// getters and setters
double LinearRegression::bias() const { return Bias; }
double &LinearRegression::bias() { return Bias; }
Matrix LinearRegression::coefficient() const { return Coefficient; }
Matrix &LinearRegression::coefficient() { return Coefficient; }
Matrix LinearRegression::intermediate() const { return Intermediate; }
Matrix &LinearRegression::intermediate() { return Intermediate; }
double LinearRegression::ridgeRegularizer() const { return RidgeRegularizer; }
double &LinearRegression::ridgeRegularizer() { return RidgeRegularizer; }
double LinearRegression::lassoRegularizer() const { return LassoRegularizer; }
double &LinearRegression::lassoRegularizer() { return LassoRegularizer; }

// assienment operators
//  copy assignment operator
LinearRegression &
LinearRegression::operator=(const LinearRegression &regression) {
  Explanatory = regression.explanatory();
  Objective = regression.objective();
  DataCount = regression.dataCount();
  Dimension = regression.dimension();
  Bias = regression.bias();
  Coefficient = regression.coefficient();
  Intermediate = regression.intermediate();
  RidgeRegularizer = regression.ridgeRegularizer();
  LassoRegularizer = regression.lassoRegularizer();
  return *this;
}

// move assignment operator
LinearRegression &
LinearRegression::operator=(LinearRegression &&regression) noexcept {
  if (this == &regression) {
    return *this;
  }

  Explanatory = regression.explanatory();
  Objective = regression.objective();
  DataCount = regression.dataCount();
  Dimension = regression.dimension();
  Bias = regression.bias();
  Coefficient = regression.coefficient();
  Intermediate = regression.intermediate();
  RidgeRegularizer = regression.ridgeRegularizer();
  LassoRegularizer = regression.lassoRegularizer();

  regression.explanatory() = Matrix();
  regression.objective() = Matrix();
  regression.coefficient() = Matrix();
  regression.intermediate() = Matrix();
  regression.dataCount() = 0;
  regression.dimension() = 0;
  regression.bias() = 0.0;
  regression.ridgeRegularizer() = 0.0;
  regression.lassoRegularizer() = 0.0;

  return *this;
}

// print
void LinearRegression::print() const {
  std::cout << "Bias=" << Bias << std::endl;
  std::cout << "Coefficient=" << std::endl;
  Coefficient.print();
}

// output a file
void LinearRegression::output(const std::string filename) const {
  // convert Matrix to std::string
  std::string text = std::to_string(Bias) + "\n";
  for (int r = 0; r < Coefficient.row(); r++) {
    for (int c = 0; c < Coefficient.column(); c++) {
      if (isInteger(Coefficient[r][c])) {
        text += std::to_string(int(Coefficient[r][c]));
      } else {
        text += std::to_string(Coefficient[r][c]);
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
        "void LinearRegression::output(const std::string filename) const");
  }
#endif
  ofs << text;
  ofs.close();
}

// calculate
void LinearRegression::optimize() {
  double velocity = 1.2;
  initialize();
  // For reviseIntermediate() : transposedExplanatory=Explanatory.transpose()
  transposedExplanatory = Explanatory.transpose();
#ifdef DEBUG
  int iterate = 0;
#endif
  while (1) {
#ifdef DEBUG
    iterate++;
#endif
    double tmpBias = Bias;
    Matrix tmpCoefficient = Coefficient;
    revise();
    Coefficient = tmpCoefficient + velocity * (Coefficient - tmpCoefficient);
    // calculate difference (Coefficient part)
    double difference =
        std::abs((Coefficient - tmpCoefficient).elementwiseMaxNorm());

    // calculate velocity with difference (Coefficient part)
    velocity = 1.0 + 100.0 * difference;
    if (velocity < 1.0 + 1.0E-14) {
      velocity = 1.0;
    } else if (velocity > 1.2) {
      velocity = 1.2;
    }

    // calculate difference (Bias part)
    if (difference < std::abs(Bias - tmpBias)) {
      difference = std::abs(Bias - tmpBias);
    }

#ifdef DEBUG
    if (iterate % 10000 == 0) {
      std::cout << "difference:" << difference << std::endl;
    }
#endif
    if (difference < 1.0E-16) {
      break;
    }
  }
#ifdef DEBUG
  std::cout << "iterate:" << iterate << std::endl;
#endif
}

void LinearRegression::initialize() {}

void LinearRegression::revise() {
  reviseIntermediate();
  reviseBias();
#pragma omp simd
  for (int dimensionIndex = 0; dimensionIndex < Dimension; dimensionIndex++) {
    reviseCoefficient(dimensionIndex);
  }
}

void LinearRegression::reviseBias() {
  Bias = 0.0;
#pragma omp parallel for reduction(+ : Bias)
  for (int n = 0; n < DataCount; n++) {
    Bias += Intermediate[n][0];
  }
  Bias /= DataCount;
}

void LinearRegression::reviseCoefficient(const int dimensionIndex) {
  double numerator = 0.0, denominator = 0.0;
#pragma omp parallel for reduction(+ : numerator, denominator)
  for (int n = 0; n < DataCount; n++) {
    numerator +=
        Explanatory[n][dimensionIndex] *
        (Intermediate[n][0] +
         Coefficient[0][dimensionIndex] * Explanatory[n][dimensionIndex] -
         Bias);
    denominator +=
        Explanatory[n][dimensionIndex] * Explanatory[n][dimensionIndex];
  }

  // regularize
  if (std::abs(numerator) > LassoRegularizer) {
    numerator -= LassoRegularizer * sign(Coefficient[0][dimensionIndex]);
  } else {
    Coefficient[0][dimensionIndex] = 0.0;
    return;
  }
  denominator += RidgeRegularizer;

  Coefficient[0][dimensionIndex] = numerator / denominator;
}

void LinearRegression::reviseIntermediate() {
  // transposedExplanatory is initialized in optimize() for
  // transposedExplanatory=Explanatory.transpose()
  Intermediate = Objective - (Coefficient * transposedExplanatory).transpose();
}

double LinearRegression::objectiveValue() const {
  Matrix biasMatrix(DataCount, 1, Bias);
  Vector vector =
      (Explanatory * Coefficient.transpose() + biasMatrix - Objective)
          .transpose();
  return vector.l2NormSquare();
}