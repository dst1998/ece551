#include <stdio.h>
#include <stdlib.h>
struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double balance(int startage, double initial, retire_info x) {
  double bala = initial;
  for (int i = 0; i < x.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n",
           (startage + i) / 12,
           (startage + i) % 12,
           bala);
    bala = bala * (1 + x.rate_of_return) + x.contribution;
  }
  return bala;
}
void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double new_ini = balance(startAge, initial, working);
  balance(startAge + working.months, new_ini, retired);
}

int main(void) {
  retire_info working, retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  retirement(327, 21345, working, retired);
  return 0;
}
