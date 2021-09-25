#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';  //char name[64]
  ans.population = 0;  // uint64_t population
  int i = 0;           //i labels the position we are inserting into ans.name[]

  while (*line != ',' && *line != '\0') {
    ans.name[i] = *line;
    i++;
    line++;
  }
  ans.name[i] = '\0';   // add a mark to let program know this is the end of name
  if (*line == '\0') {  //error handling: reach the end without finding the population
    fprintf(stderr, "Failed when trying to find the population data\n");
    exit(EXIT_FAILURE);
  }
  else if (*line == ',') {
    line++;  //read pass the coma
  }
  char popul[40];
  int j = 0;
  if (*line == '\0' || *line == '\n') {
    fprintf(stderr, "No population data!");
    exit(EXIT_FAILURE);
  }
  while (*line != '\n' && *line != '\0') {
    if (*line < '0' || *line > '9') {
      fprintf(stderr, "invalid number!");
      exit(EXIT_FAILURE);
    }
    popul[j] = *line;
    j++;
    line++;
  }
  popul[j] = '\0';  //append a \0 at the end of the char array to make it a valid string
  ans.population = atoi(popul);
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (data == NULL) {
    fprintf(stderr, "filed when trying to find data.\n");
    exit(EXIT_FAILURE);
  }
  if (avg == NULL) {
    fprintf(stderr, "failed when tring to find average array\n");
    exit(EXIT_FAILURE);
  }
  if (n_days < 7) {
    fprintf(stderr, "No enough days to calculate!\n");
    exit(EXIT_FAILURE);
  }
  unsigned * cur_start_day = data;
  unsigned cur_total = 0;
  for (size_t i = 0; i < n_days - 6; i++) {
    cur_total = 0;
    for (int j = 0; j < 7; j++) {
      //printf("The %d th data in this cycle is:%d \n", j, *cur_start_day);
      cur_total += *cur_start_day;
      cur_start_day++;
    }
    *avg = ((double)cur_total) / 7;
    avg++;
    data++;
    cur_start_day = data;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (data == NULL) {
    fprintf(stderr, "filed when trying to find data.\n");
    exit(EXIT_FAILURE);
  }
  if (cum == NULL) {
    fprintf(stderr, "filed when trying to find cumulative array.\n");
    exit(EXIT_FAILURE);
  }
  unsigned sum = 0;
  uint64_t base = pop / 100000;
  for (size_t i = 0; i < n_days; i++) {
    sum += *data;
    *cum = ((double)sum) / base;
    data++;
    cum++;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (n_countries < 1) {
    fprintf(stderr, "No enough countries!");
    exit(EXIT_FAILURE);
  }
  if (n_days < 1) {
    fprintf(stderr, "No enough days!");
    exit(EXIT_FAILURE);
  }
  if (countries == NULL) {
    fprintf(stderr, "No country found!");
    exit(EXIT_FAILURE);
  }
  if (data == NULL) {
    fprintf(stderr, "No data found!");
    exit(EXIT_FAILURE);
  }

  size_t cur_max_country_index = 0;  //
  unsigned cur_max_cases = 0;
  int tie_flag =
      0;  //If tie_flag = 1, there were at least two counties hava the same max cases
  size_t i = 0;
  size_t j = 0;
  unsigned cur_cases = 0;
  char * ans_country = NULL;
  for (i = 0; i < n_countries; i++) {
    for (j = 0; j < n_days; j++) {
      cur_cases = data[i][j];
      if (cur_cases > cur_max_cases) {
        cur_max_cases = cur_cases;
        cur_max_country_index = i;
        tie_flag = 0;
      }
      else if (cur_cases == cur_max_cases) {
        if (cur_max_country_index != i) {
          tie_flag = 1;
        }
      }
    }
  }
  //Traversing of the 2-D Matrix Finished
  ans_country = countries[cur_max_country_index].name;
  if (tie_flag == 1) {
    printf("There is a tie between at leat two countries\n");
  }
  else {
    printf("%s has the most daily cases with %u\n", ans_country, cur_max_cases);
  }
}
