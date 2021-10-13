#include <stdio.h>
#include <stdlib.h>

int findLargestDifference(int * a1, int * a2, size_t n) {
  if (n == 0) {
    return 0;
  }
  int max_diff = 0;
  int cur_diff = 0;
  for (size_t i = 0; i < n; i++) {
    cur_diff = a1[i] - a2[i];
    max_diff = (cur_diff > max_diff) ? cur_diff : max_diff;
  }
  return max_diff;
}

int main(void) {
  int a1[] = {1, 4, 6, 7, 9};
  int a2[] = {7, 5, 1, 3, 8};
  printf("The ans is %d \n", findLargestDifference(a1, a2, 5));
  return EXIT_SUCCESS;
}
