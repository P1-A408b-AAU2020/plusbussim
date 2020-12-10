#include "node.h"

/*Checks if the plusbus is near intersection*/
int check_plusbus(vehicle *vehicle, link *link);

/* Prioritizes plusbus on current lane in the traffic light */
void prioritize_plusbus(vehicle *vehicle, link *link);

/*Changes lights green/red and resets counter*/
void change_state(intersection *intersection);

/*returns state of selected intersection*/
light_data* i_data(link *link);

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