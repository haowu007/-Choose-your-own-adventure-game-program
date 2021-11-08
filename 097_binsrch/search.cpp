#include <cstdlib>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  //base case
  if (high <= low + 1) {
    return low;
  }
  int mid = (low + high) / 2;
  int mid_value = f->invoke(mid);
  if (mid_value == 0) {
    return mid;
  }
  else {
    return (mid_value < 0) ? (binarySearchForZero(f, mid, high))
                           : (binarySearchForZero(f, low, mid));
  }
}
