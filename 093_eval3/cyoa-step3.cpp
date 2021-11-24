//This is the source file for step3
#include "cyoa.cpp"
int main(int argc, char ** argv) {
  if (argc != 2) {  //error handling
    std::cerr << "Usage: please enter one directory name!\n";
    exit(EXIT_FAILURE);
  }
  std::map<size_t, std::vector<size_t> > adj_map;
  size_t num_page = examine_whole_story(argv[1], adj_map);
  printStoryDepth(num_page, adj_map);
  return EXIT_SUCCESS;
}
