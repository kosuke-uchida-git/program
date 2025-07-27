#include "intArray.h"

// constructors
IntArray::IntArray() : Size(0), Elements(nullptr) {}

IntArray::IntArray(const int size_) : IntArray(size_, 0) {}

IntArray::IntArray(const int size_, const int initial) : Size(size_) {
#ifdef DEBUG
  if (Size < 0) {
    throw std::runtime_error(
        "IntArray::IntArray(const int size_, const int initial)");
  }
#endif
  if (Size == 0) {
    Elements = nullptr;
  } else {
    Elements = new int[Size];
    for (int i = 0; i < Size; i++) {
      (*this)[i] = initial;
    }
  }
}

IntArray::IntArray(const IntArray &IntArray) : Size(IntArray.size()) {
  if (Size == 0) {
    Elements = nullptr;
  } else {
    Elements = new int[Size];
    for (int i = 0; i < Size; i++) {
      (*this)[i] = IntArray[i];
    }
  }
}

IntArray::IntArray(IntArray &&IntArray) noexcept
    : Size(IntArray.Size), Elements(IntArray.Elements) {
  IntArray.Size = 0;
  IntArray.Elements = nullptr;
}

// destructor
IntArray::~IntArray() {
  if (Elements != nullptr) {
    delete[] Elements;
  }
}

// getters and setters
int IntArray::size() const { return Size; }

int &IntArray::size() { return Size; }

int *IntArray::elements() const { return Elements; }

int *&IntArray::elements() { return Elements; }

int &IntArray::operator[](const int index) const {
#ifdef DEBUG
  if (index < 0 || Size <= index) {
    throw std::runtime_error("int IntArray::operator[](const int index) const");
  }
#endif
  return Elements[index];
}

int &IntArray::operator[](const int index) {
#ifdef DEBUG
  if (index < 0 || Size <= index) {
    throw std::runtime_error("int &IntArray::operator[](const int index)");
  }
#endif
  return Elements[index];
}

// assign
IntArray &IntArray::operator=(const IntArray &IntArray) {
  if (this == &IntArray) {
    return *this;
  }

  if (Size != IntArray.size()) {
    Size = IntArray.size();
    if (Elements != nullptr) {
      delete[] Elements;
    }
    Elements = new int[Size];
  }

  for (int i = 0; i < Size; i++) {
    (*this)[i] = IntArray[i];
  }

  return *this;
}

IntArray &IntArray::operator=(IntArray &&IntArray) noexcept {
  if (this == &IntArray) {
    return *this;
  }

  delete[] Elements;
  Size = IntArray.Size;
  Elements = IntArray.Elements;

  IntArray.Size = 0;
  IntArray.Elements = nullptr;

  return *this;
}

// comparison operators
bool IntArray::operator==(const IntArray &intArray) const {
  if (Size != intArray.Size)
    return false;
  for (int i = 0; i < Size; i++) {
    if ((*this)[i] != intArray[i])
      return false;
  }
  return true;
}

bool IntArray::operator!=(const IntArray &intArray) const {
  return !(*this == intArray);
}

// print
void IntArray::print() const {
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
void IntArray::add(const int a) {
  int *newElements = new int[Size + 1];
  for (int i = 0; i < Size; i++) {
    newElements[i] = (*this)[i];
  }
  newElements[Size] = a;
  delete[] Elements;
  Elements = newElements;
  Size++;
}

void IntArray::remove(const int index) {
#ifdef DEBUG
  if (index < 0 || index >= Size) {
    throw std::runtime_error("void IntArray::remove(const int index)");
  }
#endif
  int *newElements = new int[Size - 1];
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