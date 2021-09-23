#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int break_function(FILE * f) {
  int c;
  int count_array[26];
  for (int i = 0; i <= 25; i++) {
    count_array[i] = 0;
  }
  int count;
  while ((c = fgetc(f)) != EOF) {
    count++;
    //    printf("we are in the while! c is %c!\n", c);
    if (isalpha(c)) {
      // printf("we are in the if!\n");
      c = tolower(c);
      //      printf("c is %d\n", c);
      c = c - 'a';
      count_array[c]++;
    }
  }
  int MAX_frequency = 0;
  int max_label = -1;
  for (int i = 0; i < 26; i++) {
    if (count_array[i] > MAX_frequency) {
      MAX_frequency = count_array[i];
      max_label = i;
    }
  }
  if (count == 0) {
    return -1;
  }
  return (max_label >= 4) ? (max_label - 4) : max_label + 22;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Please input the file name!");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Cound not open file");
    return EXIT_FAILURE;
  }
  int ans = 0;
  ans = break_function(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  if (ans != -1) {
    printf("%d\n", ans);
  }
  return EXIT_SUCCESS;
}
