#include "math.h"

bool isInteger(const double a) { return a == std::floor(a); }

int sign(const double a) {
  if (a > 0) {
    return 1;
  }
  if (a < 0) {
    return -1;
  }
  return 0;
}