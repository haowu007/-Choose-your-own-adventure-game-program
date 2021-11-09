#include <iostream>

#include "bstmap.h"

int main(void) {
  BstMap<int, int> * test = new BstMap<int, int>;
  int Nodes[] = {2, 4, 1, 7, 3, 9, -1, 88, 17, -23, 16, 44, 77, 99};
  for (int i = 0; i < 14; i++) {
    test->add(Nodes[i], i);
  }

  test->inorderprint(test->root);
  std::cout << "\n";
  std::cout << "The value of key=7 is " << test->lookup(7);
  try {
    test->lookup(110);  //look up a invalid value
  }
  catch (std::invalid_argument & e) {
    std::cerr << e.what() << std::endl;
  }
  test->remove(2);
  test->inorderprint(test->root);
  std::cout << "\n";
  test->remove(16);
  test->inorderprint(test->root);
  std::cout << "\n";
  test->remove(-1);
  std::cout << "\n";
  test->inorderprint(test->root);
  delete test;
  return EXIT_SUCCESS;
}
