#include "node.h"
#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

/* Populates the roads with vehicles */
void initialize_actors(vehicle* actors, link* links, int len);
void simulate_all_links(link* links, vehicle* vehicles);
void time_step(link* links, vehicle* vehicles);
void move(link *link, vehicle *vehicles);
void change_speed(link* link, vehicle* vehicles);

int timer = 0;

int main(void) {
    time_t seed = time(NULL);
    srand(seed);

    link links[AMOUNT_LINKS];
    intersection nodes[2];
    vehicle vehicles[AMOUNT_VEHICLES];
    build_network(nodes, links);
    initialize_actors(vehicles, links, AMOUNT_LINKS);

    print_vehicles(vehicles, AMOUNT_VEHICLES);
    for (int j = 0; j < TIME_STEPS; ++j) {
        printf("Timestep: %d\n", j+1);
        simulate_all_links(links, vehicles);
    }

    for (int j = 0; j < AMOUNT_LINKS; j++) {
        free(links[j].road);
    }

    return EXIT_SUCCESS;
}

void initialize_actors(vehicle* actors, link* links, int len){
    srand(time(NULL));
    /* generate actors */
    /* Place actors */
    for (int i = 0; i < AMOUNT_VEHICLES; i++) {
        actors[i].id = i+1;
        actors[i].v = 0;

        actors[i].is_plusbus = 0;
        actors[i].turn_direction = forward;
        actors[i].has_moved = 0;

        links->road[rand()%links->len] = i;

        /*if (actors[i].id < AMOUNT_VEHICLES/2) {
            actors[i].active = 1;
            int l = rand()%len;
            links[l].road[rand()%links[l].len] = i;
        }
        else
            actors[i].active = 0;
        */
    }
}

void simulate_all_links(link *links, vehicle *vehicles) {
    timer++;

    for (int i = 0; i < AMOUNT_LINKS; ++i) {
        if ((links + i)->time_step < timer){
            time_step(links + i, vehicles);
        }
    }
    printf("\n");
}

void time_step(link *link, vehicle *vehicles) {
    move(link, vehicles);
    if (link->spawn_lane)
        spawn_car(link, vehicles);

    link->time_step++;
    change_speed(link, vehicles);

    if(link->id == 0 || link->id==3 || link->id == 13)
        print_link(link, vehicles);
}

void move(link *link, vehicle *vehicles) {
    int a, v;
    struct link* new_link;
    for (int i = link->len-1; i >= 0; --i) {
        a = link->road[i];
        v = vehicles[a].v;
        if (a && v){
            if(vehicles[a].has_moved == 0){
                link->road[i] = 0;
                if(link->len > i + v) { /* if the vehicle does not exceed the end of the road */
                    link->road[i + v] = a;
                }
                else if (link->intersection != NULL) {/*There is an intersection at the end of the link. */
                    new_link = turn(vehicles[a].turn_direction, link->intersection, link->id);
                    new_link->road[i+v-link->len] = a; /* Place on new link */
                    vehicles[a].turn_direction = decide_turn_dir(new_link);
                    vehicles[a].has_moved = 1;
                }
            }
            else
                vehicles[a].has_moved = 0;
        }
    }
}

void change_speed(link *link, vehicle *vehicles) {
    int i, a, v, gap = 0, gap2;
    struct link* new_link;
    for(i = link->len - 1; i >= 0; i--) {
        gap2 = 0;
        a = link->road[i];
        if (a){
            v = vehicles[a].v;
            gap = lead_gap(link, i);

            /* Is the car approaching an intersection? */
            if (i + gap == link->len-1 && link->intersection != NULL) {
                new_link = turn(vehicles[a].turn_direction, link->intersection, link->id);

                if (new_link->time_step < timer)
                    time_step(new_link, vehicles);

                gap2 = lead_gap(new_link, -1);

                /* Does the car have to decelerate to avoid collision? */
                if (gap + gap2 < v)
                    vehicles[a].v = gap + gap2;

                else if (v < V_MAX && gap + gap2 > v)
                    vehicles[a].v++;
            }

            /* There is no intersection */
            else if (v < V_MAX && gap > v)
                vehicles[a].v++;

            else if (gap < v)
                vehicles[a].v = gap;

            /* The plusbus is longer than a regular car. */
            if (vehicles[link->road[i]].is_plusbus)
                i -= PLUS_BUS_LENGTH - 1;

            assert(vehicles[a].v <= gap + gap2);
        }
    }
}
