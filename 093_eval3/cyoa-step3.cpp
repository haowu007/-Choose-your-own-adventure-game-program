//This is the source file for step3
#include "cyoa.cpp"
int main(int argc, char ** argv) {
  if (argc != 2) {  //error handling
    std::cerr << "Usage: please enter one directory name!\n";
    exit(EXIT_FAILURE);
  }

  printStoryDepth(argv[1]);
  return EXIT_SUCCESS;
}
