//This is the source file for step3
#include "cyoa.cpp"
int main(int argc, char ** argv) {
  if (argc != 2) {  //error handling
    std::cerr << "Usage: please enter one directory name!\n";
    exit(EXIT_FAILURE);
  }
  std::map<int, std::vector<int> > Adjacency_list;
  size_t num_page = examine_whole_story(argv[1], Adjacency_list);
  std::vector<int> depth_vector(
      num_page - 2, 0);  //because the returned num_page is 2+the real pages number

  return EXIT_SUCCESS;
}
