#include "debug.h"
#include "node.h"


void print_link(link *link, vehicle *vehicles) {
    int i;
    char print;
    printf("L%-3d: ", link->id);
    for(i = 0; i < link->len; i++){
        print = link->road[i] > 0 ? vehicles[link->road[i]].id - 1 + '0' : '.';
        printf("%c", print);
    }
    printf("\n");
}

void print_vehicles(vehicle *vehicles, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", vehicles[i].id);
    }
    printf("\n");
}

void print_status(struct vehicle* actors, long int seed, link* link) {
    int i, active = 0, disabled;

    for (i = 1; i < ROAD_LENGTH + 1; i++) {
        if (actors[i].active == 1)
            active++;
    }
    disabled = AMOUNT_VEHICLES-active;
    printf("%s %s %s %s\n%-9s%-10d%-7d%-2c%-20d%ld\n", "Status: ", "Runtime: ", "Active / disabled vehicles: ", "Seed:",
           check_status(link, AMOUNT_VEHICLES)? "OK" : "FAIL", TIME_STEPS, active, '/', disabled, seed);
}


int check_status(link *link, int amount) {
    int n = 0;
    for (int i = 0; i < link->len; ++i) {
        if (link->road[i] != 0)
            n++;
    }

    if (n == amount) /* The expected number of vehicles have been found */
        return 1;
    else
        return 0;
}
