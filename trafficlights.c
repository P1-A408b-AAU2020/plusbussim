/*TODO add "trafficlights.c trafficlights.h" to CMakeLists.txt when this library is done
 *TODO make it work on more than one road and fix hardcoded solution(may need recursive functions)
 *TODO cars doesnt stop when traffic lights are red
 *
 *DONE make case in check_plusbus for the types of intersections.
 *DONE finish the red checker
 *DONE move radius in node.h
 *DONE change all link link to intersection intersection in function parameters*/

#include "trafficlights.h"


void light_control(){
    /*5 change_lights functions should be called in this function*/
}

int type_check(intersection *intersection, intersection_type type){
    /*switch (type){
        case C: return intersection->layout.type_c; break;
        case D: return intersection->layout.type_d; break;
        case E: return intersection->layout.type_e; break;
        case F: return intersection->layout.type_f; break;
    }*/
}

void direction_stop(intersection *intersection, vehicle *actor, link *links, intersection_type type){
    static int h, count;
    h = 0;
    count = 0;
    switch (type){
    case C:
        if(state_of_intersection(type, intersection) == Red){
            //id = link->road[links[0].len-1];
                if(lead_gap(links, i) < 5 && actor[links[0].road[24]].v == 5)
            links[0].len - 5;
            actor[links[0].road[24]].v = 0;

                int car_found = 0;
                int i = 2;
                if(links[0].road[ROAD_LENGTH -1] == 0){
                    while (!car_found) {
                        if(i <= 6) {
                            h = links[0].road[ROAD_LENGTH - i];
                            if (links[0].road[ROAD_LENGTH - i] != 0) {
                                actor[h].v = gap;
                                car_found = 1;
                            }
                        }
                        i++;
                    }
                }

            /*actor[links[intersection->layout.type_c.links[4]].len -1].v = 0;
            actor[links[intersection->layout.type_c.links[9]].len -1].v = 0;
            actor[links[intersection->layout.type_c.links[11]].len -1].v = 0;*/

            /*Cars on the prioritization road stops for red*/
        }else{
            //actor[links[intersection->layout.type_c.links[2]].len -1].v = 0;
            //actor[links[intersection->layout.type_c.links[6]].len -1].v = 0;
            /*Cars on the non prioritization road stops for red*/
        }
    break;
    case D: break;
    case E: break;
    case F: break;
    }
}

int check_plusbus(int r, intersection *intersection, vehicle *actor, link *links, int lane){
    int i, run = 0, radius;

    radius = links[lane].len - r;
    for(i = 1; i <= AMOUNT_VEHICLES; i++){
        if(actor[i].is_plusbus == 1 && links[lane].road[radius] == actor[i].id)
            run = 1;
    }
    return run;
}

void change_lights(intersection *intersection, vehicle *actor, link *links, int lane, intersection_type type){
    static int count = 0;
    int state = intersection->layout.type_c.state;

    /*Checks if the plusbus is in radius for prioritization*/
    int pb = check_plusbus(PLUSBUS_R, intersection, actor, links, lane);
    if(pb == 1 && state == Green && count < PLUSBUS_R){
        count += PLUSBUS_GREEN_ADJUST;
    }else if(pb == 1 && state == Red){
        count = PLUSBUS_RED_ADJUST;
    }

    state_counter(intersection, &count);
    direction_stop(intersection, actor, links, type);
    count++;
}

void state_counter(intersection *intersection, int *count){
    int *state = intersection->layout.type_c.state;
    if(count == RED_T && state == Red){
        *count = 0;
        *state = Green;
    }else if(count == GREEN_T && state == Green){
        *count = 0;
        *state = Red;
    }
}

int state_of_intersection(intersection_type type, struct intersection *intersection){
    switch (type) {
        case C:     return intersection->layout.type_c.state;
        /*case D:   return intersection->layout.type_d.state;
        case E:     return intersection->layout.type_e.state;
        case F:     return intersection->layout.type_f.state;*/
    }
    return 0;
}