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
        links[i].left_chance = 33.3;
        links[i].left_chance = 33.3;
    }
    construct_type_a(intersections, 0,links,links+3,links+4,links+7,links+2,links+5,links+6,links+1);
    construct_type_a(intersections + 1, 1,links+3,links+11,links+12,links+4,links+15,links+13,links+14,links+9);
    links[0].intersection = intersections;
    links[2].intersection = intersections;
    links[4].intersection = intersections;
    links[6].intersection = intersections;
    links[3].intersection = intersections + 1;
    links[15].intersection = intersections + 1;
    links[12].intersection = intersections + 1;
    links[14].intersection = intersections + 1;
}
/* Pointer to the intersection. */
void construct_type_a(intersection* intersection, int id, link* primary1_enter, link* primary1_exit, link* primary2_enter,
                      link* primary2_exit, link* secondary1_enter, link* secondary1_exit, link* secondary2_enter,
                      link* secondary2_exit){
    intersection->id = id;
    intersection->type = 'a';
    link** p= intersection->layout.type_a.links;
    p[0] = primary1_enter;
    p[1] = secondary2_exit;
    p[2] = secondary1_enter;    /*  TYPE A ER KRYDS 3 OG 4 PÅ BILLEDET  */
    p[3] = primary1_exit;
    p[4]= primary2_enter;
    p[5] = secondary1_exit;
    p[6] = secondary2_enter;
    p[7] = primary2_exit;
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
    return *intersection->layout.type_a.links + (internal_index_a(intersection, link_id) + FORWARD) % 7;
}

link* left_turn_type_a(intersection *intersection, int link_id) {
    return *intersection->layout.type_a.links + (internal_index_a(intersection, link_id) + LEFT) % 8;
}

link* right_turn_type_a(intersection *intersection, int link_id) {
    return *intersection->layout.type_a.links + (internal_index_a(intersection, link_id) + RIGHT) % 7;
}
/*
link* plusbus_type_c(intersection *intersection, int link_id) {
    return *intersection->layout.type_c.links + (internal_index_c(intersection, link_id) == 9) ? 10 : 8;
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
*/
int internal_index_a(intersection* intersection, int link_id){
    int i;
    link* link;
    for (i = 0; i < 8; i++) {
        link = intersection->layout.type_a.links[i];
        if (link->id == link_id)
            break;
    }

    return i;
}
/*
int internal_index_c(intersection* intersection, int link_id){
    int i;
    for (i = 0; i < 12; i++) {
        if(intersection->layout.type_c.links[i].id == link_id)
            break;
    }

    return i;
}
*/
link* right_turn(intersection *intersection, int link_id) {
    link* result;
    switch (intersection->type) {
        case 'a': result = right_turn_type_a(intersection, link_id);
    }
    return result;
}

link* left_turn(intersection *intersection, int link_id) {
    link* result;
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

turn_dir decide_turn_dir(link* link){
    int dir = rand()%100 + 1;
    if (dir < link->left_chance)
        return left;
    else if (dir < link->left_chance + link->right_chance)
        return right;
    else
        return forward;
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

