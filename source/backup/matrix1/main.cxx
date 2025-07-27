#include "regression/linearRegression.h"

int main(void) {
  omp_set_num_threads(2);
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();

  // =====write something here=====
  LinearRegression test("red.txt", 0.1, 0.0);
  test.optimize();
  std::cout << "value:" << test.objectiveValue() << std::endl;
  test.output("result.txt");
  //===============================

  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Execution time: " << duration.count() << " ms" << std::endl;
  return 0;
}