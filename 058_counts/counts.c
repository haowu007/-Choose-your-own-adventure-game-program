#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * p = malloc(sizeof(*p));
  if (p == NULL) {
    perror("malloc failed");
    //   exit(EXIT_FAILURE);
    return NULL;
  }
  p->counts_array = NULL;
  p->length = 0;
  p->unknown_count = 0;
  return p;
}
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknown_count++;
    return;
  }
  for (int i = 0; i < c->length; i++) {
    if (strcmp(c->counts_array[i].type, name) == 0) {
      c->counts_array[i].size++;
      return;
    }
  }
  int i = c->length;
  c->counts_array = realloc(c->counts_array, (i + 1) * sizeof(*c->counts_array));
  c->counts_array[i].type = name;
  c->counts_array[i].size = 1;
  c->length++;
}
void printCounts(counts_t * c, FILE * outFile) {
  int * rever = NULL;

  for (int i = 0; i < c->length; i++) {
    for (unsigned long j = 0; j < strlen(c->counts_array[i].type); j++) {
      fputc(c->counts_array[i].type[j], outFile);
    }
    fputc(':', outFile);
    fputc(' ', outFile);
    int n = c->counts_array[i].size;
    int k = 0;
    while (n > 0) {
      rever = realloc(rever, (k + 1) * sizeof(*rever));
      rever[k] = n % 10;
      n /= 10;
      k++;
    }
    for (int l = k - 1; l >= 0; l--) {
      fputc(rever[l] + '0', outFile);
    }
    fputc('\n', outFile);
  }
  if (c->unknown_count != 0) {
    fputs("<unknown> : ", outFile);
    fputc(c->unknown_count + '0', outFile);
    fputc('\n', outFile);
  }

  free(rever);
}

void freeCounts(counts_t * c) {
  /*  for (int i = 0; i < c->length; i++) {
    free(c->counts_array[i].type);
  }
  */
  free(c->counts_array);
  free(c);
}
