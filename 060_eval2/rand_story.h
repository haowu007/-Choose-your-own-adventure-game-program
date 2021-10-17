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
  size_t n;
};
typedef struct linesandcats linesandcats_t;

char * getoneline(FILE * f);
void ChangeandPrint(char * c, catarray_t * cats);
void addword(char * name, char * word, catarray_t * cats);
void parseStoryandchange(FILE * f, linesandcats_t * LandC);
void freelinesandcats(linesandcats_t * Landc);
linesandcats_t * ParseCategory(FILE * f, int printflag);

#endif
