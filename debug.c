#include "debug.h"
#include "variables.h"

void print_actors(vehicle* actors){
    int i;
    for(i = 1; i < AMOUNT_VEHICLES+1; i++){
        printf("Car %d:\n  v: %d\n", actors[i].id, actors[i].v);
    }
}

/* Prints out A SINGLE LANE of the simulation. */
void print_lane(const int* link, int len, struct vehicle* actors){
    int i;
    char print;
    for(i = 0; i < len; i++){
        print = link[i] > 0 ? actors[link[i]].v + '0' : '.';
        printf("%c", print);
    }
    printf("\n");
}

void print_status(struct vehicle* actors, long int seed) {
    int i, active = 0, disabled;

    for (i = 1; i < ROAD_SIZE + 1; i++) {
        if (actors[i].active == 1)
            active++;
    }
    disabled = AMOUNT_VEHICLES-active;
    printf("%s %s %s %s\n%-9s%-10d%-7d%-2c%-20d%ld\n", "Status: ", "Runtime: ", "Active / disabled vehicles: ", "Seed:",
           "OK", TIME_STEPS, active, '/', disabled, seed);
}