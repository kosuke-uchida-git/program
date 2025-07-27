#include "regression/linearRegression.h"

int main(void) {
  struct timespec start, end;

  // 開始時刻を取得
  clock_gettime(CLOCK_MONOTONIC, &start);
  /*omp_set_num_threads(2);
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();*/

  // =====write something here=====
  LinearRegression test("red.txt", 0.1, 0.0);
  test.optimize();
  std::cout << "value:" << test.objectiveValue() << std::endl;
  test.output("result.txt");
  //===============================

  /*
  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Execution time: " << duration.count() << " ms" << std::endl;*/
  // 終了時刻を取得
  clock_gettime(CLOCK_MONOTONIC, &end);

  // 経過時間を計算（ミリ秒）
  uint64_t elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 +
                        (end.tv_nsec - start.tv_nsec) / 1000000;

  printf("Execution time: %lu ms\n", elapsed_ms);
  return 0;
}