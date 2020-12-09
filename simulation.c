#include "node.h"
#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

/* Populates the roads with vehicles */
void initialize_actors(vehicle* actors, link* links, int len);
void simulate_all_links(link* links, vehicle* vehicles, int* done);
void time_step(link* links, vehicle* vehicles);
void move(link *link, vehicle *vehicles);
void change_speed(link* link, vehicle* vehicles);
int is_finished(vehicle* vehicle, link* links, int* done);

int timer = 0;

int main(void) {
    time_t seed = time(NULL);
    srand(seed);
    int done = 0, i = 0, j;
    link links[AMOUNT_LINKS];
    intersection nodes[9];
    vehicle vehicles[AMOUNT_VEHICLES];
    build_network(nodes, links);
    initialize_actors(vehicles, links, AMOUNT_LINKS);

    while (!done) {
      printf("Timestep: %d\n", i + 1);
      simulate_all_links(links, vehicles, &done);
      ++i;
    }
    print_status(vehicles, seed, links + 46);

    for (int j = 0; j < AMOUNT_LINKS; j++) {
        free(links[j].road);
    }

    return EXIT_SUCCESS;
}

void initialize_actors(vehicle* actors, link* links, int len){
    int n;
    /* generate actors */
    /* Place actors */
    for (int i = 0; i < AMOUNT_VEHICLES; i++) {
        actors[i].id = i + 1;
        actors[i].v = 0;

        actors[i].is_plusbus = 0;
        actors[i].turn_direction = forward;
        actors[i].has_moved = 0;
        actors[i].active = 1;

        do
            n=rand()%links->len;
        while (links->road[n] != 0);

        links->road[n] = i + 1;

        /*if (actors[i].id < AMOUNT_VEHICLES/2) {
            actors[i].active = 1;
            int l = rand()%len;
            links[l].road[rand()%links[l].len] = i;
        }
        else
            actors[i].active = 0;
        */
    }
    actors[0].is_plusbus = 1;
    printf("\n");
}

void simulate_all_links(link *links, vehicle *vehicles, int* done) {
    timer++;

    for (int i = 0; i < AMOUNT_LINKS; ++i) {
        if ((links + i)->time_step < timer){
            time_step(links + i, vehicles);
            /*Check if the code is done*/
            if(links[i].id == END_LINK)
              is_finished(vehicles, links + i, done);
        }
    }
    printf("\n");
}

void time_step(link *link, vehicle *vehicles) {
    move(link, vehicles);
    /*if (link->spawn_lane)
        spawn_car(link, vehicles);*/

    link->time_step++;
    change_speed(link, vehicles);

    if(link->id == 0 || link->id == 5 || link->id == 12 || link->id == 20 || link->id == 28 || link->id == 32 || link->id == 38 || link->id == 46)
        print_link(link, vehicles);
}

void move(link *link, vehicle *vehicles) {
    int id, v, index;
    struct link* new_link;
    for (int i = link->len-1; i >= 0; --i) {
        id = link->road[i];
        index = id - 1;
        v = vehicles[index].v;
        if (id && v){
            if(vehicles[index].has_moved == 0){
                link->road[i] = 0;
                if(link->len > i + v) { /* if the vehicle does not exceed the end of the road */
                    link->road[i + v] = id;
                }
                else if (link->intersection != NULL) {/*There is an intersection at the end of the link. */
                    new_link = turn(vehicles[index].turn_direction, link->intersection, link->id);
                    new_link->road[i+v-link->len] = id; /* Place on new link */
                    vehicles[index].turn_direction = decide_turn_dir(new_link, vehicles[index].is_plusbus);
                    vehicles[index].has_moved = 1;
                }
            }
            else
                vehicles[index].has_moved = 0;
        }
    }
}

void change_speed(link *link, vehicle *vehicles) {
    int i, id, v, gap = 0, gap2, index;
    struct link* new_link;
    for(i = link->len - 1; i >= 0; i--) {
        gap2 = 0;
        id = link->road[i];
        index = id - 1;
        if (id){
            v = vehicles[index].v;
            gap = lead_gap(link, i);

            /* Is the car approaching an intersection? */
            if (i + gap == link->len-1 && link->intersection != NULL) {
                new_link = turn(vehicles[index].turn_direction, link->intersection, link->id);

                if (new_link->time_step < timer)
                    time_step(new_link, vehicles);

                gap2 = lead_gap(new_link, -1);

                /* Does the car have to decelerate to avoid collision? */
                if (gap + gap2 < v)
                    vehicles[index].v = gap + gap2;

                else if (v < V_MAX && gap + gap2 > v)
                    vehicles[index].v++;
            }

            /* There is no intersection */
            else if (v < V_MAX && gap > v)
                vehicles[index].v++;

            else if (gap < v)
                vehicles[index].v = gap;

            /* The plusbus is longer than a regular car. */
            if (vehicles[index].is_plusbus)
                i -= PLUS_BUS_LENGTH - 1;

            assert(vehicles[index].v <= gap + gap2);
        }
    }
}

int is_finished(vehicle* vehicle, link* links, int* done){
    int i, index;
    /*Checks if the Plusbus has reached its destination */
    for(i = links->len -1; i >= 0; i--){
        index = links->road[i] - 1;
        if(vehicle[index].is_plusbus && index >= 0){
          *done = 1;
        }
    }

}
