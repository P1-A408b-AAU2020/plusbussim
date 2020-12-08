/*TODO add "trafficlights.c trafficlights.h" to CMakeLists.txt when this library is done*/
#include "trafficlights.h"

void link_stop(link *link, vehicle *vehicle){
    int car_found = 0;
    int i = 2, l;
    if(link->road[link->len - 1] == 0){
        while (!car_found) {
            if(i <= 6) {
                l = link->road[link->len - i];
                if (l != 0) {
                    vehicle[l].v = lead_gap(link, i);
                    car_found = 1;
                }
            }
            i++;
        }
    }
}

void direction_stop(intersection *intersection, vehicle *vehicle, link *link, i_type type){
    if(i_data(type, intersection) == Red){
        link_stop(link, vehicle);
    }else {
        link_stop(link, vehicle);
    }
}

int check_plusbus(int r, vehicle *vehicle, link *link){
    int i, run = 0, radius, l;
    radius = link->len - r;
    l = link->road[link->len - i];

    if(vehicle[l].is_plusbus == 1 && link->road[radius] == vehicle[l].id)
        run = 1;
    return run;
}

void change_lights(intersection *intersection, vehicle *actor, link *link, i_type type){
    int state = i_data(type, intersection)->state,
      counter = i_data(type, intersection)->counter;
    int pb = check_plusbus(PLUSBUS_R, actor, link);

    if(pb == 1 && state == Green && counter < PLUSBUS_R){
        i_data(type, intersection)->counter += PLUSBUS_GREEN_ADJUST;
    }else if(pb == 1 && state == Red){
        i_data(type, intersection)->counter = PLUSBUS_RED_ADJUST;
    }

    change_state(intersection, type);
    *counter++;
}

void change_state(intersection *intersection, i_type type){
    int state = i_data(type, intersection)->state,
      counter = i_data(type, intersection)->counter;

    if(counter == RED_T && state == Red){
        i_data(type, intersection)->counter = 0;
        i_data(type, intersection)->state = Green;
    }else if(counter == GREEN_T && state == Green){
        i_data(type, intersection)->counter = 0;
        i_data(type, intersection)->state = Red;
    }
}

light_data* i_data(i_type type, struct intersection *intersection){
    switch (type) {
        case C: return &intersection->layout.type_c.data;
        case D: return &intersection->layout.type_d.data;
        case E: return &intersection->layout.type_e.data;
        case F: return &intersection->layout.type_f.data;
    }
    return 0;
}