/*TODO add "trafficlights.c trafficlights.h" to CMakeLists.txt when this library is done
 *TODO make it work on more than one road and fix hardcoded solution(may need recursive functions)
 *TODO finish the red checker
 *TODO move radius in node.h
 *
 *DONE change all link link to intersection intersection in function parameters*/

#include "trafficlights.h"
#include "node.h"

#define RADIUS 10


enum light_state {Red, Green};

/*Checks if the plusbus is near intersection*/
int check_plusbus(int r, intersection *intersection, vehicle *actor, link *links){
    int i, run = 0, radius;
    int *p = intersection->layout.type_c.links;
    radius = links[p[0]].len - r;
    for(i = 1; i <= AMOUNT_VEHICLES; i++){
        if(actor[i].is_plusbus == 1 && links[p[0]].road[radius] == actor[i].id)
            run = 1;
    }
    return run;
}



/*changes traffic lights from green to red and vise versa*/
void change_lights(intersection *intersection, vehicle *actor, link *links){
    int id;
    int *p = intersection->layout.type_c.links;
    static int count = 0;
    /*Checks if the plusbus is in radius for prioritization*/
    if(check_plusbus(RADIUS, intersection, actor, links) == 1 && intersection->layout.type_c.state == Green && count < RADIUS){
        count += 5;
    }else if(check_plusbus(RADIUS, intersection, actor, links) == 1 && intersection->layout.type_c.state == Red){
        count = 5;
    }

    /*How much time before it should be red/green*/
    if(count == 10 && intersection->layout.type_c.state == Red){
        count = 0;
        intersection->layout.type_c.state = Green;
    }else if(count == 10 && intersection->layout.type_c.state == Green){
        count = 0;
        intersection->layout.type_c.state = Red;
    }

    /*
     * if its red then stop the cars stop
     * Red light means that one direction stops and the other drives
     * and vise versa
     */
    if(intersection->layout.type_c.state == Red){
        //id = link->road[links[0].len-1];
        id = links[p[0]].len -1;
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