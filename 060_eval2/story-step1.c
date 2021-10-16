#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

void ChangeandPrint(char * c) {
  char * blank_found = NULL;
  char * blank_pre = NULL;
  char * blank_post = NULL;
  char * category = NULL;
  char * changed_string = NULL;
  size_t len = 0;

  const char * changed_word = NULL;
  while ((blank_found = strchr(c, '_')) != NULL) {
    blank_pre = blank_found;  //ready to find the corresponding post_blank
    *blank_pre = '\0';
    if ((blank_found = strchr(blank_pre + 1, '_')) ==
        NULL) {  //error handling:No mathcing back blank
      fprintf(stderr, "no mathcing post-blank found!\n");
      exit(EXIT_FAILURE);
    }
    blank_post = blank_found;
    *blank_post = '\0';
    category = blank_pre++;
    changed_word = chooseWord((category), NULL);

    len = strlen(c) + strlen(changed_word) + 5;  //this should be enough!
    changed_string = malloc(len * sizeof(char));
    if (changed_string == NULL) {
      fprintf(stderr, "malloc failed!\n");
      exit(EXIT_FAILURE);
    }
    snprintf(changed_string, len, "%s%s", c, changed_word);

    len = strlen(changed_string) + strlen(blank_post + 1) + 5;
    snprintf(c, len, "%s%s", changed_string, blank_post + 1);
    free(changed_string);
  }

  printf("%s", c);

  return;
}

int main(int argc, char ** argv) {
  if (argc != 2) {  //error handilng
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {  //error handling
  }
  char * curr = NULL;
  int endflag = 0;
  while (endflag == 0) {
    curr = getoneline(f);
    if (curr == NULL) {
      endflag = 1;
      break;
    }
    //now we have read in one line of input
    ChangeandPrint(
        curr);  //change words for all the 'blanks' in this one line and print the result of these changes
    free(curr);  //After print, this line is of no use now, so we free the space
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "fclose failed!\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
