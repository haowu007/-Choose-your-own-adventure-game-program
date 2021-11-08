#include <cmath>
#include <cstdlib>
#include <ctgmath>
#include <iostream>

#include "function.h"
int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class Myfunction : public Function<int, int> {
 public:
  virtual int invoke(int x) { return x * 2 + 4; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned max_invoke = (high - low > 0) ? (log2(high - low) + 1) : 1;
  Function<int, int> * C1 = new CountedIntFn(max_invoke, f, mesg);
  int result_of_BS = binarySearchForZero(C1, low, high);
  if (result_of_BS != expected_ans) {
    std::cout << "The answer of Binary search is incorrect for " << mesg << std::endl;
    exit(EXIT_FAILURE);
  }
  delete C1;
}

int main(void) {
  Myfunction * f = new Myfunction;

  check(f, 1, 9, 1, "Test case 1");  //f(x) >=6,so 0 is not in our range,return 'low'
  check(f,
        -10,
        100,
        -2,
        "Test case 2");  //we do have f(-2)=0  in our range and -2 is in the middle
  check(f,
        -10,
        -1,
        -2,
        "Test case 3");  //We do have f(-2)=0 in our range and -2 is 'high'-1
  check(f,
        -10,
        -2,
        -3,
        "Test case 4");  //We did not have f(-2)=0 in our range but have -3 in range
  check(f, -2, 101, -2, "Test case 5");  //We do have f(-2)=0 in our range and -2 is 'low'
  check(f, -1, 40, -1, "Test case 6");   //We do not have -2 in our range but have -1
  check(f,
        -10,
        -6,
        -7,
        "Test case 6");  // f(x)<=-10, so 0 is not in our range, return 'high-1'
  check(f, 3, 3, 3, "Test case 7");     // We try low=high
  check(f, -2, -1, -2, "Test case 8");  //we try low = high+1

  delete f;
  return EXIT_SUCCESS;
}
