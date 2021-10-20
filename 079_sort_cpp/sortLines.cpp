#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
void readFromstdin(void) {
  std::vector<std::string> Myvector;

  while (!std::cin.eof()) {
    std::string s;
    std::cin >> s;
    Myvector.push_back(s);
  }
  std::vector<std::string>::iterator it1 = Myvector.begin();
  std::vector<std::string>::iterator it2 = Myvector.end();
  std::sort(it1, it2);
  while (it1 != it2) {
    std::cout << *it1 << std::endl;
    it1++;
  }
}

void readFromfile(char * filename) {
  std::ifstream Mystream;
  Mystream.open(filename);
  std::vector<std::string> Myvector;

  while (!Mystream.eof()) {
    std::string s;
    Mystream >> s;
    Myvector.push_back(s);
  }
  std::vector<std::string>::iterator it1 = Myvector.begin();
  std::vector<std::string>::iterator it2 = Myvector.end();
  std::sort(it1, it2);
  while (it1 != it2) {
    std::cout << *it1 << std::endl;
    it1++;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    readFromstdin();
  }
  else if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      readFromfile(argv[i]);
    }
  }

  return EXIT_SUCCESS;
}
