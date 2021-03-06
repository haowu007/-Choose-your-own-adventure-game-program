#include "rand_story.h"

//This .cpp file is the interface for step4
int main(int argc, char ** argv) {
  if (argc != 3 && argc != 4) {  //error handling
    fprintf(stderr, "Usage: please type in category/word file and story template file\n");
    exit(EXIT_FAILURE);
  }
  linesandcats_t * LandC = NULL;
  int reuse_enable = 0;
  if (argc == 4) {  // a '-n' option might be typed in
    if (strcmp(argv[1], "-n") == 0) {
      LandC = ParseCategory(argv[2], 0);
      reuse_enable = 0;
      parseStoryandchange(argv[3], LandC, reuse_enable);
    }
    else {  //error handling
      fprintf(stderr, "Usage: please tyoe in '-n' to ban words reusing!");
      exit(EXIT_FAILURE);
    }
  }
  else {  // no '-n' typed in, we do exactly the same work as in step3
    LandC = ParseCategory(argv[1], 0);
    reuse_enable = 1;
    parseStoryandchange(argv[2], LandC, reuse_enable);
  }
  freelinesandcats(LandC);
  return EXIT_SUCCESS;
}
