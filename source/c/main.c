#include "process/process.h"

int main(void) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  process();
  clock_gettime(CLOCK_MONOTONIC, &end);
  uint64_t elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 +
                        (end.tv_nsec - start.tv_nsec) / 1000000;
  printf("Execution time: %f sec\n", (double)elapsed_ms / 1000.0);
  return 0;
}
