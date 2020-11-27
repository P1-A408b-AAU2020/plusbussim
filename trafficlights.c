/*TODO add "trafficlights.c trafficlights.h" to CMakeLists.txt when this library is done*/
#include "trafficlights.h"
#include "node.h"

#define RADIUS 10


enum light_state {Red, Green};

/*Checks if the plusbus is near intersection*/
int check_plusbus(int r, link link, vehicle *actor){
    int i, run = 0, radius;
    radius = link.len - r;
    for(i = 1; i <= AMOUNT_VEHICLES; i++){
        if(actor[i].is_plusbus == 1 && link.road[radius] == actor[i].id)
            run = 1;
    }
    return run;
}

/*changes traffic lights from green to red and vise versa*/
void change_lights(node *node, vehicle *actor, link *link){
    int id, count = 0;
    /*Checks if the plusbus is in radius for prioritization*/
    if(check_plusbus(RADIUS, *link, actor) == 1 && node.state == Green && count < RADIUS){
        count += 5;
    }else if(check_plusbus(RADIUS, *link, actor) == 1 && node.state == Red){
        count = 5;
    }

    /*How much time before it should be red/green*/
    if(count == 10 && node.state == Red){
        count = 0;
        node.state = Green;
    }else if(count == 10 && node.state == Green){
        count = 0;
        node.state = Red;
    }

    /*
     * if its red then stop the cars stop
     * Red light means that one direction stops and the other drives
     * and vise versa
     */
    if(node.state = Red){
        id = link->road[link->len-1];
        actor[id].v = 0;
        /*
         * Cars on the prioritization road stops for red
         */
    } else{
        /*
         * Cars on the non prioritization road stops for red
         */
    }
    count++;
}