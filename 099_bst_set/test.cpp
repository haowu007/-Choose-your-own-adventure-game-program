#include <iostream>

#include "bstset.h"

int main(void) {
  BstSet<int> * test = new BstSet<int>;
  int Nodes[] = {2, 4, 1, 7, 3, 9, -1, 88, 17, -23, 16, 44, 77, 99};
  for (int i = 0; i < 14; i++) {
    test->add(Nodes[i]);
  }

  test->inorderprint(test->root);
  std::cout << "\n";

  if (test->contains(17) == true) {
    std::cout << "The set contains 17!\n";
  }
  else {
    std::cout << "The set does not contains 17!\n";
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

  BstSet<int> Apple;
  Apple = *test;

  delete test;
  return EXIT_SUCCESS;
}
