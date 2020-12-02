/*TODO add "trafficlights.c trafficlights.h" to CMakeLists.txt when this library is done
 *TODO make it work on more than one road and fix hardcoded solution(may need recursive functions)
 *
 * 
 *DONE make case in check_plusbus for the types of intersections.
 *DONE finish the red checker
 *DONE move radius in node.h
 *DONE change all link link to intersection intersection in function parameters*/

#include "trafficlights.h"
#include "node.h"

void light_control(){
    /*5 change_lights functions should be called in this function*/
}

void car_stops(intersection *intersection, vehicle *actor, link *links, intersection_type type){
    switch (type){
    case C: 
        if(intersection->layout.type_c.state == Red){
            //id = link->road[links[0].len-1];
            actor[links[p[0]].len -1].v = 0;
            actor[links[p[4]].len -1].v = 0;
            actor[links[p[9]].len -1].v = 0;
            actor[links[p[11]].len -1].v = 0;
            /*Cars on the prioritization road stops for red*/
        } else{
            actor[links[p[2]].len -1].v = 0;
            actor[links[p[6]].len -1].v = 0;
            /*Cars on the non prioritization road stops for red*/
        }
    break;
    case D: break;
    case E: break;
    case F: break;
    }
}

int check_plusbus(int r, intersection *intersection, vehicle *actor, link *links, int lane, int *p){
    int i, run = 0, radius;

    radius = links[p.links[lane]].len - r;
    for(i = 1; i <= AMOUNT_VEHICLES; i++){
        if(actor[i].is_plusbus == 1 && links[p.links[lane]].road[radius] == actor[i].id)
            run = 1;
    }
    return run;
}

void change_lights(intersection *intersection, vehicle *actor, link *links, int lane, intersection_type type){
    int *p;
    static int count = 0;
    int pb = check_plusbus(PLUSBUSRADIUS, intersection, actor, links, lane, p);
    switch (type){
        case C: *p = intersection->layout.type_c; break;
        case D: *p = intersection->layout.type_d; break;
        case E: *p = intersection->layout.type_e; break;
        case F: *p = intersection->layout.type_f; break;
    }

    /*Checks if the plusbus is in radius for prioritization*/
    if(pb == 1 && p.state == Green && count < PLUSBUSRADIUS){
        count += 5;
    }else if(pb == 1 && p.state == Red){
        count = 5;
    }

    /*How much time before it should be red/green*/
    if(count == REDTIME && p.state == Red){
        count = 0;
        p.state = Green;
    }else if(count == GREENTIME && p.state == Green){
        count = 0;
        p.state = Red;
    }

    cars_stop(intersection, actor, links, type);
    count++;
}