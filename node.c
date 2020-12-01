#include "node.h"
#include <stdlib.h>
#include <time.h>

#define RIGHT 1
#define LEFT 5
#define FORWARD 3

/* The contents of this function are predefined. Make changes to how network here. */
void build_network(intersection* intersections, link* links){
    int i;

    for(i = 0; i < AMOUNT_LINKS/2; i++){
        links[i].id = i;
        links[i].road = (int*)calloc(ROAD_LENGTH, sizeof(int));
        links[i].len = ROAD_LENGTH;
    }
    construct_type_a(intersections, 0,0,3,4,7,2,5,6,1);

    for(i = AMOUNT_LINKS/2; i < AMOUNT_LINKS; i++){
        links[i].id = i;
        links[i].road = (int*)calloc(ROAD_LENGTH, sizeof(int));
        links[i].len = ROAD_LENGTH;
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
    for (int i = 0; i < AMOUNT_LINKS; ++i) {
        move_link(&links[i], vehicles);
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

void lane_change(link *link, vehicle *vehicles) {
    const pocket left_pocket = link->left_pocket;
    const pocket right_pocket = link->right_pocket;

    int car_id;

    if (left_pocket.len) {


    }
    else if (right_pocket.len) {
        for (size_t i = 0; i < V_MAX; ++i) {
            /* check on pocket position */
            car_id = link->road[right_pocket.pos - i];
            /* is there a car? */
            if (car_id > 0) {
                /* will car reach turn? */
                if (i - vehicles[car_id].v <= 0) {
                    if (1) {

                    }
                    else if (1) {

                    }
                }
            }
        }
    }
}