#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>

// **************DOCUMENT:***************
// Written by: Hao Wu    NetID: hw269
// In this program, I wrote four functions about dealing with Covid-19 cases data.
// ---1---parseLine()---
//   This function take in a complete line as input, and seperate them into two parts: The country's name and its population.
//   The key process is finding the comma indicating the two parts. It can give us the population information about countries.
// ---2---calcRunningAvg()---
//   This function calculates the running average of daily cases from different countries. The range was chosen to be 7 days.
// ---3---calcCumulative()---
//   This function calculates the cumulative data for countries. A cumulative data means to sum up all the cases reported
//   since the starting date, and measure the cases using a base of 10,000 people from the population.
//---4---printCountryWithMax()---
//   This function finds the country that has the max daily cases among all the reported data.
//Error handling: If any invalid input is found during the process, we exit immediatly with proper error message.
//***************************************

country_t parseLine(char * line) {
  country_t
      ans;  //short for "answer", represents the country we need to parse information for
  ans.name[0] = '\0';  //char name[64] ; initialize it with \0
  ans.population = 0;  // uint64_t population ; initialize it with 0
  int i = 0;           //i labels the position where we are inserting into ans.name[]
  char popul[40];      //stores the population information, wait to transfer to integer
  int j = 0;           //j labels the position where we are reading in population
  while (*line != ',' && *line != '\0') {  //Keep parsing the country's name
    ans.name[i] = *line;                   //parsing one character
    i++;                                   //move to the next character
    line++;                                //move to the next character
  }
  ans.name[i] = '\0';   // add a mark to let program know this is the end of name
  if (*line == '\0') {  //error handling: reach the end without finding the population
    fprintf(stderr, "Failed when trying to find the population data\n");
    exit(EXIT_FAILURE);
  }
  else if (*line == ',') {
    line++;  //read pass the comma
  }
  if (*line == '\0' || *line == '\n') {  //error handling: no population number found
    fprintf(stderr, "No population data!");
    exit(EXIT_FAILURE);
  }
  if (*line == '-') {  //nagative number!
    popul[j] = *line;
    j++;
    line++;
  }
  if (*line < '0' || *line > '9') {  //no number at all!
    fprintf(stderr, "No numbers!\n");
    exit(EXIT_FAILURE);
  }
  while (*line != '\n' && *line != '\0') {  //Keep reading in population information
    if (*line < '0' || *line > '9') {
      break;
    }
    popul[j] = *line;
    j++;
    line++;
  }
  popul[j] = '\0';  //append a \0 at the end of the char array to make it a valid string
  ans.population = atoi(popul);  // ascii(char) to integer
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  unsigned * cur_start_day = data;  //the starting day's data in 7-day-group
  unsigned cur_total = 0;           //the cases's sum so far in this 7-day-group
  if (data == NULL) {               //error handling: no data found
    fprintf(stderr, "filed when trying to find data.\n");
    exit(EXIT_FAILURE);
  }
  if (avg == NULL) {  //error handling: no destination array found
    fprintf(stderr, "failed when tring to find average array\n");
    exit(EXIT_FAILURE);
  }
  if (n_days < 7) {  //error handling: too few day for a 7-day-average
    fprintf(stderr, "No enough days to calculate!\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < n_days - 6; i++) {
    cur_total = 0;  //for each 7-day-group, add up the cases number from zero
    for (int j = 0; j < 7; j++) {
      cur_total += *cur_start_day;
      cur_start_day++;
    }
    *avg = ((double)cur_total) / 7;  //calculate the average
    avg++;
    data++;
    cur_start_day = data;  //move on to the next 7-day-group starting at the next day
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  unsigned sum = 0;                      // the sum of all the cases counted till now
  double base = ((double)pop) / 100000;  //do some preparation work for later
  if (data == NULL) {                    //error handling: input is  NULL pointer
    fprintf(stderr, "filed when trying to find data.\n");
    exit(EXIT_FAILURE);
  }
  if (cum == NULL) {  //error handling: input is NULL pointer
    fprintf(stderr, "filed when trying to find cumulative array.\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < n_days; i++) {
    sum += *data;
    *cum =
        (double)(sum /
                 base);  //not sure which one of unsigned and double will covert to the other. Since googling is not allowed
                         //, I'd better explicitly  convert it to double myself
    data++;
    cum++;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  unsigned cur_max_cases = 0;  //the max case number currently found for a given country
  unsigned max_of_all = 0;     //the max case number for all data
  int winners = 0;             // If winners >= 2, there is a tie
  size_t i = 0;                //iterate on all countries
  size_t j = 0;                //iteratre on all days
  unsigned cur_cases =
      0;  //the case number for the currently processing day for a given country
  char * ans_country = NULL;   //the name for the country that had the max data
  unsigned maxs[n_countries];  //maxs[i] stores the max cases for the (i+1)th country
  if (n_countries < 1 || n_days < 1) {
    return;
  }
  if (countries == NULL) {  // error handling: NULL input
    fprintf(stderr, "No country found!");
    exit(EXIT_FAILURE);
  }
  if (data == NULL) {  //error handling: NULL input
    fprintf(stderr, "No data found!");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < n_countries; i++) {  //initialize the newly created array
    maxs[i] = 0;
  }
  for (i = 0; i < n_countries; i++) {
    cur_max_cases = 0;
    for (j = 0; j < n_days; j++) {
      cur_cases = data[i][j];
      if (cur_cases > cur_max_cases) {
        cur_max_cases =
            cur_cases;            //renew the currently found max number for this country
        maxs[i] = cur_max_cases;  //store the newly found max number in the array
      }
      if (cur_cases > max_of_all) {  //renew the max_of_all data
        max_of_all = cur_cases;
      }
    }
  }
  //Now we have the max daily cases for each country. This is stored in the array maxs[]
  for (i = 0; i < n_countries; i++) {
    if (maxs[i] == max_of_all) {
      ans_country = countries[i].name;
      winners++;
    }
  }
  if (winners > 1) {  //Tie exists.
    printf("There is a tie between at least two countries");
  }
  else {
    printf("%s has the most daily cases with %u\n", ans_country, max_of_all);
  }
}
