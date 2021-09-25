#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>

country_t parseLine(char * line) {
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
  unsigned cur_max_cases = 0;
  unsigned max_of_all = 0;
  int winners = 0;  // If winners >= 2, there is a tie
  size_t i = 0;
  size_t j = 0;
  unsigned cur_cases = 0;
  char * ans_country = NULL;
  unsigned max_within_one_country[n_countries];
  for (i = 0; i < n_countries; i++) {
    max_within_one_country[i] = 0;
  }  //initialize the newly created arry to all zeors

  for (i = 0; i < n_countries; i++) {
    cur_max_cases = 0;
    for (j = 0; j < n_days; j++) {
      cur_cases = data[i][j];
      if (cur_cases > cur_max_cases) {
        cur_max_cases = cur_cases;
        max_within_one_country[i] = cur_max_cases;
      }
      if (cur_cases > max_of_all) {
        max_of_all = cur_cases;
      }
    }
  }
  //Now we have the max daily cases for each country. This is stored in max_within_one_country[]
  for (i = 0; i < n_countries; i++) {
    if (max_within_one_country[i] == max_of_all) {
      ans_country = countries[i].name;
      winners++;
    }
  }
  if (winners > 1) {
    printf("There is a tie between at least two countries");
  }
  else {
    printf("%s has the most daily cases with %u\n", ans_country, max_of_all);
  }
}
