/*TODO add "trafficlights.c trafficlights.h" to CMakeLists.txt when this library is done*/
#include "trafficlights.h"
#include <stdio.h>

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

int check_plusbus(int r, vehicle *vehicle, link *link){
    int run = 0, radius, l;
    radius = link->len - r;
    l = link->road[link->len - 1];

    if(vehicle[l].is_plusbus == 1 && link->road[radius] == vehicle[l].id)
        run = 1;
    return run;
}

void prioritize_plusbus(vehicle *vehicle, link *link){
    int pb = check_plusbus(PLUSBUS_R, vehicle, link);
    switch (link->intersection->type){
        case 'c':
            if(pb == 1 && link->intersection->layout.type_c.data.state == Green && link->intersection->layout.type_c.data.counter < PLUSBUS_R){
                link->intersection->layout.type_c.data.counter += PLUSBUS_GREEN_ADJUST;
            }else if(pb == 1 && link->intersection->layout.type_c.data.state == Red){
                link->intersection->layout.type_c.data.counter = PLUSBUS_RED_ADJUST;
            }
            break;
    }
}

/*void traffic_timer(intersection *intersection){
    switch (intersection->type) {
        case 'c': intersection->layout.type_c.data.counter++;
        case 'd': intersection->layout.type_d.data.counter++;
        case 'e': intersection->layout.type_e.data.counter++;
    }
}*/

void change_state(link *link){
    /*int state = i_data(type, intersection)->state,
      counter = i_data(type, intersection)->counter;*/

    switch (link->intersection->type) {
        case 'c':
            if(link->intersection->layout.type_c.data.counter == RED_T && link->intersection->layout.type_c.data.state == Red){
                link->intersection->layout.type_c.data.counter = 0;
                link->intersection->layout.type_c.data.state = Green;
            }else if(link->intersection->layout.type_c.data.counter == GREEN_T && link->intersection->layout.type_c.data.state == Green){
                link->intersection->layout.type_c.data.counter = 0;
                link->intersection->layout.type_c.data.state = Red;
            }
            link->intersection->layout.type_c.data.counter++;
            break;
        case 'd':
            if(link->intersection->layout.type_d.data.counter == RED_T && link->intersection->layout.type_d.data.state == Red){
                link->intersection->layout.type_d.data.counter = 0;
                link->intersection->layout.type_d.data.state = Green;
            }else if(link->intersection->layout.type_d.data.counter == GREEN_T && link->intersection->layout.type_d.data.state == Green){
                link->intersection->layout.type_d.data.counter = 0;
                link->intersection->layout.type_d.data.state = Red;
            }
            link->intersection->layout.type_d.data.counter++;
        break;
        case 'e':
            if(link->intersection->layout.type_e.data.counter == RED_T && link->intersection->layout.type_e.data.state == Red){
                link->intersection->layout.type_e.data.counter = 0;
                link->intersection->layout.type_e.data.state = Green;
            }else if(link->intersection->layout.type_e.data.counter == GREEN_T && link->intersection->layout.type_e.data.state == Green){
                link->intersection->layout.type_e.data.counter = 0;
                link->intersection->layout.type_e.data.state = Red;
            }
            link->intersection->layout.type_e.data.counter++;
            break;
    }
    /*if(counter == RED_T && state == Red){
        i_data(type, intersection)->counter = 0;
        i_data(type, intersection)->state = Green;
    }else if(counter == GREEN_T && state == Green){
        i_data(type, intersection)->counter = 0;
        i_data(type, intersection)->state = Red;
    }*/
    //i_data(type, intersection)->counter++;
}

light_data* i_data(i_type type, intersection *intersection){
    switch (type) {
        case C: return &intersection->layout.type_c.data;
        case D: return &intersection->layout.type_d.data;
        case E: return &intersection->layout.type_e.data;
        /*case F: return &intersection->layout.type_f.data;*/
        default: return 0;
    }
}

void traffic_light(link *link, vehicle *vehicle){
    switch (link->intersection->type) {
        case 'c':
            intersection_traffic_lights_type_c(vehicle, link,
                                               link->intersection->layout.type_c.links[10]->id,
                                               link->intersection->layout.type_c.links[8]->id,
                                               link->intersection->layout.type_c.links[0]->id,
                                               link->intersection->layout.type_c.links[4]->id,
                                               link->intersection->layout.type_c.links[2]->id,
                                               link->intersection->layout.type_c.links[6]->id);
        break;
        case 'd':
            intersection_traffic_lights_type_d(vehicle, link,
                                               link->intersection->layout.type_d.links[7]->id,
                                               link->intersection->layout.type_d.links[1]->id,
                                               link->intersection->layout.type_d.links[0]->id,
                                               link->intersection->layout.type_d.links[3]->id);
        break;
        case 'e':
                intersection_traffic_lights_type_e(vehicle, link,
                                                   link->intersection->layout.type_e.links[8]->id,
                                                   link->intersection->layout.type_e.links[1]->id,
                                                   link->intersection->layout.type_e.links[2]->id,
                                                   link->intersection->layout.type_e.links[0]->id,
                                                   link->intersection->layout.type_e.links[4]->id);

        break;
        /*case 'f': break;*/
    }
}

void intersection_traffic_lights_type_c(vehicle *vehicle, link *link,
                              int pb_e1, int pb_e2,int l_e1,int l_e2,int l_e3,int l_e4){
    change_state(link);
    if(link->intersection->layout.type_c.data.state == Red) {
        if (link->id == pb_e1 || link->id == pb_e2 || link->id == l_e1 || link->id == l_e2) {
            if(link->id == pb_e1 || link->id == pb_e2)
                prioritize_plusbus(vehicle, link);
            link_stop(link, vehicle);
        }
    } else{
        if (link->id == l_e3 || link->id == l_e4) {
            link_stop(link, vehicle);
        }
    }
}

void intersection_traffic_lights_type_d(vehicle *vehicle, link *link,
                                        int pb_e, int l_e1, int l_e2, int l_e3){
    change_state(link);
    if(link->intersection->layout.type_d.data.state == Red){
        if(link->id == pb_e || link->id == l_e1 || link->id == l_e2){
            if(link->id == pb_e)
                prioritize_plusbus(vehicle, link);
            link_stop(link, vehicle);
        }
    } else{
        if(link->id == l_e3){
            prioritize_plusbus(vehicle, link);
            link_stop(link, vehicle);
        }
    }

}

void intersection_traffic_lights_type_e(vehicle *vehicle, link *link,
                                        int pb_e, int l_e1, int l_e2,int l_e3,int l_e4){
    change_state(link);
    if(link->intersection->layout.type_c.data.state == Red){
        if(link->id == pb_e || link->id == l_e1 || link->id == l_e2){
            if(link->id == pb_e || link->id == l_e2)
                prioritize_plusbus(vehicle, link);
            link_stop(link, vehicle);
        }
    } else{
        if (link->id == l_e3 || link->id == l_e4) {
            link_stop(link, vehicle);
        }
    }
}