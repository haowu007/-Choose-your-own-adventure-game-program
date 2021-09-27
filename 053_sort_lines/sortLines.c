#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}

//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printFromstdin(void) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t linecap;
  size_t i = 0;
  while (getline(&curr, &linecap, stdin) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    //    printf("the string just read in is:%s\n", lines[i]);
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

void printFromInput(int argc, char ** argv) {
  char * curr = NULL;
  char ** lines = NULL;
  size_t linecap = 0;
  size_t i = 0;
  FILE * f = NULL;
  //  printf("In printFromInput, argc = %d, argv = %s.\n", argc, argv[1]);
  for (int j = 1; j < argc; j++) {
    f = fopen(argv[j], "r");
    if (f == NULL) {
      fprintf(stderr, "failed while open %s\n", argv[j]);
      exit(EXIT_SUCCESS);
    }
    while (getline(&curr, &linecap, f) >= 0) {
      lines = realloc(lines, (i + 1) * sizeof(*lines));
      if (lines == NULL) {
        fprintf(stderr, "realloc failed!\n");
        exit(EXIT_FAILURE);
      }
      lines[i] = curr;
      curr = NULL;
      i++;
    }
    free(curr);
    curr = NULL;
    linecap = 0;
    if (fclose(f) != 0) {
      fprintf(stderr, "while yring to close %s", argv[j]);
      exit(EXIT_SUCCESS);
    }
    f = NULL;
    if (lines == NULL) {
      fprintf(stderr, "no things to sort!\n");
      exit(EXIT_FAILURE);
    }
    sortData(lines, i);
    for (size_t j = 0; j < i; j++) {
      printf("%s", lines[j]);
      free(lines[j]);
    }
    free(lines);
    lines = NULL;
    i = 0;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {  //read from stdin!
    printFromstdin();
  }
  if (argc > 1) {
    //  printf("In main->agrv>1,argc is %d, argv is %s.\n", argc, argv[1]);
    printFromInput(argc, argv);
  }

  return EXIT_SUCCESS;
}
