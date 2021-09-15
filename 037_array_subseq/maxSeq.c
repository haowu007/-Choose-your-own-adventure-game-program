#include <stdlib.h>

size_t max(size_t a, size_t b) {
  return a > b ? a : b;
}

size_t maxSeq(int * a, size_t n) {
  if (a == NULL || n <= 0) {
    return 0;
  }
  size_t ans = 1;
  size_t cur = 1;
  for (int i = 1; i < n; i++) {
    if (a[i] > a[i - 1]) {
      cur++;
    }
    else {
      ans = max(ans, cur);
      cur = 1;
    }
  }

  ans = max(ans, cur);
  return ans;
}
