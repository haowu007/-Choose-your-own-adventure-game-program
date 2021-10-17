#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {  //error handling
    fprintf(stderr, "Usage: please type in category/word file and story template file\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "fopen failed!");
    exit(EXIT_FAILURE);
  }
  linesandcats_t * LandC = ParseCategory(f, 0);
  if (fclose(f) != 0) {  //error handling
    fprintf(stderr, "fclose failed!\n");
    exit(EXIT_FAILURE);
  }

  freelinesandcats(LandC);
  return EXIT_SUCCESS;
}
