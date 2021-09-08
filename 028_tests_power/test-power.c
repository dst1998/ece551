#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
int run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans == expected_ans) {
    printf("Corrrect! x=%d, y=%d, answer is %d\n", x, y, expected_ans);
    return EXIT_SUCCESS;
  }
  printf("Wrong! x=%d, y=%d, your answer is %d\n", x, y, ans);
  exit(EXIT_FAILURE);
}

int main(void) {
  run_check(2, 3, 8);
  run_check(2, 5, 32);
  run_check(0, 0, 1);
  run_check(2, 0, 1);
  run_check(1, 1000000000, 1);
  run_check(5, 2, 25);
  run_check(1000000, 1, 1000000);
  run_check(1, 100, 1);
  run_check(10, 4, 10000);
  return EXIT_SUCCESS;
}
