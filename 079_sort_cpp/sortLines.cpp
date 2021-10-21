#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
void readFromstdin(void) {
  std::vector<std::string> Myvector;
  std::string s;
  while (getline(std::cin, s)) {
    Myvector.push_back(s);
  }
  if (!std::cin.eof() && !std::cin) {
    std::cerr << "read failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<std::string>::iterator it1 = Myvector.begin();
  std::vector<std::string>::iterator it2 = Myvector.end();
  std::sort(Myvector.begin(), Myvector.end());
  while (it1 != it2) {
    std::cout << *it1 << std::endl;
    ++it1;
  }
}

void readFromfile(char * filename) {
  std::ifstream Mystream;
  Mystream.open(filename);
  if (!Mystream) {
    std::cerr << "open failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<std::string> Myvector;
  std::string s;
  while (getline(Mystream, s)) {
    Myvector.push_back(s);
  }
  std::vector<std::string>::iterator it1 = Myvector.begin();
  std::vector<std::string>::iterator it2 = Myvector.end();
  std::sort(Myvector.begin(), Myvector.end());
  while (it1 != it2) {
    std::cout << *it1 << std::endl;
    ++it1;
  }
  Mystream.close();
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
