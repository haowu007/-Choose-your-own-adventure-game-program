#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "please input ONE string!");
    exit(EXIT_FAILURE);
  }
  char ans[11][10];

  FILE * input_matrix = fopen(argv[1], "r");
  if (input_matrix == NULL) {
    perror("wrong input!fopen failed!");
    fprintf(stderr, "while trying to open %s", argv[1]);
    exit(EXIT_FAILURE);
  }
  int i = 0;
  int j = 9;  // start from ans[0][9] to ans[10][9]
  int cur = 0;
  char cur_char = 'a';  //just trying to give it a initial value
  int count = 0;
  for (j = 9; j >= 0; j--) {
    for (i = 0; i <= 10; i++) {
      if ((cur = fgetc(input_matrix)) != EOF) {
        cur_char = (char)cur;
        if (i == 10 && cur_char != '\n') {
          fprintf(stderr, "no new line character found at the end of row %d !", j);
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
  if ((cur = fgetc(input_matrix)) != EOF) {
    fprintf(stderr, "too more elements!");
    exit(EXIT_FAILURE);
  }

  if (count != 110) {
    //perror("too few elements!");
    fprintf(stderr, "too few elements for %s, only %d elements found \n", argv[1], count);
    exit(EXIT_FAILURE);
  }
  // printf("%d elements added\n", count);
  if (fclose(input_matrix) != 0) {
    perror("fclose failed!");
    fprintf(stderr, "while tring to close %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  //now is time to print out
  for (i = 0; i <= 9; i++) {
    for (j = 0; j <= 9; j++) {
      printf("%c", ans[i][j]);
    }
    printf("\n");
  }
  //  printf("BTW,the last element was: %d", (int)ans[10][0]);
  return EXIT_SUCCESS;
}
