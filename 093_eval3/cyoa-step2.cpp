//This is the source file for step2
#include "cyoa.cpp"
int main(int argc, char ** argv) {
  if (argc != 2) {  //error handling
    std::cerr << "Usage: please enter one directory name!\n";
    exit(EXIT_FAILURE);
  }
  Useful_infor UI;
  size_t num_page =
      examine_whole_story(argv[1], UI);  //Do all the checkings before reading

  ReadaStory(argv[1], num_page);  //Let the player read the story
  return EXIT_SUCCESS;
}
