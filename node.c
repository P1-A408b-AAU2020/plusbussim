#include "node.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define RIGHT 1
#define LEFT 5
#define FORWARD 3
#define AMT_SPAWN_LANES 6

/* The contents of this function are predefined. Make changes to how network here. */
void build_network(intersection* intersections, link* links){
    int spawn_lanes[AMT_SPAWN_LANES] = {0, 2, 6, 9, 11, 13};
    double spawn_chances[AMT_SPAWN_LANES] = {25.3, 21.2, 15.7, 19.2, 8.5, 15.2};
    int i, k = 0, j = 0;
    for(i = 0; i < AMOUNT_LINKS/2; i++){
        links[i].id = i;
        links[i].road = (int*)calloc(ROAD_LENGTH, sizeof(int));
        links[i].len = ROAD_LENGTH;
        if (links[i].id == spawn_lanes[k]){
            links[i].spawn_lane = 1;
            j++;
        }
    }
    construct_type_a(intersections, 0,0,3,4,7,2,5,6,1);

    for(i = AMOUNT_LINKS/2; i < AMOUNT_LINKS; i++){
        links[i].id = i;
        links[i].road = (int*)calloc(ROAD_LENGTH, sizeof(int));
        links[i].len = ROAD_LENGTH;
        if (links[i].id == spawn_lanes[k]){
            links[i].spawn_lane = 1;
        }
    }
    construct_type_a(intersections + 1, 1,3,11,12,4,10,13,14,9);

    for (int i = 0; i < AMOUNT_LINKS; i++) {
        if (links[i].spawn_lane) {
            links[i].spawn_chance = spawn_chances[k];
            k++;
        }
    }
}
/* Pointer to the intersection. */
void construct_type_a(intersection* intersection, int id, int primary1_enter, int primary1_exit, int primary2_enter,
                      int primary2_exit, int secondary1_enter, int secondary1_exit, int secondary2_enter,
                      int secondary2_exit){
    intersection->id = id;
    intersection->type = 'a';
    int* p= intersection->layout.type_a.links;
    p[0] = primary1_enter;
    p[1] = secondary2_exit;
    p[2] = secondary1_enter;    /*  TYPE A ER KRYDS 3 OG 4 PÅ BILLEDET  */
    p[3] = primary1_exit;
    p[4] = primary2_enter;
    p[5] = secondary1_exit;
    p[6] = secondary2_enter;
    p[7] = primary2_exit;
}
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

/* DETTE ER KRYDS 6, 7 og 10 PÅ BILLEDET */
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

int forward_type_a(intersection *intersection, int link_id) {
    return intersection->layout.type_a.links[(internal_index_a(intersection, link_id) + FORWARD) % 7];
}

int left_turn_type_a(intersection *intersection, int link_id) {
    return intersection->layout.type_a.links[(internal_index_a(intersection, link_id) + LEFT) % 8];
}

int right_turn_type_a(intersection *intersection, int link_id) {
    return intersection->layout.type_a.links[(internal_index_a(intersection, link_id) + RIGHT) % 7];
}

int plusbus_type_c(intersection *intersection, int link_id) {
    return intersection->layout.type_c.links[(internal_index_c(intersection, link_id) == 9) ? 10 : 8];
}

int forward_type_c(intersection *intersection, int link_id) {
    return intersection->layout.type_c.links[(internal_index_c(intersection, link_id) + FORWARD) % 7];
}

int left_turn_type_c(intersection *intersection, int link_id) {
    return intersection->layout.type_c.links[(internal_index_c(intersection, link_id) + LEFT) % 8];
}

int right_turn_type_c(intersection *intersection, int link_id) {
    return intersection->layout.type_c.links[(internal_index_c(intersection, link_id) + RIGHT) % 7];
}

int internal_index_a(intersection* intersection, int link_id){
    int i;
    for (i = 0; i < 8; i++) {
        if(intersection->layout.type_a.links[i] == link_id)
            break;
    }

    return i;
}

int internal_index_c(intersection* intersection, int link_id){
    int i;
    for (i = 0; i < 12; i++) {
        if(intersection->layout.type_c.links[i] == link_id)
            break;
    }

    return i;
}

int right_turn(intersection *intersection, int link_id) {
    int result = 0;
    switch (intersection->type) {
        case 'a': result = right_turn_type_a(intersection, link_id);
    }
    return result;
}

int left_turn(intersection *intersection, int link_id) {
    int result = 0;
    switch (intersection->type) {
        case 'a': result = left_turn_type_a(intersection, link_id);
    }
    return result;
}

int go_forward(intersection *intersection, int link_id) {
    int result = 0;
    switch (intersection->type) {
        case 'a': result = forward_type_a(intersection, link_id);
    }
    return result;
}

void initialize_actors(vehicle* actors, link* links, int len){
    srand(time(NULL));
    /* generate actors */
    /* Place actors */
    for (int i = 0; i < CARS; i++) {
        actors[i].id = i;
        actors[i].v = 0;
        actors[i].active = (i < CARS/2) ? 1 : 0;
        actors[i].is_plusbus = 0;
        int l = rand()%len;
        links[l].road[rand()%links[l].len] = i;
    }
}

void move_link(link *link, vehicle *vehicles) {
    int i, a, mov;
    for(i = link->len-1; i >= 0; i--){
        a = link->road[i];
        if (a > 0){
            if(vehicles[a].v > 0){
                link->road[i] = 0;
                mov = i + vehicles[a].v;
                if(mov < link->len){
                    link->road[mov] = a;
                }
                else{
                    vehicles[a].active = 0;
                }
            }
        }
    }
}

void decelerate_link(link *link, vehicle *vehicles) {
    int i, v, gap;
    for(i = link->len - 1; i >= 0; i--){
        v = vehicles[link->road[i]].v;
        gap = lead_gap(link, i);

        if(gap < v){
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

void accelerate_link(link *link, vehicle *vehicles) {
    int i, v, gap;
    for(i = link->len - 1; i >= 0; i--){
        v = vehicles[link->road[i]].v;
        gap = lead_gap(link, i);

        if(v < V_MAX && gap > v){
            vehicles[link->road[i]].v++;
            if (vehicles[link->road[i]].is_plusbus)
                i -= PLUS_BUS_LENGTH-1;
        }
    }
}

void time_step(link *links, vehicle *vehicles) {
    int i;
    for (i = 0; i < AMOUNT_LINKS; i++) {
        move_link(&links[i], vehicles);

        if (links->spawn_lane)
            spawn_car(&links[i], vehicles);

        accelerate_link(&links[i], vehicles);
        decelerate_link(&links[i], vehicles);
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
    return V_MAX;
}

void spawn_car(link* link, vehicle* vehicles) {
    int car_spawned = 0;
    int i = 1;

    while(!car_spawned){
        if(!vehicles[i].active) {
            if (!vehicles[link->road[0]].id) {
                if (rand() % 100 <= link->spawn_chance) {
                    link->road[0] = vehicles[i].id;
                    vehicles[i].active = 1;
                    vehicles[i].v = V_MAX;
                    car_spawned = 1;
                }
            }
            break;
       }
       if (i > CARS)
           break;
       i++;
    }
}
