/*Checks for all intersections in current simulation*/
void light_control();

/*Stops cars that have red*/
void cars_stop(intersection *intersection, vehicle *actor, link *links, intersection_type type);

/*Checks if the plusbus is near intersection*/
int check_plusbus(int r, intersection *intersection, vehicle *actor, link *links, int lane, int *p);

/*Changes traffic lights from green to red and vise versa
  lane = where the plusbus is driving*/
void change_lights(intersection *intersection, vehicle *actor, link *links, int lane, intersection_type type);