/*Changes traffic lights from green to red and vise versa
  lane = where the plusbus is driving*/
void change_lights(intersection *intersection, vehicle *actor, link *links, int lane);
/*Checks if the plusbus is near intersection*/
int check_plusbus(int r, intersection *intersection, vehicle *actor, link *links, int lane);
/*checks for all intersections in current simulation*/
void light_control(intersection *intersection, vehicle *actor, link *links, int lane)