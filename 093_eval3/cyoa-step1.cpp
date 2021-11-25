#include "cyoa.cpp"

int main(int argc, char ** argv) {
  if (argc != 2) {  //Error handling
    std::cerr << "Usage: Please enter one file name!\n";
    exit(EXIT_FAILURE);
  }

  Page page;
  std::map<size_t, std::vector<size_t> > adj_map;
  size_t max_choice = 0;
  int flag = ParsePage(page, argv[1], adj_map, 0, max_choice);
  if (flag == -1) {
    std::cerr << "Invalid file name!\n";
    exit(EXIT_FAILURE);
  }
  page.print_page();
  return EXIT_SUCCESS;
}
