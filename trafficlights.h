#include "node.h"
/*Checks and changes light states for all intersections in current simulation*/
void light_control();

/*Stops cars that have red*/
void direction_stop(intersection *intersection, vehicle *actor, link *links, i_type type);

/*Checks if the plusbus is near intersection*/
int check_plusbus(int r, vehicle *actor, link *links);

void prioritize_plusbus(vehicle *vehicle, link *link);

void traffic_timer(intersection *intersection);

/*Changes lights green/red and resets counter*/
void change_state(intersection *intersection);

/*returns state of selected intersection*/
light_data * i_data(i_type type, struct intersection *intersection);

/*runs correct traffic light control */
int traffic_light(link *link, vehicle *vehicle);

/*stops car on link*/
void link_stop(link *link, vehicle *vehicle);

/*Controls traffic lights of type c intersections*/
int intersection_traffic_lights_type_c(vehicle *vehicle, link *link, int pb_e1, int pb_e2,int l_e1,int l_e2,int l_e3,int l_e4);
/*Controls traffic lights of type d intersections*/
int intersection_traffic_lights_type_d(vehicle *vehicle, link *link, int pb_e, int l_e1, int l_e2, int l_e3);
/*Controls traffic lights of type e intersections*/
int intersection_traffic_lights_type_e(vehicle *vehicle, link *link, int pb_e, int l_e1,int l_e2,int l_e3,int l_e4);