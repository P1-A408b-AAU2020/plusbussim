/* Hello from the other siiide! lul*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "debug.h"
#include "variables.h"
#include "datatypes.h"
#include "simulation.h"

int main(void){
    int i;

    /* Main setup */
    int* link = (int*)calloc(ROAD_SIZE, sizeof(int));
    struct vehicle* actors = (struct vehicle*)calloc(ROAD_SIZE + 1, sizeof(struct vehicle));

    long int seed = time(NULL);
    srand(seed);
    init_actors(link, ROAD_SIZE, actors);

    /* Print initial lane */
    print_lane(link, ROAD_SIZE, actors);

    for(i = 0; i < TIME_STEPS; i++){
        time_step(link, ROAD_SIZE, actors);
    }

    print_status(actors, seed);

    free(link);
    free(actors);
    return EXIT_SUCCESS;
}

/* Places vehicles on the road. The vehicles are randomly generated and placed. */
void init_actors(int* link, int len, struct vehicle* actors){
    int i, j = AMOUNT_VEHICLES, pos = 0;

    /* Generate actors */
    for(i = 1; i <= AMOUNT_VEHICLES; i++){
        actors[i].id = i;
        actors[i].v = 0;
        actors[i].active = 1;
    }

    /* Place actors on road */
    for(i = 0; i < AMOUNT_VEHICLES; i++){
        pos = rand()%len;
        if(link[pos] != 0)
            i--;
        else
            link[pos] = actors[j--].id;
    }
}

/* Each time step of the simulation, this is run. */
void time_step(int* link, int len, struct vehicle* actors){
    move(link, len, actors);
    accellerate(link, len, actors);
    decelerate(link, len, actors);
    print_lane(link, ROAD_SIZE, actors);
}

/* Accelerates all vehicles */
/* Could this be more efficient using pointers for v? */
void accellerate(int* link, int len, struct vehicle* actors){
    int i, v, gap;
    for(i = 0; i < len; i++){
        v = actors[link[i]].v;
        gap = lead_gap(link, len, i);

        if(v < V_MAX && gap > v)
            actors[link[i]].v++;
    }
}

/* Decelerates all vehicles */
void decelerate(int* link, int len, struct vehicle* actors){
    int i, v, gap;
    for(i = 0; i < len; i++){
        v = actors[link[i]].v;
        gap = lead_gap(link, len, i);

        if(gap < v)
            actors[link[i]].v = gap;
        else if(rand() % 100 <= DECELERATE_CHANCE && v > MIN_SPEED_RANDOM_DECELERATE)
            actors[link[i]].v--;
    }
}

/* Returns the lead gap in front of given position */
int lead_gap(int* link, int len, int pos){
    int i, gap = 0;
    for(i = pos + 1; i < len; i++){
        if(link[i] == 0)
            gap++;
        else
            return gap;
        if(gap > V_MAX)
            return V_MAX;
    }
    /* If the car reaches the end of the road */
    return V_MAX;
}

/* Moves all vehicles by their speed. Removes them from the road if they reach the end. */
void move(int* link, int len, struct vehicle* actors){
    int i, a, mov;
    for(i = len-1; i >= 0; i--){
        a = link[i];
        if (a > 0){
            if(actors[a].v > 0){
                link[i] = 0;
                mov = i + actors[a].v;
                if(mov < len){
                    link[mov] = a;
                }
                else{
                    actors[a].active = 0;
                }
            }
        }
    }
}


