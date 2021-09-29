#include "pandemic.h"

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//typedef unsigned long int       uint64_t;

country_t parseLine(char * line) {
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  char * p = line;
  int i = 0;
  //int cnt = 0;
  /*while (*p != '\0') {
    while (*p == ',') {
      cnt++;
      p++;
    }
    p++;
  }
  if (cnt != 1) {
    printf("Wrong number of ','.\n");
    exit(EXIT_FAILURE);
  }
  */
  p = line;
  while (*p != ',') {
    ans.name[i] = (*p);
    // printf("%c", *p);
    i++;
    if (i == 64) {
      perror("Courntry name is too long.\n");
      exit(EXIT_FAILURE);
    }
    p++;
  }
  ans.name[i] = '\0';
  p++;
  while (*p == ' ') {
    p++;
  }
  if ((*p < 48 || *p > 57) && *p != 45) {  //45 is "-"
    perror("Wrong input of population.\n");
    exit(EXIT_FAILURE);
  }
  if (*p >= 48 && *p <= 57) {
    ans.population = strtoul(p, NULL, 10);
    //printf("Correct!");  //
    return ans;
  }
  //*p==45
  p++;
  if (*p < 48 || *p > 57) {
    perror("Wrong input of population.\n");
    exit(EXIT_FAILURE);
  }
  ans.population = (uint64_t)(0 - strtoul(p, NULL, 10));
  // printf("Correct!");  //
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  /*if (data == NULL) {
    printf("Could not open file.\n");
    exit(EXIT_FAILURE);
    }*/
  if (n_days <= 6) {
    return;
  }
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
  if (data == NULL) {
    printf("Could not open file.\n");
    exit(EXIT_FAILURE);
  }
  if (!n_days) {
    printf("Wrong number of day.\n");
    exit(EXIT_FAILURE);
  }
  unsigned total = 0;
  for (size_t i = 0; i < n_days; i++) {
    cum[i] = (total + data[i]) / (double)pop * 100000;
    total += data[i];
    // printf("%d", total);
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  if (data == NULL) {
    printf("Could not open file.\n");
    exit(EXIT_FAILURE);
  }
  if (!n_days || !n_countries) {
    return;
  }
  unsigned temp = 0;
  size_t x = 0;
  char country_name[64];
  unsigned same = 0;
  int xdiffe = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (temp < data[i][j]) {
        temp = data[i][j];
        x = i;
        continue;
      }
      if (temp == data[i][j]) {
        same = temp;
        if (i != x) {
          xdiffe = 1;
        }
      }
    }
  }
  if ((temp == same) && xdiffe) {
    printf("There is a tie between at least two countries");
    return;
  }
  unsigned number_cases = temp;
  strncpy(country_name, countries[x].name, 64);
  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
