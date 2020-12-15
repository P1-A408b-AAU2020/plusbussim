#include "node.h"
#include "debug.h"

/*Checks if the plusbus is near intersection*/
int check_plusbus(link *link, vehicle *vehicle);

/*Prioritizes plusbus on current lane*/
void prioritize_plusbus(link *link, vehicle *vehicle);

/*Changes lights green/red and resets counter for all intersections*/
void change_state(intersection *intersection);

/*returns state of selected intersection*/
light_data* i_data(link *link);

/*Runs intersection control from type*/
int traffic_light(link *link, vehicle *vehicle);

/*Stops car on link*/
void link_stop(link *link, vehicle *vehicle);

/*Stops vehicles on correct road in type c intersection*/
int intersection_control_type_c(vehicle *vehicle, link *link, int pb_e1, int pb_e2,int l_e1,int l_e2,int l_e3,int l_e4);
/*Stops vehicles on correct road in type d intersection*/
int intersection_control_type_d(vehicle *vehicle, link *link, int pb_e, int l_e1, int l_e2, int l_e3);
/*Stops vehicles on correct road in type e intersection*/
int intersection_control_type_e(vehicle *vehicle, link *link, int pb_e, int l_e1,int l_e2,int l_e3,int l_e4);