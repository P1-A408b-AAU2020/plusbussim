/* Hello from the other siiide! lul*/
#include "simulation.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "debug.h"
#include "variables.h"

void lane_change(offset);

int main(void){
    int i, x, y;
    link links[16];
    node nodes[2];
    build_network(links, nodes);

    /* Main setup */

    int* link = (int*)calloc(ROAD_SIZE, sizeof(int));
    /* int* link = new_link(ROAD_SIZE); */

    struct vehicle* actors = (struct vehicle*)calloc(ROAD_SIZE + 1, sizeof(struct vehicle));

    time_t seed = time(NULL);
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
    int *offset;
    lane_change(offset);

    move(link, len, actors);
    accellerate(link, len, actors);
    decelerate(link, len, actors);
    print_lane(link, ROAD_SIZE, actors);
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
void move(int* link, int len, struct vehicle* actors){
    int i, a, mov;
    for(i = len-1; i >= 0; i--){
        a = link[i];
        if (a > 0){
            if(actors[a].v - offset > 0){
                link[i] = 0;
                mov = i + actors[a].v - offset;
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

void lane_change(link *l_link, int *offset) {
    int i;

    const pocket left_pocket = l_link->left_pocket_lane;
    const pocket right_pocket = l_link->right_pocket_lane;

    if (left_pocket != NULL) {
        for (i = left_pocket.pos ; i > left_pocket.pos-V_MAX; --i) {
            if (l_link->road[i] != NULL) {
                if (car.turn_left == 1) {
                    
                }
            }
        }
    }
    else if (right_pocket != NULL) {

    }
    else {
        return;
    }
}