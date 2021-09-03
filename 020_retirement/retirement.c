

#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

typedef struct info_t {
  double saving;
  int age;
} info;

info compute(int startAge, double initial, retire_info working, int retire_flag) {
  int current_age = 0;
  //if flag is 1, meaning I have retired, no need to repeat the beginning saving anymore.
  for (int i = retire_flag; i < working.months + retire_flag; i++) {
    current_age = startAge + i;
    //   int mon = startAge % 12;

    printf("Age %3d month %2d you have $%.2lf\n",
           current_age / 12,
           current_age % 12,
           initial);
    initial += working.contribution + initial * working.rate_of_return;
  }
  info in;
  in.saving = initial;
  in.age = current_age;
  return in;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  info in1 = compute(startAge, initial, working, 0);
  info in2 = compute(in1.age, in1.saving, retired, 1);
  in2.saving++;  //simply because we don't want money2 to be unused variable
}
int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;

  retired.rate_of_return = 0.01 / 12;
  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}
