#include "pandemic.h"

#include "stdio.h"
#include "stdlib.h"

country_t parseLine(char * line) {
  country_t ans;
  char * p = line;
  int i = 0;
  while (*p != ',') {
    ans.name[i] = (*p);
    // printf("%c", *p);
    i++;
    p++;
  }
  ans.name[i] = '\0';
  p++;
  ans.population = atoi(p);
  //printf("\n");
  // ans.name[0] = '\0';
  //ans.population = 0;
  //if... return EXIT_FAILURE;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //char * p = data;
  unsigned total = 0;
  for (size_t i = 0; i < n_days - 6; i++) {
    total = 0;
    for (size_t j = 0; j < n_days; j++) {
      total = data[i + j];
      // printf("%ud", data[i]);
    }
    avg[i] = total / n_days;
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
