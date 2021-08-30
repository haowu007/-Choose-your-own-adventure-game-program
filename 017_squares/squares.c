#include <stdio.h>
int between(int x, int a, int b) {
  if (a >= b) {
    return (x >= b && x < a) ? 1 : 0;
  }
  else {
    return (x >= a && x < b) ? 1 : 0;
  }
}

int equal(int x, int a, int b) {
  return ((x == a) || (x == b)) ? 1 : 0;
}

int max(int a, int b) {
  return a > b ? a : b;
}

void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, x_offset + size2);
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, y_offset + size2);
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      if ((between(x, x_offset, x_offset + size2) &&
           equal(y, y_offset, y_offset + size2 - 1)) ||
          (between(y, y_offset, y_offset + size2) &&
           (equal(x, x_offset, x_offset + size2 - 1)))) {
        printf("*");
      }
      else {
        if ((x < size1 && (y == 0 || y == size1 - 1)) ||
            (y < size1 && (x == 0 || x == size1 - 1))) {
          printf("#");
        }
        else {
          printf(" ");
        }
      }
    }
    printf("\n");
  }
  //count from 0 to w. Call the number you count with x

  //check if  EITHER
  //    ((x is between x_offset  and x_offset +size2) AND
  //     y is equal to either y_offset OR y_offset + size2 - 1 )
  //  OR
  //    ((y is between y_offset and y_offset + size2) AND
  //     x is equal to either x_offset OR x_offset + size2 -1)
  // if so, print a *

  //if not,
  // check if EITHER
  //    x is less than size1 AND (y is either 0 or size1-1)
  // OR
  //    y is less than size1 AND (x is either 0 or size1-1)
  //if so, print a #

  //else print a space
  //when you finish counting x from 0 to w,
  //print a newline
}
