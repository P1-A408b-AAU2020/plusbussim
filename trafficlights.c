#include "trafficlights.h"

/*Stops the first vehicle on link, because there is a red light */
void link_stop(link *link, vehicle *vehicle) {
  int car_found = 0;
  int i = 2, pos;

  /*Runs if there isn't a vehicle in the last cell of a link*/
  if (link->road[link->len - 1] == 0) {
    while (!car_found) {
      /*
       * Searches for a car in a radius from 2-6 away from the last cell
       * sets car_found to 1 if a car has been found
       * */
      if (i <= 6) {
        pos = link->road[link->len - i];
        if (pos != 0) {
          vehicle[pos - 1].v = i - 1;
          car_found = 1;
        }
      }
      else
        break;
      i++;
    }
  } else { /*else it stops the car in the last cell*/
    pos = link->road[link->len - 1];
    vehicle[pos - 1].v = 0;
  }

}

/*Checks if the plusbus is near intersection*/
int check_plusbus(link *link, vehicle *vehicle) {
  int pos, plusbus_found = 0, i = 1;

  while (!plusbus_found) {
    if (i <= PLUSBUS_R) {
      pos = link->road[link->len - i];
      if (pos != 0 && vehicle[pos - 1].is_plusbus) {
        plusbus_found = 1;
      }
    }
    else {
      break;
    }
    i++;
  }
  return plusbus_found;
}

/*Prioritizes plusbus on current link. */
void prioritize_plusbus(link *link, vehicle *vehicle) {
  int plusbus_found = check_plusbus(link, vehicle);
  switch (link->intersection->type) {
    case 'c':
      if (plusbus_found == 1 && link->intersection->layout.type_c.data.state == Green && link->intersection->layout.type_c.data.counter < PLUSBUS_R && link->intersection->layout.type_c.data.counter != 0) {
        link->intersection->layout.type_c.data.counter -= PLUSBUS_GREEN_ADJUST;
      } else if (plusbus_found == 1 && link->intersection->layout.type_c.data.state == Red) {
        link->intersection->layout.type_c.data.counter += PLUSBUS_RED_ADJUST;
      }
      break;

    case 'd':
      if (plusbus_found == 1 && link->intersection->layout.type_d.data.state == Green && link->intersection->layout.type_d.data.counter < PLUSBUS_R && link->intersection->layout.type_d.data.counter != 0) {
        link->intersection->layout.type_d.data.counter -= PLUSBUS_GREEN_ADJUST;
      } else if (plusbus_found == 1 && link->intersection->layout.type_d.data.state == Red) {
        link->intersection->layout.type_d.data.counter += PLUSBUS_RED_ADJUST;
      }
      break;

    case 'e':
      if (plusbus_found == 1 && link->intersection->layout.type_e.data.state == Green && link->intersection->layout.type_e.data.counter < PLUSBUS_R && link->intersection->layout.type_c.data.counter != 0) {
        link->intersection->layout.type_e.data.counter -= PLUSBUS_GREEN_ADJUST;
      } else if (plusbus_found == 1 && link->intersection->layout.type_e.data.state == Red) {
        link->intersection->layout.type_e.data.counter += PLUSBUS_RED_ADJUST;
      }
      break;
  }
}

/* Changes lights green/red and resets counter for all intersections */
void change_state(intersection *intersection) {
  int i;
  for (i = 0; i < 9; i++) {
    switch ((intersection + i)->type) {
      case 'c':
        if ((intersection + i)->layout.type_c.data.counter >= RED_T && (intersection + i)->layout.type_c.data.state == Red) {
          (intersection + i)->layout.type_c.data.counter = 0;
          (intersection + i)->layout.type_c.data.state = Green;
        } else if ((intersection + i)->layout.type_c.data.counter >= GREEN_T && (intersection + i)->layout.type_c.data.state == Green) {
          (intersection + i)->layout.type_c.data.counter = 0;
          (intersection + i)->layout.type_c.data.state = Red;
        }
        (intersection + i)->layout.type_c.data.counter++;

        if (DEBUG)
          printf("TYPE: %-3c ID: %-3d STATE: %-3d COUNTER: %d\n", (intersection + i)->type, (intersection + i)->id,
                 (intersection + i)->layout.type_c.data.state, (intersection + i)->layout.type_c.data.counter);

        break;
      case 'd':
        if ((intersection + i)->layout.type_d.data.counter >= RED_T && (intersection + i)->layout.type_d.data.state == Red) {
          (intersection + i)->layout.type_d.data.counter = 0;
          (intersection + i)->layout.type_d.data.state = Green;
        } else if ((intersection + i)->layout.type_d.data.counter >= GREEN_T &&
                   (intersection + i)->layout.type_d.data.state == Green) {
          (intersection + i)->layout.type_d.data.counter = 0;
          (intersection + i)->layout.type_d.data.state = Red;
        }
        (intersection + i)->layout.type_d.data.counter++;

        if (DEBUG)
          printf("TYPE: %-3c ID: %-3d STATE: %-3d COUNTER: %d\n", (intersection + i)->type, (intersection + i)->id,
                 (intersection + i)->layout.type_d.data.state, (intersection + i)->layout.type_d.data.counter);

        break;
      case 'e':
        if ((intersection + i)->layout.type_e.data.counter >= RED_T && (intersection + i)->layout.type_e.data.state == Red) {
          (intersection + i)->layout.type_e.data.counter = 0;
          (intersection + i)->layout.type_e.data.state = Green;
        } else if ((intersection + i)->layout.type_e.data.counter >= GREEN_T && (intersection + i)->layout.type_e.data.state == Green) {
          (intersection + i)->layout.type_e.data.counter = 0;
          (intersection + i)->layout.type_e.data.state = Red;
        }
        (intersection + i)->layout.type_e.data.counter++;

        if (DEBUG)
          printf("TYPE: %-3c ID: %-3d STATE: %-3d COUNTER: %d\n", (intersection + i)->type, (intersection + i)->id,
                 (intersection + i)->layout.type_e.data.state, (intersection + i)->layout.type_e.data.counter);
        break;
    }
  }
}

light_data* i_data(link *link) {
  switch (link->intersection->type) {
    case 'c': return &link->intersection->layout.type_c.data;
    case 'd': return &link->intersection->layout.type_d.data;
    case 'e': return &link->intersection->layout.type_e.data;
    default: return 0;
  }
}

/*Runs intersection control based on the type of intersection*/
int traffic_light(link *link, vehicle *vehicle) {
  switch (link->intersection->type) {
    case 'c':
      return intersection_control_type_c(vehicle, link,
                                                link->intersection->layout.type_c.links[10]->id,
                                                link->intersection->layout.type_c.links[8]->id,
                                                link->intersection->layout.type_c.links[0]->id,
                                                link->intersection->layout.type_c.links[4]->id,
                                                link->intersection->layout.type_c.links[2]->id,
                                                link->intersection->layout.type_c.links[6]->id);
    case 'd':
      return intersection_control_type_d(vehicle, link,
                                                link->intersection->layout.type_d.links[7]->id,
                                                link->intersection->layout.type_d.links[1]->id,
                                                link->intersection->layout.type_d.links[5]->id,
                                                link->intersection->layout.type_d.links[3]->id);
    case 'e':
      return intersection_control_type_e(vehicle, link,
                                                link->intersection->layout.type_e.links[6]->id,
                                                link->intersection->layout.type_e.links[8]->id,
                                                link->intersection->layout.type_e.links[2]->id,
                                                link->intersection->layout.type_e.links[0]->id,
                                                link->intersection->layout.type_e.links[4]->id);

    default:
      return 1;
  }
}

/* Checks which links should be stopped because of red light in type c intersection */
int intersection_control_type_c(vehicle *vehicle, link *link,
                              int pb_l1, int pb_l2,int car_l1,int car_l2,int car_l3,int car_l4) {
  if (link->intersection->layout.type_c.data.state == Red) {
    if (link->id == pb_l1 || link->id == pb_l2 || link->id == car_l1 || link->id == car_l2) { /*Runs if current link is one of these roads*/
      if (link->id == pb_l1 || link->id == pb_l2) /*Runs if current link is a plusbus link*/
        prioritize_plusbus(link, vehicle);
      link_stop(link, vehicle);
      return Red;

    }
  } else {
    if (link->id == car_l3 || link->id == car_l4) {
      link_stop(link, vehicle);
      return Red;
    }
  }
  return Green;
}

/* Checks which links should be stopped because of red light in type d intersection */
int intersection_control_type_d(vehicle *vehicle, link *link,
                                        int pb_l, int car_l1, int car_l2, int car_l3) {
  if (link->intersection->layout.type_d.data.state == Red) {
    if (link->id == pb_l || link->id == car_l1 || link->id == car_l2) {
      if (link->id == pb_l)
        prioritize_plusbus(link, vehicle);
      link_stop(link, vehicle);
      return Red;
    }
  } else {
    if (link->id == car_l3) {
      prioritize_plusbus(link, vehicle);
      link_stop(link, vehicle);
      return Red;
    }
  }
  return Green;
}

/* Checks which links should be stopped because of red light in type d intersection */
int intersection_control_type_e(vehicle *vehicle, link *link,
                                        int pb_l1, int pb_l2, int car_l1,int car_l2,int car_l3) {
  if (link->intersection->layout.type_e.data.state == Red) {
    if (link->id == pb_l1 || link->id == pb_l2 || link->id == car_l1) {
      if (link->id == pb_l1 || link->id == pb_l2)
        prioritize_plusbus(link, vehicle);
      link_stop(link, vehicle);
      return Red;
    }
  } else {
    if (link->id == car_l2 || link->id == car_l3) {
      link_stop(link, vehicle);
      return Red;
    }
  }
  return Green;
}