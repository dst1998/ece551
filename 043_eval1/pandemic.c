#include "pandemic.h"

country_t parseLine(char * line) {
  country_t ans;
  char * p = line;
  int i = 0;
  while (*p != ',') {
    ans.name[i] = *p;
    i++;
    p++;
  }
  ans.population = atoi(p);
  // ans.name[0] = '\0';
  //ans.population = 0;
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
