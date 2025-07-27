#include "doubleArray.h"

// constructors
DoubleArray::DoubleArray() : Size(0), Elements(nullptr) {}

DoubleArray::DoubleArray(const int size_) : DoubleArray(size_, 0.0) {}

DoubleArray::DoubleArray(const int size_, const double initial) : Size(size_) {
#ifdef DEBUG
  if (Size < 0) {
    throw std::runtime_error(
        "DoubleArray::DoubleArray(const int size_, const double initial)");
  }
#endif
  if (Size == 0) {
    Elements = nullptr;
  } else {
    Elements = new double[Size];
    for (int i = 0; i < Size; i++) {
      (*this)[i] = initial;
    }
  }
}

DoubleArray::DoubleArray(const DoubleArray &doubleArray)
    : Size(doubleArray.size()) {
  if (Size == 0) {
    Elements = nullptr;
  } else {
    Elements = new double[Size];
    for (int i = 0; i < Size; i++) {
      (*this)[i] = doubleArray[i];
    }
  }
}

DoubleArray::DoubleArray(DoubleArray &&doubleArray) noexcept
    : Size(doubleArray.Size), Elements(doubleArray.Elements) {
  doubleArray.Size = 0;
  doubleArray.Elements = nullptr;
}

// destructor
DoubleArray::~DoubleArray() {
  if (Elements != nullptr) {
    delete[] Elements;
  }
}

// getters and setters
int DoubleArray::size() const { return Size; }

int &DoubleArray::size() { return Size; }

double *DoubleArray::elements() const { return Elements; }

double *&DoubleArray::elements() { return Elements; }

double &DoubleArray::operator[](const int index) const {
#ifdef DEBUG
  if (index < 0 || Size <= index) {
    throw std::runtime_error(
        "double DoubleArray::operator[](const int index) const");
  }
#endif
  return Elements[index];
}

double &DoubleArray::operator[](const int index) {
#ifdef DEBUG
  if (index < 0 || Size <= index) {
    throw std::runtime_error(
        "double &DoubleArray::operator[](const int index)");
  }
#endif
  return Elements[index];
}

// assign
DoubleArray &DoubleArray::operator=(const DoubleArray &doubleArray) {
  if (this == &doubleArray) {
    return *this;
  }

  if (Size != doubleArray.size()) {
    Size = doubleArray.size();
    if (Elements != nullptr) {
      delete[] Elements;
    }
    Elements = new double[Size];
  }

  for (int i = 0; i < Size; i++) {
    (*this)[i] = doubleArray[i];
  }

  return *this;
}

DoubleArray &DoubleArray::operator=(DoubleArray &&doubleArray) noexcept {
  if (this == &doubleArray) {
    return *this;
  }

  delete[] Elements;
  Size = doubleArray.Size;
  Elements = doubleArray.Elements;

  doubleArray.Size = 0;
  doubleArray.Elements = nullptr;

  return *this;
}

// comparison operators
bool DoubleArray::operator==(const DoubleArray &doubleArray) const {
  if (Size != doubleArray.Size)
    return false;
  for (int i = 0; i < Size; i++) {
    if ((*this)[i] != doubleArray[i])
      return false;
  }
  return true;
}

bool DoubleArray::operator!=(const DoubleArray &doubleArray) const {
  return !(*this == doubleArray);
}

// print
void DoubleArray::print() const {
  if (Size == 0) {
    return;
  }
  std::cout << "(";
  for (int i = 0; i < Size; i++) {
    std::cout << (*this)[i];
    if (i != Size - 1) {
      std::cout << ", ";
    }
  }
  std::cout << ")" << std::endl;
}

// add and remove
void DoubleArray::add(const double a) {
  double *newElements = new double[Size + 1];
  for (int i = 0; i < Size; i++) {
    newElements[i] = (*this)[i];
  }
  newElements[Size] = a;
  delete[] Elements;
  Elements = newElements;
  Size++;
}

void DoubleArray::remove(const int index) {
#ifdef DEBUG
  if (index < 0 || index >= Size) {
    throw std::runtime_error("void DoubleArray::remove(const int index)");
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
