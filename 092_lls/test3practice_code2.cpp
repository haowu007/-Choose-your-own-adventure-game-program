#include <cstdlib>
#include <exception>
#include <iostream>

class special_exception : public std::exception {
 public:
  virtual const char * what() { return "special exception\n"; }
};

class X {
 public:
  int x;
  X(int in) : x(in) { std::cout << "X(" << x << ")\n"; }
  ~X() { std::cout << "~X(" << x << ")\n"; }
};

void f(X myX) {
  if (myX.x > 1) {
    throw special_exception();
  }
  else {
    std::cout << "X: " << myX.x << "\n";
  }
}

int main(void) {
  X ans(0);
  for (int i = 0; i < 4; i++) {
    try {
      ans.x++;
      f(ans);
    }

    catch (special_exception & e) {
      std::cout << e.what();
    }
    catch (std::exception & e) {
      std::cout << "standard exception\n";
    }
  }
  return EXIT_SUCCESS;
}
