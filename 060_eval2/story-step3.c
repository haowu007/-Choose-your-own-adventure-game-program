#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {  //error handling
    fprintf(stderr, "Usage: please type in category/word file and story template file\n");
    exit(EXIT_FAILURE);
  }
  linesandcats_t * LandC = ParseCategory(argv[1], 0);
  parseStoryandchange(argv[2], LandC);
  freelinesandcats(LandC);
  return EXIT_SUCCESS;
}
