#include "debug.h"
 /*
  * Debugging library used to find errors in code.
  * Can be enabled in node.h #define DEBUG
  * Enabled: 1
  * Disabled: 0
  * */

 /* Checks if there is a vehicle on link */
int check_link(link* link){
  int i;
  for (i = 0; i < link->len; i++){
    if (link->road[i] > 0)
      return 1;
  }
  return 0;
}

/* Prints link if there are vehicles on the link */
void print_link(link *link, vehicle *vehicles) {
  int i, car_found;
  char print;
  if (DEBUG){
    car_found = check_link(link);
    if (car_found) {
      printf("L%-3d: ", link->id);

      for (i = 0; i < link->len; i++) {
        print = (link->road[i] > 0) ? vehicles[link->road[i] - 1].v + '0' : '.';
        printf("%c", print);
      }

      printf("\n");
    }
  }
}

/* Prints status of the simulation */
void print_status(struct vehicle* actors, long int seed, int timer) {
  int i, active_cars = 0, inactive_cars;

    for (i = 0; i < AMOUNT_VEHICLES; i++) {
      if (actors[i].active == 1)
        active_cars++;
    }
    inactive_cars = AMOUNT_VEHICLES - active_cars;
    printf("%s %s %s %s\n%-9s%-.2lf%-5s%-7d%-2c%-20d%ld\n",
           "Status: ", "Runtime: ", "Active / inactive vehicles: ", "Seed:",
           "OK", timer * SECONDS_PER_TIMESTEP,
           "s", active_cars, '/', inactive_cars, seed);
}

/* Makes a new line */
void new_line() {
  if (DEBUG)
    printf("\n");
}

/* prints the Timestep #number when debug is on*/
void print_int(char name[], int p) {
  if (DEBUG)
    printf("%s: %d\n", name, p);
}