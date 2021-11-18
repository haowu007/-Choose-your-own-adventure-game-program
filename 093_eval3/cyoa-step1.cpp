#include "cyoa.cpp"

int main(int argc, char ** argv) {
  if (argc != 2) {  //Error handling
    std::cerr << "Usage: Please enter one file name!\n";
    exit(EXIT_FAILURE);
  }

  Page page;
  ParsePage(page, argv[1]);
  print_page(page);
  return EXIT_SUCCESS;
}
