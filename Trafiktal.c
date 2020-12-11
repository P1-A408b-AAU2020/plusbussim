#include <stdio.h>
#define SECONDS_PER_DAY 86400
#define SECONDS_PER_TIMESTEP 1.667
#define TIMESTEPS_PER_DAY SECONDS_PER_DAY * SECONDS_PER_TIMESTEP
double chance_for_traffic();

int main() {
  char run_again;
  printf("%f%%\n", chance_for_traffic());
  printf("New calculation? (y/n)\n");
  scanf(" %c", &run_again);
  while (run_again == 'y' || run_again == 'Y') {
    printf("%f%%\n", chance_for_traffic());
    printf("New calculation? (y/n)\n");
    scanf(" %c", &run_again);
  }
  return 0;
}

double chance_for_traffic() {
  double number_of_cars_per_day;
  printf("enter number of cars\n");
  scanf(" %lf", &number_of_cars_per_day);
  return (number_of_cars_per_day / TIMESTEPS_PER_DAY) * 100;
}

