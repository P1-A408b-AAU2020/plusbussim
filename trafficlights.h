#include "node.h"
#include "debug.h"


int check_plusbus(link *link, vehicle *vehicle);
void prioritize_plusbus(link *link, vehicle *vehicle);
void change_state(intersection *intersection);
int traffic_light(link *link, vehicle *vehicle);
void link_stop(link *link, vehicle *vehicle);


int intersection_control_type_c(vehicle *vehicle, link *link, int pb_e1, int pb_e2,int l_e1,int l_e2,int l_e3,int l_e4);

int intersection_control_type_d(vehicle *vehicle, link *link, int pb_e, int l_e1, int l_e2, int l_e3);

int intersection_control_type_e(vehicle *vehicle, link *link, int pb_e, int l_e1,int l_e2,int l_e3,int l_e4);