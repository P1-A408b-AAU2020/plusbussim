/* Hello from the other siiide! lul*/
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "debug.h"
#include "variables.h"

#define AMOUNT_ROADS 16

void init_actors(int*, int, struct vehicle*);
void time_step(int*, int, struct vehicle*);
void accellerate(int*, int, struct vehicle*);
void decelerate(int*, int, struct vehicle*);
void move(int*, int, struct vehicle*);
int lead_gap(int*, int, int);


int main(void){
    int i, x, y;
    time_t seed = time(NULL);
    srand(seed);

    link links[AMOUNT_ROADS];
    intersection nodes[2];
    vehicle vehicles[CARS];
    build_network(nodes, links);
    initialize_actors(vehicles, links, 16);
    printf("%d\n", left_turn(nodes, 6));
    printf("%d\n", left_turn(nodes+1, 3));

    /* Main setup */
    int* link = (int*)calloc(ROAD_SIZE, sizeof(int));
    struct vehicle* actors = (struct vehicle*)calloc(ROAD_SIZE + 1, sizeof(struct vehicle));

    init_actors(link, ROAD_SIZE, actors);

    print_vehicles(vehicles, CARS);
    /*for (int j = 0; j < 16; ++j) {
        print_link(&links[j], vehicles);
    }*/
    /* Print initial lane */
    /*print_lane(link, ROAD_SIZE, actors);*/

    for(i = 0; i < TIME_STEPS; i++){
        time_step(links->road, 25, vehicles);
        print_link(links, vehicles);

    }

    print_status(actors, seed);

    for (int j = 0; j < AMOUNT_ROADS; ++j) {
        free(links[j].road);
    }

    free(link);
    free(actors);
    return EXIT_SUCCESS;
}

/* Places vehicles on the road. The vehicles are randomly generated and placed. */
void init_actors(int* link, int len, struct vehicle* actors){
    int i, k, j = 1, pos = 0, plusbus_assigned = 0;

    /* Generate actors */
    for(i = 1; i <= AMOUNT_VEHICLES; i++){
        actors[i].id = i;
        actors[i].v = 0;
        actors[i].active = 1;

        if (!plusbus_assigned){
            actors[i].is_plusbus = 1;
            plusbus_assigned = 1;
        }
        else
            actors[i].is_plusbus = 0;
    }

    /* Place actors on road */
    for(i = 0; i < AMOUNT_VEHICLES; i++){
        pos = rand()%len;
        if(link[pos] != 0)
            i--;
        else{
            if (actors[j].is_plusbus){
                for (k = 0; k < PLUSBUS_LENGTH; k++)
                    link[pos +k] = actors[j].id;
            }
            else{
                link[pos] = actors[j].id;
            }
            j++;
        }
    }
}

/* Each time step of the simulation, this is run. */
void time_step(int* link, int len, struct vehicle* actors){
    move(link, len, actors);
    accellerate(link, len, actors);
    decelerate(link, len, actors);
}

/* Accelerates all vehicles */
/* Could this be more efficient using pointers for v? */
void accellerate(int* link, int len, struct vehicle* actors){
    int i, v, gap;
    for(i = len - 1; i >= 0; i--){
        v = actors[link[i]].v;
        gap = lead_gap(link, len, i);

        if(v < V_MAX && gap > v){
            actors[link[i]].v++;
            if (actors[link[i]].is_plusbus)
                i -= PLUSBUS_LENGTH-1;
        }
    }
}

/* Decelerates all vehicles */
void decelerate(int* link, int len, struct vehicle* actors){
    int i, v, gap;
    for(i = len - 1; i >= 0; i--){
        v = actors[link[i]].v;
        gap = lead_gap(link, len, i);

        if(gap < v){
            actors[link[i]].v = gap;
            if (actors[link[i]].is_plusbus == 1)
                i -= PLUSBUS_LENGTH - 1;
        }
        else if(rand() % 100 <= DECELERATE_CHANCE && v > MIN_SPEED_RANDOM_DECELERATE){
            actors[link[i]].v--;
            if (actors[link[i]].is_plusbus)
                i -= PLUSBUS_LENGTH - 1;
        }
        if (actors[link[i]].is_plusbus)
            i -= PLUSBUS_LENGTH - 1;
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
void move(int* link, int len, vehicle* actors){
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


