#include <cstdlib>
#include <iostream>

class A {
 public:
  int x;
  A(int x_) : x(x_) { pr(); }
  virtual void pr() { std::cout << "A:" << x << "\n"; }
};

class B : public A {
 public:
  B(int x_) : A(x_) { pr(); }
  virtual void pr() { std::cout << "B:" << x << "\n"; }
};

int & f(A * ptr) {
  ptr->x++;
  ptr->pr();
  return ptr->x;
}

int main(void) {
  A ** arr = new A *[4];
  arr[0] = new A(3);
  arr[1] = new B(7);
  arr[2] = arr[1];
  for (int i = 0; i < 3; i++) {
    int & y = f(arr[i]);
    y *= 2;
    arr[i]->pr();
  }
  return EXIT_SUCCESS;
}
