#include "node.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "debug.h"
#define RIGHT 1
#define LEFT 5
#define FORWARD 3

/* The contents of this function are predefined. Make changes to how network here. */
void build_network(intersection* intersections, link* links){
    int i;
    for(i = 0; i < AMOUNT_LINKS; i++){
        links[i].id = i;
        links[i].road = (int*)calloc(ROAD_LENGTH, sizeof(int));
        links[i].len = ROAD_LENGTH;
        links[i].time_step = 0;
        links[i].intersection = NULL;
    }
    construct_type_a(intersections, 0,&links[0],&links[3],&links[4],&links[7],&links[2],&links[5],&links[6],&links[1]);
    construct_type_a(intersections + 1, 1,&links[3],&links[11],&links[12],&links[4],&links[10],&links[13],&links[14],&links[9]);
    links[0].intersection = &intersections[0];
    links[2].intersection = &intersections[0];
    links[4].intersection = &intersections[0];
    links[6].intersection = &intersections[0];
    links[3].intersection = &intersections[1];
    links[10].intersection = &intersections[1];
    links[12].intersection = &intersections[1];
    links[13].intersection = &intersections[1];
}
/* Pointer to the intersection. */
void construct_type_a(intersection* intersection, int id, link* primary1_enter, link* primary1_exit, link* primary2_enter,
                      link* primary2_exit, link* secondary1_enter, link* secondary1_exit, link* secondary2_enter,
                      link* secondary2_exit){
    intersection->id = id;
    intersection->type = 'a';
    link* p= intersection->layout.type_a.links;
    p[0] = *primary1_enter;
    p[1] = *secondary2_exit;
    p[2] = *secondary1_enter;    /*  TYPE A ER KRYDS 3 OG 4 PÅ BILLEDET  */
    p[3] = *primary1_exit;
    p[4] = *primary2_enter;
    p[5] = *secondary1_exit;
    p[6] = *secondary2_enter;
    p[7] = *primary2_exit;
}
/*
void construct_type_b(intersection* intersection, int id, int primary1_enter, int primary1_exit, int primary2_enter,
                      int primary2_exit, int secondary1_enter, int secondary1_exit){
    intersection->id = id;
    intersection->type = 'b';
    int* p= intersection->layout.type_a.links;
    p[0] = primary1_enter;
    p[2] = secondary1_enter;
    p[3] = primary1_exit;
    p[4] = primary2_enter;
    p[5] = secondary1_exit;
    p[7] = primary2_exit;
}
*/
/* DETTE ER KRYDS 6, 7 og 10 PÅ BILLEDET */
/*
void construct_type_c(intersection* intersection, int id, int primary1_enter, int primary1_exit, int primary2_enter,
                      int primary2_exit, int secondary1_enter, int secondary1_exit, int secondary2_enter,
                      int secondary2_exit, int plusbus1_enter, int plusbus1_exit, int plusbus2_enter, int plusbus2_exit) {
    intersection->id = id;
    intersection->type = 'c';
    int* p = intersection->layout.type_c.links;
    p[0] = primary1_enter;
    p[1] = secondary2_exit;
    p[2] = secondary1_enter;
    p[3] = primary1_exit;
    p[4] = primary2_enter;
    p[5] = secondary1_exit;
    p[6] = secondary2_enter;
    p[7] = primary2_exit;
    p[8] = plusbus2_exit;
    p[9] = plusbus1_enter;
    p[10] = plusbus1_exit;
    p[11] = plusbus2_enter;
}
*/
link* forward_type_a(intersection *intersection, int link_id) {
    return &intersection->layout.type_a.links[(internal_index_a(intersection, link_id) + FORWARD) % 7];
}

link* left_turn_type_a(intersection *intersection, int link_id) {
    return &intersection->layout.type_a.links[(internal_index_a(intersection, link_id) + LEFT) % 8];
}

link* right_turn_type_a(intersection *intersection, int link_id) {
    return &intersection->layout.type_a.links[(internal_index_a(intersection, link_id) + RIGHT) % 7];
}

link* plusbus_type_c(intersection *intersection, int link_id) {
    return &intersection->layout.type_c.links[(internal_index_c(intersection, link_id) == 9) ? 10 : 8];
}

link* forward_type_c(intersection *intersection, int link_id) {
    return &intersection->layout.type_c.links[(internal_index_c(intersection, link_id) + FORWARD) % 7];
}

link* left_turn_type_c(intersection *intersection, int link_id) {
    return &intersection->layout.type_c.links[(internal_index_c(intersection, link_id) + LEFT) % 8];
}

link* right_turn_type_c(intersection *intersection, int link_id) {
    return &intersection->layout.type_c.links[(internal_index_c(intersection, link_id) + RIGHT) % 7];
}

int internal_index_a(intersection* intersection, int link_id){
    int i;
    for (i = 0; i < 8; i++) {
        if(intersection->layout.type_a.links[i].id == link_id)
            break;
    }

    return i;
}

int internal_index_c(intersection* intersection, int link_id){
    int i;
    for (i = 0; i < 12; i++) {
        if(intersection->layout.type_c.links[i].id == link_id)
            break;
    }

    return i;
}

link* right_turn(intersection *intersection, int link_id) {
    link* result;
    switch (intersection->type) {
        case 'a': result = right_turn_type_a(intersection, link_id);
    }
    return result;
}

link* left_turn(intersection *intersection, int link_id) {
    link* result = 0;
    switch (intersection->type) {
        case 'a': result = left_turn_type_a(intersection, link_id);
    }
    return result;
}

link* go_forward(intersection *intersection, int link_id) {
    link* result;
    switch (intersection->type) {
        case 'a': result = forward_type_a(intersection, link_id);
    }
    return result;
}

void initialize_actors(vehicle* actors, link* links, int len){
    srand(time(NULL));
    /* generate actors */
    /* Place actors */
    for (int i = 0; i < CARS; ++i) {
        actors[i].id = i;
        actors[i].v = 0;
        actors[i].active = 1;
        actors[i].is_plusbus = 0;
        actors[i].turn_direction = left;
        int l = rand()%len;
        links[l].road[rand()%links[l].len] = i;
    }
}

void move(link *link, vehicle *vehicles){
    int a, v;
    for (int i = link->len-1; i >= 0; --i) {
        a = link->road[i];
        v = vehicles[a].v;
        if (v){
            link->road[i] = 0;
            if(link->len-1 > i + v) /* if the vehicle does not exceed the end of the road */
                link->road[i + v] = a;
            else if (link->intersection != NULL) {/*There is an intersection at the end of the link. */
                turn(vehicles[a].turn_direction, link->intersection, link->id)->road[0] = a; /* Place on new link */
            }
            else
                vehicles[a].active = 0;
        }
    }
}

void accelerate(link* link, vehicle* vehicles){
    int i, a, v, gap, gap2;
    struct link* new_link;
    for(i = link->len - 1; i >= 0; i--) {
        a = link->road[i];
        v = vehicles[a].v;
        gap = lead_gap(link, i);

        /* If the vehicle is close to an intersection */
        if (i + gap == link->len-1 && link->intersection != NULL){

            new_link = turn(vehicles[a].turn_direction, link->intersection, link->id);
            gap2 = lead_gap(new_link, 0);

            if (gap + gap2 > v){
                vehicles[a].v++;
                if (vehicles[link->road[i]].is_plusbus)
                    i -= PLUS_BUS_LENGTH-1;
            }

            else if (link->time_step < current_time_step(0)){
                time_step(new_link, vehicles);
                gap2 = lead_gap(new_link, -1);

                if (gap + gap2 > v){
                    vehicles[a].v++;
                    if (vehicles[link->road[i]].is_plusbus)
                        i -= PLUS_BUS_LENGTH-1;
                }
            }
        }

        else if(v < V_MAX && gap > v){
            vehicles[link->road[i]].v++;
            if (vehicles[link->road[i]].is_plusbus)
                i -= PLUS_BUS_LENGTH-1;
        }
    }
}

void decelerate(link* link, vehicle* vehicles){
    int i, v, a, gap, gap2;
    struct link* new_link;

    for(i = link->len - 1; i >= 0; i--){
        a = link->road[i];
        v = vehicles[a].v;
        gap = lead_gap(link, i);

        if (i + gap == link->len-1 && link->intersection != NULL){
            new_link = turn(vehicles[a].turn_direction, link->intersection, link->id);
            gap2 = lead_gap(new_link, -1);

            if (gap + gap2 < v) {
                if (new_link->time_step < current_time_step(0)) {
                    time_step(new_link, vehicles);
                    gap2 = lead_gap(new_link, -1);
                }
            }

            if (gap + gap2 < v) {
                vehicles[a].v = gap + gap2;
                if (vehicles[link->road[i]].is_plusbus)
                    i -= PLUS_BUS_LENGTH-1;
            }
        }

        else if(gap < v){
            vehicles[link->road[i]].v = gap;
            if (vehicles[link->road[i]].is_plusbus == 1)
                i -= PLUS_BUS_LENGTH - 1;
        }
        else if(rand() % 100 <= DECELERATE_CHANCE && v > MIN_SPEED_RANDOM_DECELERATE){
            vehicles[link->road[i]].v--;
            if (vehicles[link->road[i]].is_plusbus)
                i -= PLUS_BUS_LENGTH - 1;
        }
        if (vehicles[link->road[i]].is_plusbus)
            i -= PLUS_BUS_LENGTH - 1;
    }
}

int current_time_step(int increase) {
    static int t = 0;
    if(increase)
        t++;
    return t;
}

link* turn(turn_dir dir, intersection *intersection, int link_id) {
    link* result;
    switch (dir) {
        case left:    result = left_turn(intersection, link_id);   break;
        case right:   result = right_turn(intersection, link_id);  break;
        case forward: result = go_forward(intersection, link_id);  break;
    }
    return result;
}

void time_step(link *link, vehicle *vehicles) {
    move(link, vehicles);
    accelerate(link, vehicles);
    decelerate(link, vehicles);
    link->time_step++;
    //if(link->id == 0 || link->id == 5)
        print_link(link, vehicles);
}

void simulate_all_links(link *links, vehicle *vehicles) {
    for (int i = 0; i < AMOUNT_LINKS; ++i) {
        current_time_step(1);
        move(links + i, vehicles);
        accelerate(links + i, vehicles);
        decelerate(links +  i, vehicles);
    }
}

int lead_gap(link *link, int pos) {
    int i, gap = 0;
    for(i = pos + 1; i < link->len; i++){
        if(link->road[i] == 0)
            gap++;
        else
            return gap;
        if(gap > V_MAX)
            return V_MAX;
    }
    /* If the car reaches the end of the road */
    return gap;
}

