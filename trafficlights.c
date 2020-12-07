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

void car_stops(intersection *intersection, vehicle *actor, link *links, intersection_type type){
    static int b, count;
    b = 0;
    count = 0;
    switch (type){
    case C:
        if(intersection->layout.type_c.state == Red){
            //id = link->road[links[0].len-1];
            for (int i = ROAD_LENGTH-1; i <= ROAD_LENGTH -6; i--) {
                if (count < 5){
                    if(links[0].road[i] != 0)
                        actor[links[0].road[i]].v = 1;
                    count++;
                }
            }

            actor[links[0].road[24]].v = 0;

            /*actor[links[intersection->layout.type_c.links[4]].len -1].v = 0;
            actor[links[intersection->layout.type_c.links[9]].len -1].v = 0;
            actor[links[intersection->layout.type_c.links[11]].len -1].v = 0;*/

            /*Cars on the prioritization road stops for red*/
        } else{
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

    radius = links[intersection->layout.type_c.links[lane]].len - r;
    for(i = 1; i <= AMOUNT_VEHICLES; i++){
        if(actor[i].is_plusbus == 1 && links[intersection->layout.type_c.links[lane]].road[radius] == actor[i].id)
            run = 1;
    }
    return run;
}

void change_lights(intersection *intersection, vehicle *actor, link *links, int lane, intersection_type type){
    static int count = 0;
    int pb = check_plusbus(PLUSBUS_RADIUS, intersection, actor, links, lane);
    
    /*Checks if the plusbus is in radius for prioritization*/
    if(pb == 1 && intersection->layout.type_c.state == Green && count < PLUSBUS_RADIUS){
        count += PLUSBUS_GREEN_ADJUST;
    }else if(pb == 1 && intersection->layout.type_c.state == Red){
        count = PLUSBUS_RED_ADJUST;
    }

    /*How much time before it should be red/green*/
    if(count == RED_TIME && intersection->layout.type_c.state == Red){
        count = 0;
        intersection->layout.type_c.state = Green;
    }else if(count == GREEN_TIME && intersection->layout.type_c.state == Green){
        count = 0;
        intersection->layout.type_c.state = Red;
    }

    car_stops(intersection, actor, links, type);
    count++;
    //printf("\ncounter: %-5d state: %-5d speed: %-5d", count, intersection->layout.type_c.state, actor[links[intersection->layout.type_c.links[0]].len -1].v);
}