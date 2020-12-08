#include "node.h"
#include <stdio.h>
/*Checks and changes light states for all intersections in current simulation*/
void light_control();

/*Stops cars that have red*/
void direction_stop(intersection *intersection, vehicle *actor, link *links, i_type type);

/*Checks if the plusbus is near intersection*/
int check_plusbus(int r, vehicle *actor, link *links);


void change_lights(intersection *intersection, vehicle *actor, link *links, i_type type);

/*Changes lights green/red and resets counter*/
void change_state(intersection *intersection, i_type type);

/*returns state of selected intersection*/
light_data * i_data(i_type type, struct intersection *intersection);

/*stops car on link*/
void link_stop(link *link, vehicle *vehicle);
