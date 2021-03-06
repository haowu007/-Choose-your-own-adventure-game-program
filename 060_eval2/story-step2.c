//#include <string.h>

#include "rand_story.h"

//This .cpp file is the interface for step2
int main(int argc, char ** argv) {
  if (argc != 2) {  //error handling
    fprintf(stderr, "Please input only one argument!");
    exit(EXIT_FAILURE);
  }
  linesandcats_t * LandC = ParseCategory(argv[1], 1);
  freelinesandcats(LandC);
  return EXIT_SUCCESS;
}
