#include "rand_story.h"

char * getoneline(FILE * f) {
  ssize_t len = 0;
  size_t sz = 0;
  char * curr = NULL;
  if ((len = getline(&curr, &sz, f)) >= 0) {
    return curr;
  }
  else {
    free(curr);
    return NULL;
  }
}
