#include "rand_story.h"

/*************************DOCUMENT********************************************
Written by: Hao Wu    NetID:hw269
This .cpp file contains 9 functions that might be re-used by more than one steps
They are:
---1---getoneline---Read one single line from input file using 'getline'
---2---contains---Find out if the given category-words table contains the given category
---3---findused---Return a used word indicated by 'index'
---4---throw_a_word---Only used if '-n' was entered;
                   ---Delete a word from the category-words table after it was used
---5---ChangeandPrint---select words from the given categories, and print the result line 
---6---addword---Add a word under the given category
---7---freelinesandcats---Free the malloced spaces for lines and category-words table
---8---ParseStoryandchange---Change the blanks based on the categories they specify
---9---ParseCategory---Form the category-words table
*/

//This function read in one line and free spaces properly
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

//This function returns 1 if 'cats' has the given category; returns 0 otherwise
int contains(catarray_t * cats, char * category) {
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(category, cats->arr[i].name) == 0) {
      return 1;
    }
  }

  return 0;
}

//This function return a used word from used words array based on 'index'
const char * findused(category_t * used_words, long index) {
  size_t i = (size_t)index;
  if (i >= 1 && i <= used_words->n_words) {
    return used_words->words[used_words->n_words - i];
  }
  return NULL;
}

//This function abandon a word that has just been used
void throw_a_word(catarray_t * cats, char * category, const char * changed_word) {
  if (contains(cats, category) ==
      1) {  // We just used a category-determined changing instead of integer-based changing
    for (size_t j = 0; j < cats->n; j++) {
      if (strcmp(cats->arr[j].name, category) == 0) {
        const char ** temp_words = malloc((cats->arr[j].n_words - 1) * sizeof(char *));
        size_t k = 0;
        if (temp_words == NULL) {  //error handling
          fprintf(stderr, "Malloc failed!\n");
          exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < cats->arr[j].n_words; i++) {  //Save the not-used words
          if (strcmp(changed_word, cats->arr[j].words[i]) != 0) {
            temp_words[k] = cats->arr[j].words[i];
            k++;
            cats->arr[j].words[i] = NULL;
          }
        }
        free(cats->arr[j].words);  //free it here in case of memory leak
        cats->arr[j].words = temp_words;
        cats->arr[j].n_words = k;
        break;
      }
    }
  }
}

//This function change all the blanks in one line properly and print the result
void ChangeandPrint(char * c,
                    catarray_t * cats,
                    category_t * used_words,
                    int reuse_enable) {
  char * blank_found = NULL;
  char * blank_pre = NULL;
  char * blank_post = NULL;
  char * category = NULL;
  char * changed_string = NULL;
  size_t len = 0;
  int validnum_flag = 1;
  long used_num_index = 0;
  char buffer[10];
  char * newc = NULL;

  const char * changed_word = NULL;
  while ((blank_found = strchr(c, '_')) != NULL) {
    validnum_flag = 1;
    for (size_t i = 0; i < 10; i++) {  //initialize the buffer
      buffer[i] = 0;
    }
    blank_pre = blank_found;  //ready to find the corresponding post_blank
    *blank_pre = '\0';
    if ((blank_found = strchr(blank_pre + 1, '_')) ==
        NULL) {  //error handling:No mathcing back blank
      fprintf(stderr, "no mathcing post-blank found!\n");
      exit(EXIT_FAILURE);
    }
    blank_post = blank_found;
    *blank_post = '\0';
    category = blank_pre + 1;  //this gives us a C-string of the category
    if (cats == NULL) {        //Only used in step1
      changed_word = chooseWord(category, NULL);
    }
    else {
      len = strlen(category);
      if ((len >= 1 && category[0] != '0') ||
          len == 1) {  //And number that is not 0 can not start by 0
        for (size_t i = 0; i < len; i++) {
          if (category[i] < '0' || category[i] > '9') {
            validnum_flag = 0;  // as long as one bit was not number, the flag will be 0
            break;
          }
        }
      }
      else {
        validnum_flag = 0;  // "012321312..." is not a valid nunber!
      }
      if (validnum_flag == 1) {
        for (size_t i = 0; i < len; i++) {
          buffer[i] = category[i];
        }
        used_num_index = strtol(buffer, NULL, 10);
        changed_word = findused(used_words, used_num_index);
      }
      else {  // the category is not a valid number
        if (contains(cats, category) == 1) {
          changed_word = chooseWord(category, cats);
        }
        else {  //error handling: category is not a valid integer nor a valid category name
          fprintf(stderr, "Category Name invalid!\n");
          exit(EXIT_FAILURE);
        }
      }
      //Now we need to record this selected changed_word choice
      used_words->words =
          realloc(used_words->words, (1 + used_words->n_words) * sizeof(char *));
      used_words->words[used_words->n_words] = changed_word;
      used_words->n_words++;
      //Now we need to remove a word from the data structure if its's still in our caterogies table and resuing words is banned
      if (reuse_enable == 0) {
        throw_a_word(cats, category, changed_word);
      }
    }
    len = strlen(c) + strlen(changed_word) + 10;  //this should be enough!
    changed_string = malloc(len * sizeof(char));
    if (changed_string == NULL) {
      fprintf(stderr, "malloc failed!\n");
      exit(EXIT_FAILURE);
    }
    sprintf(
        changed_string, "%s%s", c, changed_word);  //append the changed_word to the front
    len = strlen(changed_string) + strlen(blank_post + 1) + 1;
    newc = malloc(len * sizeof(*newc));
    sprintf(newc, "%s%s", changed_string, blank_post + 1);  //append the back portion
    free(changed_string);
    free(c);
    c = newc;  //Now we've done with one blank, we go to deal with other blanks in this line
  }
  printf("%s", c);
  free(c);
  return;
}

//This function adds a new word to its category in the given category-words table
void addword(char * name, char * word, catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(name, cats->arr[i].name) ==
        0) {  //The category was already in the cats-table
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

//This function free the malloced spaces for categories table and lines we read from file
void freelinesandcats(linesandcats_t * LandC) {
  for (size_t i = 0; i < LandC->n; i++) {
    free(LandC->lines[i]);
  }
  free(LandC->lines);
  if (LandC->used_words != NULL) {
    free(LandC->used_words->words);
  }
  free(LandC->used_words);
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

//This function is a interface for parsing->change word->print
void parseStoryandchange(char * argv, linesandcats_t * LandC, int reuse_enable) {
  FILE * f = fopen(argv, "r");
  if (f == NULL) {
    fprintf(stderr, "fopen failed!");
    exit(EXIT_FAILURE);
  }
  char * curr = NULL;
  int endflag = 0;  //labels the end of file
  while (endflag == 0) {
    curr = getoneline(f);
    if (curr == NULL) {
      endflag = 1;
      break;
    }
    //now we have read in one line of input
    ChangeandPrint(
        curr,
        LandC->cats,
        LandC->used_words,
        reuse_enable);  //change words for all the 'blanks' in this one line and print the result of these changes
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "fclose failed!\n");
    exit(EXIT_FAILURE);
  }
}

//This function forms a category table based on the input file
linesandcats_t * ParseCategory(char * argv, int printflag) {
  FILE * f = fopen(argv, "r");
  if (f == NULL) {
    fprintf(stderr, "fopen failed!\n");
    exit(EXIT_FAILURE);
  }
  linesandcats_t * linesandcat = malloc(sizeof(*linesandcat));
  catarray_t * cats = malloc(sizeof(*cats));
  category_t * used_words = malloc(sizeof(*used_words));
  used_words->n_words = 0;
  used_words->name = "used";
  used_words->words = NULL;
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
  if (printflag == 1) {  //Only step1 needs this
    printWords(cats);
  }

  linesandcat->cats = cats;
  linesandcat->used_words = used_words;
  linesandcat->lines = lines;
  linesandcat->n = n_lines;
  return linesandcat;  //return the category table and the lines we read in
}
