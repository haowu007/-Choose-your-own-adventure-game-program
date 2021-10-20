#include "rand_story.h"

//This .cpp file is the interface for step3
int main(int argc, char ** argv) {
  if (argc != 3) {  //error handling
    fprintf(stderr, "Usage: please type in category/word file and story template file\n");
    exit(EXIT_FAILURE);
  }
  linesandcats_t * LandC = NULL;
  int reuse_enable = 0;

  LandC = ParseCategory(argv[1], 0);
  reuse_enable = 1;  // allow words reusing
  parseStoryandchange(argv[2], LandC, reuse_enable);

  freelinesandcats(LandC);
  return EXIT_SUCCESS;
}
