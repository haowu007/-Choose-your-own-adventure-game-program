#include <stdio.h>
#include <stdlib.h>
void f(int x, int * p, int ** q) {
  x = x + 3;
  *p = **q + x;
  *q = p;
}

int main(void) {
  int a = 3;
  int b = 4;
  int c = 5;
  int * data[] = {&a, &b, &c};
  int ** q = &data[1];
  **q = 99;
  q[0] = q[1];
  printf("a=%d, b=%d, c=%d\n", a, b, c);
  for (int i = 0; i < 3; i++) {
    *data[i] = *data[i] + 11;
  }
  printf("a=%d, b=%d, c=%d\n", a, b, c);
  f(a, &b, &data[2]);
  *q[1] = *q[1] - 3;
  printf("a=%d, b=%d, c=%d\n", a, b, c);
  return EXIT_SUCCESS;
}
