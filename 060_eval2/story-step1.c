#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {  //error handilng
    fprintf(stderr, "Please type one input file!\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {  //error handling
    fprintf(stderr, "fopen failed!\n");
    exit(EXIT_FAILURE);
  }

  linesandcats_t * LandC = malloc(sizeof(*LandC));
  if (LandC == NULL) {
    fprintf(stderr, "malloc failed!\n");
    exit(EXIT_FAILURE);
  }
  LandC->lines = NULL;
  LandC->cats = NULL;
  LandC->n = 0;
  parseStoryandchange(f, LandC);
  freelinesandcats(LandC);
  return EXIT_SUCCESS;
}
