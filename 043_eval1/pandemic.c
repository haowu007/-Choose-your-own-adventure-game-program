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
  if (*line == '\0') {  //error handling: reach the end without finding the population
  }
  else if (*line == ',') {
    line++;  //read pass the coma
  }
  char popul[40];
  int j = 0;
  while (*line != '\0') {
    if (*line < '0' || *line > '9') {  //error handling: non-valid-number found}
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
