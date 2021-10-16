#include <string.h>

#include "rand_story.h"

void addword(char * name, char * word, catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(name, cats->arr[i].name) == 0) {
      cats->arr[i].words =
          realloc(cats->arr[i].words, (cats->arr[i].n_words + 1) * sizeof(char *));
      cats->arr[i].words[cats->arr[i].n_words] = word;
      cats->arr[i].n_words++;
      return;
    }
  }
  //we have not seen this name before
  cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
  cats->arr[cats->n].name = name;
  cats->arr[cats->n].words = malloc(sizeof(char *));
  cats->arr[cats->n].words[0] = word;
  cats->arr[cats->n].n_words = 1;
  cats->n++;
  return;
}

void freelines(char ** lines, size_t n) {
  for (size_t i = 0; i < n; i++) {
    free(lines[i]);
  }
  free(lines);
}

void freecats(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    free(cats->arr[i].words);
  }
  free(cats->arr);
  free(cats);
}

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

  catarray_t * cats = malloc(sizeof(*cats));
  cats->n = 0;
  cats->arr = NULL;
  char ** lines = NULL;
  size_t n_lines = 0;
  char * curr = NULL;
  char * word = NULL;
  while ((curr = getoneline(f)) != NULL) {
    lines = realloc(lines, (n_lines + 1) * sizeof(*lines));
    lines[n_lines] = curr;
    n_lines++;
    size_t len = strlen(curr);
    curr[len - 1] = '\0';  // no need to keep the '\n' at the end of line

    char * colon_position = strchr(curr, ':');
    if (colon_position == NULL) {  //error handling
      fprintf(stderr, "No colon found!!");
      exit(EXIT_FAILURE);
    }
    *colon_position = '\0';
    word = colon_position + 1;
    addword(curr, word, cats);
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "fclose failed!");
    exit(EXIT_FAILURE);
  }
  printWords(cats);
  freelines(lines, n_lines);
  freecats(cats);
  return EXIT_SUCCESS;
}
