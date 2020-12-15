#include "node.h"
#include "debug.h"
#include "trafficlights.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "simbuildinterpreter.h"

/* Populates the roads with vehicles */
void initialize_actors(vehicle* actors, link* links);
void simulate_all_links(link* links, vehicle* vehicles, int* done);
void time_step(link* links, vehicle* vehicles);
void move(link *link, vehicle *vehicles);
void change_speed(link* link, vehicle* vehicles);
void is_finished(vehicle* vehicle, link* links, int* done);

int timer = 0;

int main(void) {
  int done = 0, i = 0, j;
  link *links;
  vehicle vehicles[AMOUNT_VEHICLES];
  intersection *nodes;
  time_t seed = time(NULL);

  srand(seed);
  build_network(nodes, links);

  initialize_actors(vehicles, links);

  while (!done) {
    printf("Timestep: %d\n", i + 1);
    change_state(nodes);
    simulate_all_links(links, vehicles, &done);
    ++i;
    //(nodes+2)->layout.type_c.data.counter++;
  }
  print_status(vehicles, seed, links + 46, timer);

  for (j = 0; j < AMOUNT_LINKS; j++) {
    free(links[j].road);
  }

  return EXIT_SUCCESS;
}

void initialize_actors(vehicle* actors, link* links) {
  int n, i;
  actors->id = 1;
  actors->v = 0;
  actors->is_plusbus = 1;
  actors->turn_direction = plusbus;
  actors->has_moved = 0;
  actors->active = 1;
  links[2].road[0] = 1;

  for (i = 1; i < AMOUNT_VEHICLES; i++) {
    actors[i].id = i + 1;
    actors[i].v = 0;
    actors[i].is_plusbus = 0;
    actors[i].turn_direction = forward;
    actors[i].has_moved = 0;
    actors[i].active = 1;

    do n = rand() % links->len;
    while (links->road[n] != 0);

    links->road[n] = i + 1;

    /*if (actors[i].id < AMOUNT_VEHICLES/2) {
        actors[i].active = 1;
        int l = rand()%len;
        links[l].road[rand()%links[l].len] = i;
    }
    else
        actors[i].active = 0;
    */
  }

  actors[0].is_plusbus = 1;
  printf("\n");
}

void simulate_all_links(link *links, vehicle *vehicles, int* done) {
  int i;
  timer++;

  for (i = 0; i < AMOUNT_LINKS; ++i) {
    if ((links + i)->time_step < timer) {
      time_step(links + i, vehicles);

      /* Check if the plusbus has reached the destination*/
      if (links[i].id == END_LINK)
        is_finished(vehicles, links + i, done);
    }
  }

  printf("\n");
}

void time_step(link *link, vehicle *vehicles) {
  /*if (link->spawn_lane)
      spawn_car(link, vehicles);*/

  link->time_step++;
  change_speed(link, vehicles);

  /* Print this link if there are vehicles on it */
  print_link(link, vehicles);

  move(link, vehicles);
}

void move(link *link, vehicle *vehicles) {
  int id, v, index, i;
  struct link *new_link;
  turn_dir next_turn;

  for (i = link->len - 1; i >= 0; --i) {
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
          next_turn = decide_turn_dir(new_link, vehicles[index].is_plusbus);
          vehicles[index].turn_direction = next_turn;

          vehicles[index].has_moved = 1;
        }
      }

      else
        vehicles[index].has_moved = 0;
    }
  }
}

void change_speed(link *link, vehicle *vehicles) {
  int i, id, v, gap, gap2, index;
  struct link *new_link;

  for (i = link->len - 1; i >= 0; i--) {
    gap2 = 0;
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

      else if (gap < v)
        vehicles[index].v = gap;

      assert(vehicles[index].v <= gap + gap2);
    }
  }
}

void is_finished(vehicle* vehicle, link* links, int* done) {
  int i, index;

  /*Checks if the Plusbus has reached its destination */
  for (i = links->len - 1; i >= 0; i--) {
    index = links->road[i] - 1;

    if (vehicle[index].is_plusbus && index >= 0)
      *done = 1;
  }
}
