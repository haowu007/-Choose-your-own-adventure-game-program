#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readaKey(FILE * f, kvarray_t * a, int i) {
  int c = 0;
  char cur = '0';
  int j = 0;
  while ((c = fgetc(f)) != EOF) {
    cur = (char)c;
    if (cur == '\n') {
      fprintf(stderr, "found new line character when loading KEY!!\n");
      return -1;
    }
    a->kvarray[i].key =
        realloc(a->kvarray[i].key, (j + 1) * sizeof(*(a->kvarray[i].key)));
    if (a->kvarray[a->length].key == NULL) {
      fprintf(stderr, "falied reallocating space for key!\n");
      return 0;
    }
    if (cur == '=') {
      a->kvarray[i].key[j] = '\0';
      return 0;
    }
    else {
      a->kvarray[i].key[j] = cur;
      j++;
    }
  }
  return (j == 0) ? 1 : -1;  // end of file found!
}

void readaValue(FILE * f, kvarray_t * a, int i) {
  int c = 0;
  char cur = '0';
  int j = 0;
  while ((c = fgetc(f)) != EOF) {
    cur = (char)c;
    a->kvarray[i].value =
        realloc(a->kvarray[i].value, (j + 1) * sizeof(*(a->kvarray[i].value)));
    if (a->kvarray[i].value == NULL) {
      fprintf(stderr, "Falied realloc space for value!\n");
      return;
    }
    if (cur == '\n') {
      a->kvarray[i].value[j] = '\0';
      return;
    }
    else {
      a->kvarray[i].value[j] = cur;
      j++;
    }
  }

  return;
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Failed open file!");
    //  exit(EXIT_FAILURE);
    return NULL;  // could not open file
  }
  kvarray_t * ans = malloc(sizeof(*ans));
  if (ans == NULL) {
    return NULL;
  }
  ans->kvarray = NULL;
  ans->length = 0;
  int endflag = 0;
  int i = 0;
  while (1) {
    ans->kvarray = realloc(ans->kvarray, (i + 1) * sizeof(*ans->kvarray));
    if (ans->kvarray == NULL) {
      return NULL;
    }
    ans->kvarray[i].key = NULL;
    ans->kvarray[i].value = NULL;
    endflag = readaKey(f, ans, i);
    if (endflag == 1) {
      free(ans->kvarray[i].key);
      break;
    }
    if (endflag == -1) {
      fprintf(stderr, "Reach end of file when loeading some KEY!!\n");
      return NULL;
    }
    readaValue(f, ans, i);
    i++;
    ans->length = i;
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed when closing the file!");
    return NULL;
  }
  return ans;
}

void freeKVs(kvarray_t * pairs) {
  int n = pairs->length;
  for (int i = 0; i < n; i++) {
    free(pairs->kvarray[i].key);
    free(pairs->kvarray[i].value);
  }
  free(pairs->kvarray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvarray[i].key, pairs->kvarray[i].value);
  }
  return;
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (int i = 0; i < pairs->length; i++) {
    if (strcmp(key, pairs->kvarray[i].key) == 0) {
      return pairs->kvarray[i].value;
    }
  }
  return NULL;
}
