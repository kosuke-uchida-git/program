#ifndef INT_ARRAY
#define INT_ARRAY

#include "../head.h"

typedef struct {
  size_t size, capacity;
  int *elements;
} IntArray;

IntArray *intArray_construct();
void intArray_destruct(IntArray *da);
void intArray_add(IntArray *da, int d);
void intArray_remove(IntArray *ia, size_t index);
void intArray_shuffle(IntArray *ia);
void intArray_print(const IntArray *ia);

#endif