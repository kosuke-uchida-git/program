#ifndef DOUBLE_ARRAY
#define DOUBLE_ARRAY

#include "../head.h"

typedef struct {
  size_t size, capacity;
  double *elements;
} DoubleArray;

DoubleArray *doubleArray_construct();
void doubleArray_destruct(DoubleArray *da);
void doubleArray_add(DoubleArray *da, double d);

#endif