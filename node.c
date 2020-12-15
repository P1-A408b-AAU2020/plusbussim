#include "node.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "debug.h"
#define RIGHT 1
#define LEFT 5
#define FORWARD 3
#define AMT_SPAWN_LANES 6
#include "simbuildinterpreter.h"
#include "errno.h"
#include <string.h>

/* The contents of this function are predefined. Make changes to how network here. */
void build_network(intersection* intersections, link* links){
  FILE *file = fopen("C:/Repositories/plusbussim/input.txt", "r");
  printf("%s\n", strerror(errno));

  interpret_file(file, intersections, 9, links, 64);
  fclose(file);


  /*
  int link_length[AMOUNT_LINKS] = {JYLGADE_1_LEN, JYLGADE_1_LEN, JYLGADE_1_LEN, JYLGADE_2_LEN, JYLGADE_2_LEN,
                                   JYLGADE_2_LEN, JYLGADE_2_LEN, AAGADE_LEN, AAGADE_LEN, JYLGADE_1_LEN,

                                   JYLGADE_3_LEN, JYLGADE_3_LEN, JYLGADE_3_LEN, JYLGADE_3_LEN,
                                   NIELS_EBS_GADE_LEN, NIELS_EBS_GADE_LEN,

                                   DAG_HAM_GADE_1_LEN, DAG_HAM_GADE_1_LEN, JYLGADE_4_LEN, JYLGADE_4_LEN,
                                   JYLGADE_4_LEN, JYLGADE_4_LEN, DAG_HAM_GADE_2_LEN, DAG_HAM_GADE_2_LEN,

                                   SDRBRO_LEN, SDRBRO_LEN, FYENSGADE_LEN, FYENSGADE_LEN, FYENSGADE_LEN,
                                   FYENSGADE_LEN, KJELRUPSGADE_LEN, KJELRUPSGADE_LEN,

                                   BORNHOLMSGADE_1_LEN, BORNHOLMSGADE_1_LEN, KAROLUNDSVEJ_LEN, KAROLUNDSVEJ_LEN,

                                   FAEROESGADE_1_LEN, FAEROESGADE_1_LEN, BORNHOLMSGADE_2_LEN, BORNHOLMSGADE_2_LEN,
                                   FAEROESGADE_2_LEN, FAEROESGADE_2_LEN,

                                   SJAELGADE_1_LEN, SJAELGADE_1_LEN, BORNHOLMSGADE_3_LEN, BORNHOLMSGADE_3_LEN,
                                   SJAELGADE_2_LEN, SJAELGADE_2_LEN,

                                   OESTER_ALLE_1_LEN, OESTER_ALLE_1_LEN, SGHSVEJ_1_LEN, SGHSVEJ_1_LEN,
                                   SGHSVEJ_1_LEN, SGHSVEJ_1_LEN, OESTER_ALLE_2_LEN, OESTER_ALLE_2_LEN,

                                   KRIDTSJLFEN_LEN, KRIDTSJLFEN_LEN, SGHSVEJ_2_LEN, SGHSVEJ_2_LEN,
                                   SGHSVEJ_2_LEN, SGHSVEJ_2_LEN, BERNSTFFGADE_LEN, BERNSTFFGADE_LEN
                                   };
                                   */
    /*int spawn_lanes[AMT_SPAWN_LANES] = {0, 2, 6, 12, 14, 15};
    double spawn_chances[AMT_SPAWN_LANES] = {30.5, 21.2, 15.7, 19.2, 8.5, 15.2};*/
  /*
  int i;



    for (i = jylgade_1_east; i <= bernstorffsgade_west; i++){
        links[i].id    = i;
        links[i].road  = (int*)calloc(link_length[i], sizeof(int));
        links[i].len   = link_length[i];
        links[i].time_step    = 0;
        links[i].intersection = NULL;
        links[i].left_chance  = 0;
        links[i].right_chance = 0;
        */
/*
        if (links[i].id == spawn_lanes[j]){
            links[i].spawn_lane = 1;
            links[i].spawn_chance = 0;  spawn_chances[k];
            k++;
            j++;
        }
        else {
            links[i].spawn_lane = 0;
            links[i].spawn_chance = 0.0;
        }*/
/*
    }
    links[fyensgade_east].right_chance       = 100;
    links[bornholmsgade_2_south].left_chance = 100;

    printf("længde af vej: %d", links[0].len);

    construct_type_b(intersections, 0,links+jylgade_1_east,links+jylgade_2_east, links+jylgade_2_west,links+jylgade_1_west,
                     links+aagade_south,links+aagade_north,links+jylgade_1_east_plusbus,links+jylgade_2_east_plusbus,
                     links+jylgade_2_west_plusbus, links+jylgade_1_west_plusbus);

    construct_type_b(intersections + 1, 1, links+jylgade_2_east, links+jylgade_3_east, links+jylgade_3_west,
                     links+jylgade_2_west ,links+niels_ebbesens_gade_south, links+niels_ebbesens_gade_north, links+jylgade_2_east_plusbus,
                     links+jylgade_3_east_plusbus ,links+jylgade_3_west_plusbus ,links+jylgade_2_west_plusbus);

    construct_type_c(intersections + 2, 2, links+jylgade_3_east, links+jylgade_4_east, links+jylgade_4_west, links+jylgade_3_west,
                     links+dag_ham_gade_1_north, links+dag_ham_gade_2_north, links+dag_ham_gade_2_south, links+dag_ham_gade_1_south,
                     links+jylgade_3_east_plusbus, links+jylgade_4_east_plusbus, links+jylgade_4_west_plusbus, links+jylgade_3_west_plusbus);

    construct_type_c(intersections+3, 3, links+jylgade_4_east, links+fyensgade_east, links+fyensgade_west, links+jylgade_4_west,
                     links+sdrbro_north, links+kjellerupsgade_north, links+kjellerupsgade_south, links+sdrbro_south,
                     links+jylgade_4_east_plusbus, links+fyensgade_east_plusbus, links+fyensgade_west_plusbus, links+jylgade_4_west_plusbus);

    construct_type_d(intersections+4, 4, links+fyensgade_east, links+karolinelundsvej_north, links+karolinelundsvej_south, links+fyensgade_west,
                     links+bornholmsgade_1_north, links+bornholmsgade_1_south, links+fyensgade_east_plusbus, links+fyensgade_west_plusbus);

    construct_type_a(intersections+5, 5, links+bornholmsgade_1_south, links+bornholmsgade_2_south, links+bornholmsgade_2_north, links+bornholmsgade_1_north,
                     links+faerogade_1_east, links+faereogade_2_east, links+faereogade_2_west, links+faereogade_1_west);

    construct_type_a(intersections+6, 6, links+bornholmsgade_2_south, links+bornholmsgade_3_south, links+bornholmsgade_3_north, links+bornholmsgade_2_north,
                     links+sjaelgade_1_east, links+sjaelgade_2_east, links+sjaelgade_2_west, links+sjaelgade_1_west);

    construct_type_e(intersections+7, 7, links+oester_alle_1_east, links+oester_alle_2_east, links+oester_alle_2_west, links+oester_alle_1_west,
                     links+sghsvej_1_north, links+sghsvej_1_south, links+sghsvej_1_north_plusbus, links+bornholmsgade_3_north,
                     links+bornholmsgade_3_south, links+sghsvej_1_south_plusbus);

    construct_type_c(intersections+8, 8, links+sghsvej_1_south, links+sghsvej_2_south, links+sghsvej_2_north, links+sghsvej_1_north,
                     links+kridtsleofen_east, links+bernstorffsgade_east, links+bernstorffsgade_west, links+kridtsleofen_west,
                     links+sghsvej_1_south_plusbus, links+sghsvej_2_south_plusbus, links+sghsvej_2_north_plusbus, links+sghsvej_1_north_plusbus);

  */
}

void add_link(intersection* node, int index, link* link){
  switch (node->type) {
    case 'a': node->layout.type_a.links[index] = link;
    case 'b': node->layout.type_b.links[index] = link;
    case 'c': node->layout.type_c.links[index] = link;
    case 'd': node->layout.type_d.links[index] = link;
    case 'e': node->layout.type_e.links[index] = link;

  }
}

int get_link_index_a(enum internal_name name){
  int index;
  switch (name) {
    case p1i: index = 0; break;
    case p1o: index = 3; break;
    case p2i: index = 4; break;
    case p2o: index = 7; break;
    case s1i: index = 2; break;
    case s1o: index = 5; break;
    case s2i: index = 6; break;
    case s2o: index = 1; break;
  }

  return index;
}

/* Pointer to the intersection. */
void construct_type_a(intersection* intersection, int id,
                      link* primary1_enter,   link* primary1_exit,
                      link* primary2_enter,   link* primary2_exit,
                      link* secondary1_enter, link* secondary1_exit,
                      link* secondary2_enter, link* secondary2_exit){
  int i;
  link* links[N_TYPE_A] = {primary1_enter,   secondary2_exit,
                           secondary1_enter, primary1_exit,
                           primary2_enter,   secondary1_exit,
                           secondary2_enter, primary2_exit};
  intersection->id = id;
  intersection->type = 'a';
  intersection->n = N_TYPE_A;
  for (i = 0; i < N_TYPE_A; ++i){
    intersection->layout.type_a.links[i] = links[i];

    if((i + 1) % 2)
      links[i]->intersection = intersection;
  }
}

int get_link_index_b(enum internal_name name){
  int index;
  switch (name) {
    case p1i: index = 5; break;
    case p1o: index = 0; break;
    case p2i: index = 1; break;
    case p2o: index = 4; break;
    case s1i: index = 3; break;
    case s1o: index = 2; break;
    case b1i: index = 8; break;
    case b1o: index = 9; break;
    case b2i: index = 6; break;
    case b2o: index = 7; break;
  }

  return index;
}

void construct_type_b(intersection* intersection, int id,
                      link* primary1_enter,  link* primary1_exit,
                      link* primary2_enter,  link* primary2_exit,
                      link* secondary_enter, link* secondary_exit,
                      link* plusbus1_enter,  link* plusbus1_exit,
                      link* plusbus2_enter,  link* plusbus2_exit){
  int i;
  link* links[N_TYPE_B] = {primary1_exit,  primary2_enter,
                           secondary_exit, secondary_enter,
                           primary2_exit,  primary1_enter,
                           plusbus2_enter, plusbus2_exit,
                           plusbus1_enter, plusbus1_exit};
  intersection->id = id;
  intersection->type = 'b';
  intersection->n = N_TYPE_B;

  for (i = 0; i < N_TYPE_B; ++i) {
    intersection->layout.type_b.links[i] = links[i];

    if (i < 6 && (i + 1) % 2 == 0 || i >= 6 && (i + 1) % 2)
      links[i]->intersection = intersection;
  }
}

int get_link_index_c(enum internal_name name){
  int index;
  switch (name) {
    case p1i: index = 0; break;
    case p1o: index = 3; break;
    case p2i: index = 4; break;
    case p2o: index = 7; break;
    case s1i: index = 2; break;
    case s1o: index = 5; break;
    case s2i: index = 6; break;
    case s2o: index = 1; break;
    case b1i: index = 10; break;
    case b1o: index = 11; break;
    case b2i: index = 8; break;
    case b2o: index = 9; break;
  }

  return index;
}

void construct_type_c(intersection* intersection, int id,
                      link* primary1_enter,   link* primary1_exit,    link* primary2_enter,
                      link* primary2_exit,    link* secondary1_enter, link* secondary1_exit,
                      link* secondary2_enter, link* secondary2_exit,  link* plusbus1_enter,
                      link* plusbus1_exit,    link* plusbus2_enter,   link* plusbus2_exit){
  int i;
  link* links[N_TYPE_C] = {primary1_enter,   secondary2_exit, secondary1_enter,
                           primary1_exit,    primary2_enter,  secondary1_exit,
                           secondary2_enter, primary2_exit,   plusbus2_enter,
                           plusbus2_exit,    plusbus1_enter,  plusbus1_exit};
  intersection->id = id;
  intersection->type = 'c';
  intersection->layout.type_c.data.counter = 0;
  intersection->layout.type_c.data.state = 0;
  intersection->n = N_TYPE_C;
  for (i = 0; i < N_TYPE_C; ++i) {
    intersection->layout.type_c.links[i] = links[i];

    if((i + 1) % 2)
      links[i]->intersection = intersection;
  }
}

int get_link_index_d(enum internal_name name){
  int index;
  switch (name) {
    case p1i: index = 1; break;
    case p1o: index = 4; break;
    case p2i: index = 5; break;
    case p2o: index = 0; break;
    case s1i: index = 3; break;
    case s1o: index = 2; break;
    case b1i: index = 7; break;
    case b1o: index = 6; break;
  }

  return index;
}

void construct_type_d(intersection* intersection, int id,
                      link* primary1_enter, link* primary1_exit,   link* primary2_enter,
                      link* primary2_exit,  link* secondary_enter, link* secondary_exit,
                      link* plusbus_enter,  link* plusbus_exit){
  int i;
  link* links[N_TYPE_D] = {primary2_exit,   primary1_enter, secondary_exit,
                           secondary_enter, primary1_exit,  primary2_enter,
                           plusbus_exit,    plusbus_enter};
  intersection->id = id;
  intersection->type = 'd';
  intersection->layout.type_d.data.counter = 0;
  intersection->layout.type_d.data.state = 0;
  intersection->n = N_TYPE_D;
  for (i = 0; i < N_TYPE_D; ++i) {
    intersection->layout.type_d.links[i] = links[i];

    if ((i + 1) % 2 == 0)
      links[i]->intersection = intersection;
  }

}

int get_link_index_e(enum internal_name name){
  int index;
  switch (name) {
    case p1i: index = 0; break;
    case p1o: index = 3; break;
    case p2i: index = 4; break;
    case p2o: index = 5; break;
    case s1i: index = 1; break;
    case s1o: index = 2; break;
    case b1i: index = 8; break;
    case b1o: index = 9; break;
    case b2i: index = 6; break;
    case b2o: index = 7; break;
  }

  return index;
}

void construct_type_e(intersection* intersection, int id,
                      link* primary1_enter, link* primary1_exit,   link* primary2_enter,
                      link* primary2_exit,  link* secondary_enter, link* secondary_exit,
                      link* plusbus1_enter, link* plusbus1_exit,   link* plusbus2_enter,
                      link* plusbus2_exit){
  int i;
  link* links[N_TYPE_E] = {primary1_enter, secondary_enter, secondary_exit,
                           primary1_exit,  primary2_enter,  primary2_exit,
                           plusbus2_enter, plusbus2_exit,   plusbus1_enter,
                           plusbus1_exit};
  intersection->id = id;
  intersection->type = 'e';
  intersection->layout.type_e.data.counter = 0;
  intersection->layout.type_e.data.state = 0;
  intersection->n = N_TYPE_E;
  for (i = 0; i < N_TYPE_E; ++i) {
    intersection->layout.type_e.links[i] = links[i];

    if ((i == 0 || i == 1) || i >= 4 && (i + 1) % 2)
      links[i]->intersection = intersection;
  }
}

link** get_links(intersection* intersection){
  link** links;

  switch (intersection->type) {
    case 'a': links = intersection->layout.type_a.links; break;
    case 'b': links = intersection->layout.type_b.links; break;
    case 'c': links = intersection->layout.type_c.links; break;
    case 'd': links = intersection->layout.type_d.links; break;
    case 'e': links = intersection->layout.type_e.links; break;
  }

  return links;
}

int get_link_index(enum internal_name name, char type) {
  int (*fn) (enum internal_name);

  switch (type) {
    case 'a': fn = &get_link_index_a; break;
    case 'b': fn = &get_link_index_b; break;
    case 'c': fn = &get_link_index_c; break;
    case 'd': fn = &get_link_index_d; break;
    case 'e': fn = &get_link_index_e; break;
  }

  return fn(name);
}

int internal_index(intersection* intersection, int link_id) {
  int i, n = intersection->n;
  link **link = get_links(intersection);

  for (i = 0; i < n; i++){
    if (link[i]->id == link_id)
      return i;
  }
}

link* right_turn(intersection *intersection, int link_id) {
  link *result;
  link** links = get_links(intersection);
  result = links[(internal_index(intersection, link_id) + RIGHT) % 8];

  return result;
}

link* left_turn(intersection *intersection, int link_id) {
  link *result;
  link** links = get_links(intersection);
  result = links[(internal_index(intersection, link_id) + LEFT) % 8];

  return result;
}

link* go_forward(intersection *intersection, int link_id) {
  link *result;
  link** links = get_links(intersection);
  result = links[(internal_index(intersection, link_id) + FORWARD) % 8];

  return result;
}

link* plusbus_dec(intersection *intersection, int link_id) {
  link *result;
  link** links = get_links(intersection);
  switch (intersection->type) {
    case 'a' :
      result = links[((internal_index(intersection, link_id) == 0) ? 3 : 7)];
      break;

    case 'b' : case 'c' : case 'e' :
      result = links[(internal_index(intersection, link_id) + 1)];
      break;

    case 'd' :
      result = links[(internal_index(intersection, link_id) + 3) % 8];
      break;
  }

  return result;
}

turn_dir decide_turn_dir(link* link, int is_plusbus) {
  int dir = rand() % 100 + 1;

  if (is_plusbus)
    return plusbus;

  else if (dir <= link->left_chance)
    return left;

  else if (dir <= link->left_chance + link->right_chance)
    return right;

  else
    return forward;
}

link* turn(turn_dir dir, intersection *intersection, int link_id) {
  link *result = 0;
  switch (dir) {
    case left:    result = left_turn(intersection, link_id);   break;
    case right:   result = right_turn(intersection, link_id);  break;
    case forward: result = go_forward(intersection, link_id);  break;
    case plusbus: result = plusbus_dec(intersection, link_id); break;
  }
  return result;
}

int lead_gap(link* link, int pos) {
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
    return gap;
}

void spawn_car(link *link, vehicle *vehicles) {
  int car_spawned = 0;
  int i = 1;

  while (!car_spawned) {
    if (!(vehicles + i)->active) {
      if (!(vehicles + link->road[0])->id) {
        if (rand() % 101 <= link->spawn_chance) {
          link->road[0] = (vehicles + i)->id;
          (vehicles + i)->active = 1;
          (vehicles + i)->v = V_MAX;
          car_spawned = 1;
        }
      }
      break;
    }
    if (i > AMOUNT_VEHICLES)
      break;
    i++;
  }
}