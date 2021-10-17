//#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {  //error handling
    fprintf(stderr, "Please input only one argument!");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {  //error handling
    fprintf(stderr, "fopen failed!");
    exit(EXIT_FAILURE);
  }
  linesandcats_t * LandC = ParseCategory(f, 1);
  freelinesandcats(LandC);
  return EXIT_SUCCESS;
}
