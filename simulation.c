#include "node.h"
#include "debug.h"
#include "trafficlights.h"
#include <stdlib.h>
#include <time.h>

void initialize_actors(vehicle* actors, link* links);
void simulate_all_links(link* links, vehicle* vehicles, int* done);
void time_step(link* links, vehicle* vehicles);
void move(link *link, vehicle *vehicles);
void change_speed(link* link, vehicle* vehicles);
int lead_gap(link* link, int pos);
void spawn_car(link* link, vehicle* vehicles);
void is_finished(vehicle* vehicle, link* links, int* done);

int timer = 0;

/* This is where the simulation is ran */
int main(void) {
  int done = 0, i = 0, j;
  link links[AMOUNT_LINKS];
  vehicle vehicles[AMOUNT_VEHICLES];
  intersection nodes[AMOUNT_NODES];
  time_t seed = time(NULL);
  srand(seed);

  /* creates simulation environment */
  build_network(nodes, links);
  initialize_actors(vehicles, links);

  /* the environment is simulated */
  while (!done) {
    print_int("Timestep", i+1);
    change_state(nodes);
    simulate_all_links(links, vehicles, &done);
    i++;
  }

  /* the status is printed to the user */
  print_status(vehicles, seed, timer);

  for (j = 0; j < AMOUNT_LINKS; j++)
    free(links[j].road);

  return EXIT_SUCCESS;
}

/* initializes the vehicles and placing them in the road network */
void initialize_actors(vehicle* actors, link* links) {
  int num, i, ran_link;
  actors->id = 1;
  actors->v = 0;
  actors->has_moved = 0;
  actors->active = 1;
  actors->intersec_counter = 0;
  if (PLUS_OR_BUS) {
    actors->is_bus = 0;
    actors->is_plusbus = 1;
    actors->turn_direction = plusbus;
    links[PLUSBUS_START_LINK].road[0] = 1;
  }
  else {
    actors->is_bus = 1;
    actors->is_plusbus = 0;
    actors->turn_direction = forward;
    links[BUS_START_LINK].road[0] = 1;
  }

  for (i = 1; i < AMOUNT_VEHICLES; i++) {
    actors[i].id = i + 1;
    actors[i].v = 0;
    actors[i].is_bus = 0;
    actors[i].is_plusbus = 0;
    actors[i].intersec_counter = 0;
    actors[i].has_moved = 0;

    /* initiates half of the vehicles on the road network */
    if (actors[i].id < AMOUNT_VEHICLES * INIT_PERCENTAGE) {
      do ran_link = rand() % AMOUNT_LINKS;
      while (links[ran_link].plusbus_link);

      actors[i].active = 1;
      do num = rand() % links[ran_link].len;
      while (links[ran_link].road[num] != 0);

      links[ran_link].road[num] = i + 1;
      actors[i].turn_direction = decide_turn_dir(links+ran_link, actors[i].is_plusbus, actors[i].is_bus);
    }
    else
      actors[i].active = 0;
  }
  new_line();
}

/* simulates all the links on the road network */
void simulate_all_links(link *links, vehicle *vehicles, int *done) {
  int i;
  timer++;

  for (i = 0; i < AMOUNT_LINKS; i++) {
    if ((links + i)->time_step < timer) {
      time_step(links + i, vehicles);

      /* Check if the plusbus has reached the destination*/
      if (links[i].id == END_LINK)
        is_finished(vehicles, links + i, done);
    }
  }

  for (i = 0; i < AMOUNT_VEHICLES; i++)
    vehicles[i].has_moved = 0;

  new_line();
}

/* Timestep agent, here a timestep is simulated for a link*/
void time_step(link *link, vehicle *vehicles) {
  if (link->spawn_lane)
    spawn_car(link, vehicles);

  link->time_step++;
  change_speed(link, vehicles);

  /* Print this link if there are vehicles on it */
  print_link(link, vehicles);

  move(link, vehicles);

}

/* Move agent, here the vehicles are moved according to their speed. */
void move(link *link, vehicle *vehicles) {
  int id, v, index, i;
  struct link *new_link;
  turn_dir next_turn;

  for (i = link->len - 1; i >= 0; i--) {
    id = link->road[i];
    index = id - 1;
    v = vehicles[index].v;

    if (id && v) {
      if (vehicles[index].has_moved == 0) {
        link->road[i] = 0;

        /* if there is room on current link, just move forward */
        if (link->len > i + v)
          link->road[i + v] = id;

          /*There is an intersection at the end of the link. */
        else if (link->intersection != NULL) {

          /* Place vehicle on new link */
          new_link = turn(vehicles[index].turn_direction, link->intersection, link->id);
          new_link->road[i + v - link->len] = id;

          /* Find out where to turn next */
          next_turn = decide_turn_dir(new_link, vehicles[index].is_plusbus, vehicles[index].is_bus);
          vehicles[index].turn_direction = next_turn;

          vehicles[index].has_moved = 1;
        }
        /* if a vehicle leaves the simulation */
        else {
          vehicles[index].active = 0;
        }
      }
      else
        vehicles[index].has_moved = 0;
    }
  }
}

/* speed agent, here the speed of the vehicles is changed */
void change_speed(link *link, vehicle *vehicles) {
  int i, id, v, gap, gap2, index;
  struct link *new_link;

  for (i = link->len - 1; i >= 0; i--) { /* loops through the link */
    id = link->road[i];
    index = id - 1;

    if (id) {
      v = vehicles[index].v;
      gap = lead_gap(link, i);

      /* Is the car approaching an intersection? */
      if (i + gap == link->len - 1 && link->intersection != NULL) {

        if (traffic_light(link, vehicles)) {
          new_link = turn(vehicles[index].turn_direction, link->intersection, link->id);

          if (new_link->time_step < timer)
            time_step(new_link, vehicles);

          gap2 = lead_gap(new_link, -1);

          /* Does the car have to decelerate to avoid collision? */
          if (gap + gap2 < v)
            vehicles[index].v = gap + gap2;

          else if (v < V_MAX && gap + gap2 > v)
            vehicles[index].v++;
        }

      }
      /* There is no intersection */
      else if (v < V_MAX && gap > v)
        vehicles[index].v++;

      /* Does the car have to decelerate to avoid collision?*/
      else if (gap < v)
        vehicles[index].v = gap;
    }
  }
}

/* Gap agent, calculates the lead gap a vehicle has on the link */
int lead_gap(link *link, int pos) {
  int i, gap = 0;
  for(i = pos + 1; i < link->len; i++){
    if(link->road[i] == 0)
      gap++;
    else
      return gap;
    if(gap > V_MAX)
      return V_MAX;
  }
  /* If the car reaches the end of the road */
  if (link->intersection == NULL)
    return V_MAX;
  else
    return gap;
}

/* Initiate new cars agent, here new vehicles are initiated. */
void spawn_car(link *link, vehicle *vehicles) {
  int car_spawned = 0, i = 0;

  while (!car_spawned) {
    if (!vehicles[i].active) {
      if (!link->road[0]) {
        if (rand() % 101 <= link->spawn_chance) {
          link->road[0] = (vehicles+ i)->id;
          vehicles[i].active = 1;
          vehicles[i].v = V_MAX;
          vehicles[i].turn_direction = decide_turn_dir(link, vehicles[i].is_plusbus, vehicles[i].is_bus);
        }
      }
      car_spawned = 1;
    }
    if (i == AMOUNT_VEHICLES - 1)
      break;
    i++;
  }
}

/* This function checks whether the bus or plusbus has reached it's destination*/
void is_finished(vehicle *vehicles, link *links, int *done) {
  int i, index;

  for (i = links->len - 1; i >= (links->len - 1) - 10; i--) { /* loops through the end of the link */
    index = links->road[i] - 1;

    if ((vehicles[index].is_plusbus || vehicles[index].is_bus) && index >= 0) {
      *done = 1;
    }
  }
}
