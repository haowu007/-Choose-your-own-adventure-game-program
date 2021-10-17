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

void ChangeandPrint(char * c, catarray_t * cats) {
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
    changed_word = chooseWord((category), cats);

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

void freelinesandcats(linesandcats_t * LandC) {
  for (size_t i = 0; i < LandC->n; i++) {
    free(LandC->lines[i]);
  }
  free(LandC->lines);
  if (LandC->cats !=
      NULL) {  //We need special handles for story-step1!(in which case cats is NULL)
    for (size_t i = 0; i < LandC->cats->n; i++) {
      free(LandC->cats->arr[i].words);
    }
    free(LandC->cats->arr);
  }
  free(LandC->cats);
  free(LandC);
}

void parseStoryandchange(FILE * f, linesandcats_t * LandC) {
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
        curr,
        LandC
            ->cats);  //change words for all the 'blanks' in this one line and print the result of these changes
    free(curr);  //After print, this line is of no use now, so we free the space
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "fclose failed!\n");
    exit(EXIT_FAILURE);
  }
}

linesandcats_t * ParseCategory(FILE * f, int printflag) {
  linesandcats_t * linesandcat = malloc(sizeof(*linesandcat));
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
  if (printflag == 1) {
    printWords(cats);
  }

  linesandcat->cats = cats;
  linesandcat->lines = lines;
  linesandcat->n = n_lines;
  return linesandcat;
}
