#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "please input ONE string!");
    exit(EXIT_FAILURE);
  }
  char ans[11][10];

  FILE * input_matrix = fopen(argv[1], "r");
  int i = 0;
  int j = 9;  // start from ans[0][9] to ans[10][9]
  int cur = 0;
  char cur_char;
  int count = 0;  //
  for (j = 9; j >= 0; j--) {
    for (i = 0; i <= 10; i++) {
      if ((cur = fgetc(input_matrix)) != EOF) {
        cur_char = (char)cur;
        if (i == 10 && cur_char != '\n') {
          fprintf(stderr, "no new line character found at the end of row!");
          exit(EXIT_FAILURE);
        }
        if (cur_char == '\n' && i != 10) {
          fprintf(stderr, "did't get enough elements!");
          exit(EXIT_FAILURE);
        }
        ans[i][j] = cur_char;
        count++;
      }
    }
  }
  if (fclose(input_matrix) != 0) {
    perror("fclose failed!");
    fprintf(stderr, "while tring to close %s\n", argv[1]);
  }
  //now is time to print out
  for (i = 0; i <= 9; i++) {
    for (j = 0; j <= 9; j++) {
      printf("%c", ans[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
