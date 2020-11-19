#include <stdio.h>
#include "simulation.h"
#include "variables.h"
#include "debug.h"

void print_actors(struct vehicle* actors){
    int i;
    for(i = 1; i < AMOUNT_VEHICLES+1; i++){
        printf("Car %d:\n  v: %d\n", actors[i].id, actors[i].v);
    }
}

/* Prints out A SINGLE LANE of the simulation. */
void print_lane(int* link, int len, struct vehicle* actors){
    int i;
    char print;
    for(i = 0; i < len; i++){
        print = link[i] > 0 ? actors[link[i]].v + '0' : '.';
        printf("%c", print);
    }
    printf("\n");
}