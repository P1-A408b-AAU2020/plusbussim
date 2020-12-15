#include "debug.h"
 /*
  * Debugging library used to find errors in code.
  * Can be enabled in node.h #define DEBUG
  * Enabled: 1
  * Disabled: 0
  * */

int check_link(link* link, vehicle* vehicles){
  int i;

  for (i = 0; i < link->len; i++){
    if (link->road[i] > 0)
      return 1;
  }

  return 0;
}

void print_link(link *link, vehicle *vehicles) {
  int i, a;
  char print;
  if (DEBUG){
    a = check_link(link, vehicles);
    if (a) {
      printf("L%-3d: ", link->id);

      for (i = 0; i < link->len; i++) {
        print = link->road[i] > 0 ? vehicles[link->road[i] - 1].v + '0' : '.';
        printf("%c", print);
      }

      printf("\n");
    }
  }
}

void print_vehicles(vehicle *vehicles, int len) {
    if(DEBUG) {
        for (int i = 0; i < len; i++) {
            printf("%d ", vehicles[i].id);
        }
        printf("\n");
    }
}

void print_status(struct vehicle* actors, long int seed, link* link, int timer) {
    int i, active = 0, disabled;
    /*if (DEBUG) {*/
        for (i = 0; i < AMOUNT_VEHICLES; i++) {
            if (actors[i].active == 1)
                active++;
        }
        disabled = AMOUNT_VEHICLES - active;
        printf("%s %s %s %s\n%-9s%-.2lf%-5s%-7d%-2c%-20d%ld\n",
               "Status: ", "Runtime: ", "Active / disabled vehicles: ", "Seed:",
               "OK", timer * SECONDS_PER_TIMESTEP,
               "s", active, '/', disabled, seed);
    /*}*/
}


int check_status(link *link, int amount) {
    int n = 0;
    if(DEBUG) {
        for (int i = 0; i < link->len; ++i) {
            if (link->road[i] != 0)
                n++;
        }

        if (n == amount) /* The expected number of vehicles have been found */
            return 1;
        else
            return 0;
    }
}

/*NOT WORKING*/
void print_i_data(intersection *intersection) {
  int i;
  if (DEBUG) {
    for (i = 0; i < 9; i++) {
      switch (intersection->type) {
        case 'c': printf("TYPE: %-3c ID: %-3d STATE: %-3d COUNTER: %d\n", (intersection + i)->type, (intersection + i)->id,(intersection + i)->layout.type_c.data.state, (intersection + i)->layout.type_c.data.counter); break;
        case 'd': printf("TYPE: %-3c ID: %-3d STATE: %-3d COUNTER: %d\n", (intersection + i)->type, (intersection + i)->id,(intersection + i)->layout.type_d.data.state, (intersection + i)->layout.type_d.data.counter); break;
        case 'e': printf("TYPE: %-3c ID: %-3d STATE: %-3d COUNTER: %d\n", (intersection + i)->type, (intersection + i)->id,(intersection + i)->layout.type_e.data.state, (intersection + i)->layout.type_e.data.counter); break;

      }
    }
  }
}

void new_line() {
  if (DEBUG)
    printf("\n");
}

void print_int(char name[], int p) {
  if (DEBUG)
    printf("%s: %d\n", name, p);
}