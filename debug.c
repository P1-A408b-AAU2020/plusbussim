#include "debug.h"
#include "node.h"
#define SECONDS_PER_TIMESTEP 1.667

void print_link(link *link, vehicle *vehicles) {
    int i;
    char print;
    printf("L%-3d: ", link->id);
    for(i = 0; i < link->len; i++){
        print = link->road[i] > 0 ? vehicles[link->road[i] - 1].v + '0' : '.';
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

void print_status(struct vehicle* actors, long int seed, link* link, int timer) {
    int i, active = 0, disabled;

    for (i = 0; i < AMOUNT_VEHICLES; i++) {
        if (actors[i].active == 1)
            active++;
    }
    disabled = AMOUNT_VEHICLES-active;
    printf("%s %s %s %s\n%-9s%-.2lf%-5s%-7d%-2c%-20d%ld\n",
           "Status: ", "Runtime: ", "Active / disabled vehicles: ", "Seed:",
           check_status(link, AMOUNT_VEHICLES)? "OK" : "FAIL", timer*SECONDS_PER_TIMESTEP,
           "s",active, '/', disabled, seed);
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
