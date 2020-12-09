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

/*void direction_stop(intersection *intersection, vehicle *vehicle, link *link, i_type type){
    if(i_data(type, intersection) == Red){
        link_stop(link, vehicle);
    }else {
        link_stop(link, vehicle);
    }
}*/

int check_plusbus(int r, vehicle *vehicle, link *link){
    int i, run = 0, radius, l;
    radius = link->len - r;
    l = link->road[link->len - i];

    if(vehicle[l].is_plusbus == 1 && link->road[radius] == vehicle[l].id)
        run = 1;
    return run;
}

void prioritize_plusbus( intersection *intersection,vehicle *vehicle, link *link, i_type type){
    int state = i_data(type, intersection)->state,
      counter = i_data(type, intersection)->counter;
    int pb = check_plusbus(PLUSBUS_R, vehicle, link);
    if(pb == 1 && state == Green && counter < PLUSBUS_R){
        i_data(type, intersection)->counter += PLUSBUS_GREEN_ADJUST;
    }else if(pb == 1 && state == Red){
        i_data(type, intersection)->counter = PLUSBUS_RED_ADJUST;
    }
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
    i_data(type, intersection)->counter++;
}

light_data* i_data(i_type type, intersection *intersection){
    switch (type) {
        case C: return &intersection->layout.type_c.data;
        case D: return &intersection->layout.type_d.data;
        case E: return &intersection->layout.type_e.data;
        case F: return &intersection->layout.type_f.data;
    }
    return 0;
}

void get_i_type(intersection *intersection, int id, link *link, vehicle *vehicle){
    switch (intersection->type) {
        case 'c':
            if(intersection->id == id)
            intersection_traffic_lights_type_c(intersection, vehicle, link,
                                               intersection->layout.type_c.links[0],
                                               intersection->layout.type_c.links[0],
                                               intersection->layout.type_c.links[0],
                                               intersection->layout.type_c.links[0],
                                               intersection->layout.type_c.links[0],
                                               intersection->layout.type_c.links[0]);
        break;
        case 'd': break;
        case 'e':
            if(intersection->id == id)
                intersection_traffic_lights_type_e(intersection, vehicle, link,
                                                   intersection->layout.type_c.links[0],
                                                   intersection->layout.type_c.links[0],
                                                   intersection->layout.type_c.links[0],
                                                   intersection->layout.type_c.links[0],
                                                   intersection->layout.type_c.links[0])

        break;
        case 'f': break;
    }
}

void intersection_traffic_lights_type_c(intersection *intersection, vehicle *vehicle, link *link,
                              int pb_e1, int pb_e2,int l_e1,int l_e2,int l_e3,int l_e4){
    change_state(intersection, C);
    if(i_data(C, intersection) == Red) {
        if (link->id == pb_e1 || link->id == pb_e2 || link->id == l_e1 || link->id == link + l_e2) {
            if(link->id == pb_e1 || link->id == pb_e2)
                prioritize_plusbus(intersection, vehicle, link, C);
            link_stop(link, vehicle);
        }
    } else{
        if (link->id == l_e3 || link->id == l_e4) {
            link_stop(link, vehicle);
        }
    }
}

void intersection_traffic_lights_type_d(intersection *intersection, vehicle *vehicle, link *link,
                                        int pb_e, int l_e1, int l_e2, int l_e3){
    change_state(intersection, D);
    if(i_data(D, intersection) == Red){
        if(link->id == pb_e || link->id == l_e1 || link->id == l_e2){
            if(link->id == pb_e)
                prioritize_plusbus(intersection, vehicle, link, D);
            link_stop(link, vehicle);
        }
    } else{
        if(link->id == l_e3){
            prioritize_plusbus(intersection, vehicle, link, D);
            link_stop(link, vehicle)
        }
    }

}

void intersection_traffic_lights_type_e(intersection *intersection, vehicle *vehicle, link *link,
                                        int pb_e, int l_e1, int l_e2,int l_e3,int l_e4){
    change_state(intersection, E);
    if(i_data(C, intersection) == Red){
        if(link->id == pb_e || link->id == l_e1 || link->id == l_e2){
            if(link->id == pb_e || link->id == l_e2)
                prioritize_plusbus(intersection, vehicle, link, E);
            link_stop(link, vehicle);
        }
    } else{
        if (link->id == l_e3 || link->id == l_e4) {
            link_stop(link, vehicle);
        }
    }
}