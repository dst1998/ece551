#include "pandemic.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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
  double total = 0;
  for (size_t i = 0; i < n_days - 6; i++) {
    total = 0;
    for (size_t j = 0; j < 7; j++) {
      total += data[i + j];
      // printf("%ud", data[i]);
    }
    avg[i] = total / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  unsigned total = 0;
  for (size_t i = 0; i < n_days; i++) {
    cum[i] = (total + data[i]) * 100000 / pop;
    total += data[i];
    printf("%d", total);
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  unsigned temp = 0;
  size_t x = 0;
  char country_name[64];
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (temp < data[i][j]) {
        temp = data[i][j];
        x = i;
      }
    }
  }
  unsigned number_cases = temp;

  strncpy(country_name, countries[x].name, 64);
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
