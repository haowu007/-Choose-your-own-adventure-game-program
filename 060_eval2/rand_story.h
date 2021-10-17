
#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
//any functions you want your main to use

struct linesandcats {
  char ** lines;
  catarray_t * cats;
  category_t * used_words;
  size_t n;
};
typedef struct linesandcats linesandcats_t;

char * getoneline(FILE * f);
int contains(catarray_t * cats, char * category);
void throw_a_word(catarray_t * cats, char * category, const char * changed_word);
void ChangeandPrint(char * c,
                    catarray_t * cats,
                    category_t * used_words,
                    int reuse_enable);
void addword(char * name, char * word, catarray_t * cats);
void parseStoryandchange(char * argv, linesandcats_t * LandC, int reuse_enable);
void freelinesandcats(linesandcats_t * Landc);
linesandcats_t * ParseCategory(char * argv, int printflag);

#endif
