#include "node.h"
#include <stdio.h>
/*Checks and changes light states for all intersections in current simulation*/
void light_control();

/*Stops cars that have red*/
void direction_stop(intersection *intersection, vehicle *actor, link *links, intersection_type type);

/*Checks if the plusbus is near intersection*/
int check_plusbus(int r, intersection *intersection, vehicle *actor, link *links, int lane);


void change_lights(intersection *intersection, vehicle *actor, link *links, int lane, intersection_type type);

/*Changes lights green/red and resets counter*/
void state_counter(intersection *intersection, int *count);

/*returns state of selected intersection*/
int state_of_intersection(intersection_type type, struct intersection *intersection);
