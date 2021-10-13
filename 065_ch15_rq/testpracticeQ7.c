#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct one_line {
  int length;
  char * c;
};

typedef struct one_line one_line;
int contains(one_line * s, size_t m, char * c, int n) {
  for (size_t i = 0; i < m; i++) {
    if (n == s[i].length) {
      if (strcmp(s[i].c, c) == 0) {
        return 1;
      }
    }
  }
  return 0;
}
void freespaces(one_line * l, size_t i) {
  for (size_t j = 0; j < i; j++) {
    printf("%lu succeeded!!!!!\n", j);

    free(l[j].c);
  }
  free(l);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    perror("wrong input number!\n");
    return EXIT_FAILURE;
  }
  ssize_t len = 0;
  char * curr = NULL;
  size_t i = 0;
  one_line * lines = NULL;
  size_t size = 0;
  FILE * f = fopen(argv[1], "r");
  while ((len = getline(&curr, &size, f)) >= 0) {
    if (contains(lines, i, curr, len) != 1) {
      i++;
      lines = realloc(lines, i * sizeof(*lines));
      lines[i - 1].length = len;
      lines[i - 1].c = curr;
      printf("%s", curr);
    }
    else {
      free(curr);  //***************************
    }
    curr = NULL;
    size = 0;
  }
  free(curr);
  fclose(f);
  freespaces(lines, i);
  return EXIT_SUCCESS;
}
