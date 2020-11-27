#include "debug.h"
#include "node.h"

void print_link(link *link, vehicle *vehicles) {
    int i;
    char print;
    for(i = 0; i < link->len; i++){
        print = link->road[i] > 0 ? vehicles[link->road[i]].v + '0' : '.';
        printf("%c", print);
    }
    printf("\n");
}

void print_vehicles(vehicle *vehicles, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d ", vehicles[i].id);
    }
    printf("\n");
}

void print_status(struct vehicle* actors, long int seed) {
    int i, active = 0, disabled;

    for (i = 1; i < ROAD_LENGTH + 1; i++) {
        if (actors[i].active == 1)
            active++;
    }
    disabled = AMOUNT_VEHICLES-active;
    printf("%s %s %s %s\n%-9s%-10d%-7d%-2c%-20d%ld\n", "Status: ", "Runtime: ", "Active / disabled vehicles: ", "Seed:",
           "OK", TIME_STEPS, active, '/', disabled, seed);
}