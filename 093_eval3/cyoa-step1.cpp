#include "cyoa.cpp"

int main(int argc, char ** argv) {
  if (argc != 2) {  //Error handling
    std::cerr << "Usage: Please enter one file name!\n";
    exit(EXIT_FAILURE);
  }
  std::set<size_t> pages_set;
  Page page;

  int flag = ParsePage(page, argv[1], pages_set);
  if (flag == -1) {
    std::cerr << "Invalid file name!\n";
    exit(EXIT_FAILURE);
  }
  print_page(page);
  return EXIT_SUCCESS;
}
