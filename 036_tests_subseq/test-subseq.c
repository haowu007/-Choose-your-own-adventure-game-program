#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);

void run_check(int * a, size_t n, size_t ans) {
  if (maxSeq(a, n) != ans) {
    printf("wrong ans with input n=%ld , and ans =%ld !\n", n, ans);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  //  ans = maxSeq(NULL, 0);

  // ans = maxSeq(NULL, 3);
  // ans = maxSeq(NULL, 1);
  //  char chararry[] = {'a', 'b'};
  // ans = maxSeq(chararry, 2);
  // none-valid test cases for the first parameter done
  run_check(NULL, 0, 0);
  int arr01[] = {1};
  run_check(arr01, 1, 1);
  int arr1[] = {1, 2, 3, 4, 5};
  run_check(arr1, 5, 5);
  int arr2[] = {3, 3, 3, 3, 3};
  run_check(arr2, 5, 1);  //all-the-same array
  int arr3[] = {5, 4, 3, 2, 1};
  run_check(arr3, 5, 1);                           //no-increasing array
  int arr4[] = {-1, -2, -1, 0, 1, 2, 3, 2, 1, 1};  //ordinary array
  run_check(arr4, 10, 6);
  int arr5[] = {0, 1, 2, 2, 3, 4, 5, 4, 3, 2, 1};
  run_check(arr5, 11, 4);
  int arr6[] = {1, 2, 2, 3, 4, 5};
  run_check(arr6, 6, 4);
  int arr7[] = {1, 2, 3, 4, 5, 4, 3, 2, 3, 4};
  run_check(arr7, 10, 5);
  return EXIT_SUCCESS;
}
