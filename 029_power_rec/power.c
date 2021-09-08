#include <stdio.h>
#include <stdlib.h>
unsigned int power_helper(unsigned x, unsigned y, unsigned ans);
unsigned int power(unsigned x, unsigned y) {
  return power_helper(x, y, 1);
}

unsigned int power_helper(unsigned x, unsigned y, unsigned ans) {
  if (y == 0) {
    return ans;
  }
  return (power_helper(x, y - 1, ans * x));
}

int main(void) {
  printf("3 to the pow of 4 is %u\n", power(3, 4));
  printf("0 to the pow of 0 is %u\n", power(0, 0));
  printf("-1 to the pow of 3 is %d\n", power(-1, 3));
  printf("7 to the pow of 2 is %u\n", power(7, 2));
  return EXIT_SUCCESS;
}
