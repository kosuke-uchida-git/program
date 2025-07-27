#include "intArray.h"

IntArray *intArray_construct() {
  IntArray *result = malloc(sizeof(IntArray));
  if (!result) {
    fprintf(stderr, "intArray_construct: malloc failed\n");
    exit(EXIT_FAILURE);
  }
  result->size = 0;
  result->capacity = 1;
  result->elements = calloc(1, sizeof(int));
  if (!result->elements) {
    fprintf(stderr, "intArray_construct: calloc failed\n");
    free(result);
    result = NULL;
    exit(EXIT_FAILURE);
  }
  return result;
}

void intArray_destruct(IntArray *da) {
  if (!da) {
    return;
  }
  free(da->elements);
  da->elements = NULL;
  free(da);
}

void intArray_add(IntArray *da, int d) {
#ifdef DEBUG
  if (!da) {
    fprintf(stderr, "intArray_add: NULL pointer passed\n");
    exit(EXIT_FAILURE);
  }
#endif
  if (da->size == da->capacity) {
    size_t newCapacity = da->capacity * 2;
    int *newElements = realloc(da->elements, newCapacity * sizeof(int));
    if (!newElements) {
      fprintf(stderr, "intArray_add: realloc failed\n");
      exit(EXIT_FAILURE);
    }
    da->elements = newElements;
    da->capacity = newCapacity;
  }
  da->elements[da->size++] = d;
}

void intArray_remove(IntArray *ia, size_t index) {
#ifdef DEBUG
  if (!ia) {
    fprintf(stderr, "intArray_remove: NULL pointer passed\n");
    exit(EXIT_FAILURE);
  }
  if (index >= ia->size) {
    fprintf(stderr, "intArray_remove: index out of bounds\n");
    exit(EXIT_FAILURE);
  }
#endif
  for (size_t i = index; i < ia->size - 1; i++) {
    ia->elements[i] = ia->elements[i + 1];
  }
  ia->size--;
}

// Fisher–Yates shuffle
void intArray_shuffle(IntArray *ia) {
#ifdef DEBUG
  if (!ia) {
    fprintf(stderr, "intArray_shuffle: NULL pointer passed\n");
    exit(EXIT_FAILURE);
  }
#endif
  for (size_t i = ia->size - 1; i > 0; i--) {
    size_t j = rand() % (i + 1); // 0 <= j <= i
    int tmp = ia->elements[i];
    ia->elements[i] = ia->elements[j];
    ia->elements[j] = tmp;
  }
}

void intArray_print(const IntArray *ia) {
  if (!ia) {
    return;
  }
  printf("(");
  for (size_t i = 0; i < ia->size; ++i) {
    printf("%d", ia->elements[i]);
    if (i != ia->size - 1) {
      printf(" ");
    }
  }
  printf(")\n");
}