#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("wrong answer for %d to the power of %d !!\n", x, y);
    exit(EXIT_FAILURE);
  }
  else {
    printf("wow!Right ans!\n");
  }
}

int main(void) {
  run_check(2, 3, 8);
  run_check(1, 10, 1);
  run_check(0, 12, 0);
  run_check(-1, 2, 1);
  run_check(2, 2, 4);
  run_check(2, 5, 32);
  run_check(3, 3, 27);
  run_check(10, 1, 10);
  run_check(0, 0, 1);
  run_check(10, 3, 1000);
  run_check(-10, 4, 10000);
  run_check(3.5, 2.2, 9);
  run_check(0, 1, 0);
  run_check(1, 1, 1);
  run_check(0.5, 2, 0);
  run_check('a', 1, 97);
  run_check(-3, 2, 9);
  run_check(3, 0, 1);
  run_check(99, 1, 99);
  run_check(-1, 1, -1);
  return EXIT_SUCCESS;
}
