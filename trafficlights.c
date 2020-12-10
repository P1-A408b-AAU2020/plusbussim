#include "trafficlights.h"
#include <stdio.h>

void link_stop(link *link, vehicle *vehicle){
    int car_found = 0;
    int i = 2, l, p;
    if(link->road[link->len - 1] == 0){
        while (!car_found) {
            if(i <= 6) {
                l = link->road[link->len - i];
                if (l != 0) {
                    vehicle[l-1].v = i - 1;
                    car_found = 1;
                }
            }
            i++;
        }
    }
    else {
        p = link->road[link->len - 1];
        vehicle[p-1].v = 0;
    }

}

int check_plusbus(vehicle *vehicle, link *link){
    int run = 0, l, plusbus_found = 0, i = 1;

    while (!plusbus_found) {
        if(i <= PLUSBUS_R) {
            l = link->road[link->len - i];
                if(l != 0 && vehicle[l-1].is_plusbus) {
                 run = 1;
                 plusbus_found = 1;
            }
        }
        i++;
    }
    return run;
}

void prioritize_plusbus(vehicle *vehicle, link *link){
    int pb = check_plusbus(vehicle, link);
    printf(" RUN = %d \n", pb);
    switch (link->intersection->type){
        case 'c':
            if(pb == 1 && link->intersection->layout.type_c.data.state == Green && link->intersection->layout.type_c.data.counter < PLUSBUS_R){
                link->intersection->layout.type_c.data.counter += PLUSBUS_GREEN_ADJUST;
            }else if(pb == 1 && link->intersection->layout.type_c.data.state == Red){
                link->intersection->layout.type_c.data.counter += PLUSBUS_RED_ADJUST;
            }
            break;

        case 'd':
            if(pb == 1 && link->intersection->layout.type_d.data.state == Green && link->intersection->layout.type_d.data.counter < PLUSBUS_R){
                link->intersection->layout.type_d.data.counter += PLUSBUS_GREEN_ADJUST;
            }else if(pb == 1 && link->intersection->layout.type_d.data.state == Red){
                link->intersection->layout.type_d.data.counter += PLUSBUS_RED_ADJUST;
            }
            break;

        case 'e':
            if(pb == 1 && link->intersection->layout.type_e.data.state == Green && link->intersection->layout.type_e.data.counter < PLUSBUS_R){
                link->intersection->layout.type_e.data.counter += PLUSBUS_GREEN_ADJUST;
            }else if(pb == 1 && link->intersection->layout.type_e.data.state == Red){
                link->intersection->layout.type_e.data.counter += PLUSBUS_RED_ADJUST;
            }
            break;
    }
}


void change_state(intersection *intersection){
    int i;
    for (i = 0; i < 9; i++) {
        switch ((intersection+i)->type) {
            case 'c':
                if ((intersection+i)->layout.type_c.data.counter >= RED_T &&
                    (intersection+i)->layout.type_c.data.state == Red) {
                    (intersection+i)->layout.type_c.data.counter = 0;
                    (intersection+i)->layout.type_c.data.state = Green;
                } else if ((intersection+i)->layout.type_c.data.counter >= GREEN_T &&
                        (intersection+i)->layout.type_c.data.state == Green) {
                    (intersection+i)->layout.type_c.data.counter = 0;
                    (intersection+i)->layout.type_c.data.state = Red;
                }
                (intersection+i)->layout.type_c.data.counter++;
                printf("ID: %-3d STATE: %-3d COUNTER: %d\n", (intersection+i)->id,(intersection+i)->layout.type_c.data.state, (intersection+i)->layout.type_c.data.counter);
                break;
            case 'd':
                if ((intersection+i)->layout.type_d.data.counter >= RED_T &&
                    (intersection+i)->layout.type_d.data.state == Red) {
                    (intersection+i)->layout.type_d.data.counter = 0;
                    (intersection+i)->layout.type_d.data.state = Green;
                } else if ((intersection+i)->layout.type_d.data.counter >= GREEN_T &&
                    (intersection+i)->layout.type_d.data.state == Green) {
                    (intersection+i)->layout.type_d.data.counter = 0;
                    (intersection+i)->layout.type_d.data.state = Red;
                }
                (intersection+i)->layout.type_d.data.counter++;
                printf("ID: %-3d STATE: %-3d COUNTER: %d\n", (intersection+i)->id,(intersection+i)->layout.type_d.data.state, (intersection+i)->layout.type_d.data.counter);
                break;
            case 'e':
                if ((intersection+i)->layout.type_e.data.counter >= RED_T &&
                    (intersection+i)->layout.type_e.data.state == Red) {
                    (intersection+i)->layout.type_e.data.counter = 0;
                    (intersection+i)->layout.type_e.data.state = Green;
                } else if ((intersection+i)->layout.type_e.data.counter >= GREEN_T &&
                    (intersection+i)->layout.type_e.data.state == Green) {
                    (intersection+i)->layout.type_e.data.counter = 0;
                    (intersection+i)->layout.type_e.data.state = Red;
                }
                (intersection+i)->layout.type_e.data.counter++;
                printf("ID: %-3d STATE: %-3d COUNTER: %d\n", (intersection+i)->id,(intersection+i)->layout.type_e.data.state, (intersection+i)->layout.type_e.data.counter);
                break;
        }
    }
}

light_data* i_data(link *link){
    switch (link->intersection->type) {
        case 'c': return &link->intersection->layout.type_c.data;
        case 'd': return &link->intersection->layout.type_d.data;
        case 'e': return &link->intersection->layout.type_e.data;
        default: return 0;
    }
}

int traffic_light(link *link, vehicle *vehicle){
    /*printf("test counter %d \n", i_data(link)->counter);*/
    switch (link->intersection->type) {
        case 'c':
             return intersection_traffic_lights_type_c(vehicle, link,
                                               link->intersection->layout.type_c.links[10]->id,
                                               link->intersection->layout.type_c.links[8]->id,
                                               link->intersection->layout.type_c.links[0]->id,
                                               link->intersection->layout.type_c.links[4]->id,
                                               link->intersection->layout.type_c.links[2]->id,
                                               link->intersection->layout.type_c.links[6]->id);
        case 'd':
            return intersection_traffic_lights_type_d(vehicle, link,
                                               link->intersection->layout.type_d.links[7]->id,
                                               link->intersection->layout.type_d.links[1]->id,
                                               link->intersection->layout.type_d.links[5]->id,
                                               link->intersection->layout.type_d.links[3]->id);
        case 'e':
                return intersection_traffic_lights_type_e(vehicle, link,
                                                   link->intersection->layout.type_e.links[8]->id,
                                                   link->intersection->layout.type_e.links[6]->id,
                                                   link->intersection->layout.type_e.links[2]->id,
                                                   link->intersection->layout.type_e.links[0]->id,
                                                   link->intersection->layout.type_e.links[4]->id);

        default: return Green;
    }
}

int intersection_traffic_lights_type_c(vehicle *vehicle, link *link,
                              int pb_e1, int pb_e2,int l_e1,int l_e2,int l_e3,int l_e4){
    if(link->intersection->layout.type_c.data.state == Red) {
        if (link->id == pb_e1 || link->id == pb_e2 || link->id == l_e1 || link->id == l_e2) {
            if(link->id == pb_e1 || link->id == pb_e2)
                prioritize_plusbus(vehicle, link);
            link_stop(link, vehicle);
            return Red;

        }
    } else{
        if (link->id == l_e3 || link->id == l_e4) {
            link_stop(link, vehicle);
            return Red;
        }
    }
    return Green;
}

int intersection_traffic_lights_type_d(vehicle *vehicle, link *link,
                                        int pb_e, int l_e1, int l_e2, int l_e3){
    if(link->intersection->layout.type_d.data.state == Red){
        if(link->id == pb_e || link->id == l_e1 || link->id == l_e2){
            if(link->id == pb_e)
                prioritize_plusbus(vehicle, link);
            link_stop(link, vehicle);
            return Red;
        }
    } else{
        if(link->id == l_e3){
            prioritize_plusbus(vehicle, link);
            link_stop(link, vehicle);
            return Red;
        }
    }
    return Green;
}

int intersection_traffic_lights_type_e(vehicle *vehicle, link *link,
                                        int pb_e, int l_e1, int l_e2,int l_e3,int l_e4){
    if(link->intersection->layout.type_c.data.state == Red){
        if(link->id == pb_e || link->id == l_e1 || link->id == l_e2){
            if(link->id == pb_e || link->id == l_e2)
                prioritize_plusbus(vehicle, link);
            link_stop(link, vehicle);
            return Red;
        }
    } else{
        if (link->id == l_e3 || link->id == l_e4) {
            link_stop(link, vehicle);
            return Red;
        }
    }
    return Green;
}

