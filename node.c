#include "node.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RIGHT 1
#define LEFT 5
#define FORWARD 3
#define ROAD_LENGTH 25

/* The contents of this function are predefined. Make changes to how network here. */
void build_network(intersection* intersections, link* links){
    int i;

    for(i = 0; i < 8; i++){
        links[i].id = i;
        links[i].road = (int*)calloc(ROAD_LENGTH, sizeof(int));
        links[i].len = 25;
    }
    construct_type_a(intersections, 0,0,3,4,7,2,5,6,1);

    for(i = 8; i < 16; i++){
        links[i].id = i;
        links[i].road = (int*)calloc(ROAD_LENGTH, sizeof(int));
        links[i].len = 25;
    }
    construct_type_a(intersections + 1, 1,3,11,12,4,10,13,14,9);

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
    p[2] = secondary1_enter;
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

int forward_type_a(intersection *intersection, int link_id) {
    return intersection->layout.type_a.links[(internal_index(intersection, link_id) + FORWARD) % 7];
}

int left_turn_type_a(intersection *intersection, int link_id) {
    return intersection->layout.type_a.links[(internal_index(intersection, link_id) +1 + LEFT) % 8 - 1];
}

int right_turn_type_a(intersection *intersection, int link_id) {
    return intersection->layout.type_a.links[(internal_index(intersection, link_id) + RIGHT) % 7];
}

int internal_index(intersection* intersection, int link_id){
    int i;
    for (i = 0; i < 8; ++i) {
        if(intersection->layout.type_a.links[i] == link_id)
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

int forward(intersection *intersection, int link_id) {
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
    for (int i = 0; i < CARS; ++i) {
        actors[i].id = i;
        actors[i].v = 0;
        actors[i].active = 1;
        int l = rand()%len;
        links[l].road[rand()%links[l].len] = i;
    }
}

void print_link(link *link, vehicle *vehicles) {
    int i;
    char print;
    for(i = 0; i < link->len; i++){
        print = link->road[i] > 0 ? vehicles[link->road[i]].v + '0' : '.';
        printf("%c", print);
    }
    printf("\n");
}

void print_vehicles(vehicle *vehicles, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d ", vehicles[i].id);
    }
    printf("\n");
}


