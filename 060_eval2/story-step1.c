#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

//This .cpp file is the interface for step1
int main(int argc, char ** argv) {
  if (argc != 2) {  //error handilng
    fprintf(stderr, "Please type one input file!\n");
    exit(EXIT_FAILURE);
  }

  linesandcats_t * LandC = malloc(sizeof(*LandC));
  if (LandC == NULL) {
    fprintf(stderr, "malloc failed!\n");
    exit(EXIT_FAILURE);
  }
  LandC->lines = NULL;
  LandC->cats = NULL;
  LandC->used_words = NULL;
  LandC->n = 0;
  int reuse_enable = 1;  //Allow reusing words
  parseStoryandchange(argv[1], LandC, reuse_enable);
  freelinesandcats(LandC);
  return EXIT_SUCCESS;
}
