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
  while (*line != '\0') {
    // if (*line < '0' || *line > '9') {  //error handling: non-valid-number found
    //  fprintf(stderr, "Non-valid-number found!\n");
    //  exit(EXIT_FAILURE);
    // }
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
    perror("data not found!\n");
    fprintf(stderr, "filed when trying to find data.\n");
    exit(EXIT_FAILURE);
  }
  if (avg == NULL) {
    perror("no where to store average!\n");
    fprintf(stderr, "failed when tring to find average array\n");
    exit(EXIT_FAILURE);
  }
  if (n_days < 7) {
    perror("to few days!\n");
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
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
