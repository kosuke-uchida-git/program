#include "doubleArray.h"

DoubleArray *doubleArray_construct() {
  DoubleArray *result = malloc(sizeof(DoubleArray));
  if (!result) {
    fprintf(stderr, "doubleArray_construct: malloc failed\n");
    exit(EXIT_FAILURE);
  }
  result->size = 0;
  result->capacity = 1;
  result->elements = calloc(1, sizeof(double));
  if (!result->elements) {
    fprintf(stderr, "doubleArray_construct: calloc failed\n");
    free(result);
    result = NULL;
    exit(EXIT_FAILURE);
  }
  return result;
}

void doubleArray_destruct(DoubleArray *da) {
  if (!da) {
    return;
  }
  free(da->elements);
  da->elements = NULL;
  free(da);
}

void doubleArray_add(DoubleArray *da, double d) {
#ifdef DEBUG
  if (!da) {
    fprintf(stderr, "doubleArray_add: NULL pointer passed\n");
    exit(EXIT_FAILURE);
  }
#endif
  if (da->size == da->capacity) {
    size_t newCapacity = da->capacity * 2;
    double *newElements = realloc(da->elements, newCapacity * sizeof(double));
    if (!newElements) {
      fprintf(stderr, "doubleArray_add: realloc failed\n");
      exit(EXIT_FAILURE);
    }
    da->elements = newElements;
    da->capacity = newCapacity;
  }
  da->elements[da->size++] = d;
}