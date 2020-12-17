#include "node.h"
#include "debug.h"

/* Builds the road network. Hardcoded to make the network we want to simulate. User can build own road network here. */
void build_network(intersection *intersections, link *links){
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
    int dec_chance_lanes[AMT_DEC_LANES] = {jylgade_1_east, jylgade_2_east, jylgade_2_west, aagade_south, jylgade_3_east,
                                         jylgade_3_west, niels_ebbesens_gade_south, dag_ham_gade_1_north, jylgade_4_east,
                                         jylgade_4_west, dag_ham_gade_2_south, sdrbro_north, fyensgade_east, fyensgade_west,
                                         kjellerupsgade_south, bornholmsgade_1_south, bornholmsgade_1_north, karolinelundsvej_south,
                                         faerogade_1_east, bornholmsgade_2_south, bornholmsgade_2_north, faereogade_2_west,
                                         sjaelgade_1_east, sjaelgade_2_west, oester_alle_1_east, sghsvej_1_south, sghsvej_1_north,
                                         oester_alle_2_west, kridtsleofen_east, sghsvej_2_north, bernstorffsgade_west};
    int left_chances[AMT_DEC_LANES] = {18, 18, 0, 57, 24, 0, 57, 40, 7, 29, 37, 42, 0, 57, 31, 30, 50, 20, 36, 50, 30, 36, 56, 0, 0, 9, 59, 32, 48, 4, 48};
    int right_chances[AMT_DEC_LANES] = {0, 0, 23, 43, 30, 23, 43, 39, 54, 24, 38, 49, 20, 8, 27, 30, 50, 0, 36, 50, 30, 36, 0, 56, 40, 4, 41, 0, 50, 9, 47};
    int spawn_lanes[AMT_SPAWN_LANES] = {0, 8, 15, 17, 23, 25, 31, 35, 37, 41, 43, 47, 49, 55, 57, 61, 63};
    double spawn_chances[AMT_SPAWN_LANES] = {9.95, 3.0, 3.0, 8.41, 6.86, 22.29, 3.0, 15.89, 3.0, 3.0, 3.04, 3.04, 44.13, 31.06, 2.12, 21.12, 1.0};
    int plusbus_links[AMT_PLUSBUS_LINKS] = {1, 2, 3, 4, 10, 11, 18, 19, 26, 27, 44, 45, 51, 52, 59, 60};

    int i, j = 0, k = 0, m = 0;

    /* Building all the different links */
    for (i = jylgade_1_east; i <= bernstorffsgade_west; i++){
        links[i].id   = i;
        links[i].road = (int*)calloc(link_length[i], sizeof(int));
        links[i].len  = link_length[i];
        links[i].time_step    = 0;
        links[i].intersection = NULL;

        if (links[i].id == dec_chance_lanes[m]){
          links[i].left_chance  = left_chances[m];
          links[i].right_chance = right_chances[m];
          m++;
        }
        else {
          links[i].left_chance = 0;
          links[i].right_chance = 0;
        }

        if (links[i].id == spawn_lanes[j]){
            links[i].spawn_lane = 1;
            links[i].spawn_chance = spawn_chances[j];
            j++;
        }
        else {
            links[i].spawn_lane = 0;
            links[i].spawn_chance = 0.0;
        }

        if (links[i].id == plusbus_links[k]) {
          links[i].plusbus_link = 1;
          k++;
        }
        else
          links[i].plusbus_link = 0;
    }
    links[fyensgade_east].right_chance       = 100;
    links[bornholmsgade_2_south].left_chance = 100;
    links[sjaelgade_1_east].left_chance      = 100;
    links[sjaelgade_2_west].right_chance     = 100;

    /* Building all the intersections in the road network */
    construct_type_b(intersections, 0,links+jylgade_1_east,links+jylgade_2_east, links+jylgade_2_west,links+jylgade_1_west,
                     links+aagade_south,links+aagade_north,links+jylgade_1_east_plusbus,links+jylgade_2_east_plusbus,
                     links+jylgade_2_west_plusbus, links+jylgade_1_west_plusbus);

    construct_type_b(intersections + 1, 1, links+jylgade_2_east, links+jylgade_3_east, links+jylgade_3_west,
                     links+jylgade_2_west ,links+niels_ebbesens_gade_south, links+niels_ebbesens_gade_north, links+jylgade_2_east_plusbus,
                     links+jylgade_3_east_plusbus ,links+jylgade_3_west_plusbus ,links+jylgade_2_west_plusbus);

    construct_type_c(intersections + 2, 2, links+jylgade_3_east, links+jylgade_4_east, links+jylgade_4_west, links+jylgade_3_west,
                     links+dag_ham_gade_1_north, links+dag_ham_gade_2_north, links+dag_ham_gade_2_south, links+dag_ham_gade_1_south,
                     links+jylgade_3_east_plusbus, links+jylgade_4_east_plusbus, links+jylgade_4_west_plusbus, links+jylgade_3_west_plusbus);

    construct_type_c(intersections + 3, 3, links+jylgade_4_east, links+fyensgade_east, links+fyensgade_west, links+jylgade_4_west,
                     links+sdrbro_north, links+kjellerupsgade_north, links+kjellerupsgade_south, links+sdrbro_south,
                     links+jylgade_4_east_plusbus, links+fyensgade_east_plusbus, links+fyensgade_west_plusbus, links+jylgade_4_west_plusbus);

    construct_type_d(intersections + 4, 4, links+fyensgade_east, links+karolinelundsvej_north, links+karolinelundsvej_south, links+fyensgade_west,
                     links+bornholmsgade_1_north, links+bornholmsgade_1_south, links+fyensgade_east_plusbus, links+fyensgade_west_plusbus);

    construct_type_a(intersections + 5, 5, links+bornholmsgade_1_south, links+bornholmsgade_2_south, links+bornholmsgade_2_north, links+bornholmsgade_1_north,
                     links+faerogade_1_east, links+faereogade_2_east, links+faereogade_2_west, links+faereogade_1_west);

    construct_type_a(intersections + 6, 6, links+bornholmsgade_2_south, links+bornholmsgade_3_south, links+bornholmsgade_3_north, links+bornholmsgade_2_north,
                     links+sjaelgade_1_east, links+sjaelgade_2_east, links+sjaelgade_2_west, links+sjaelgade_1_west);

    construct_type_e(intersections + 7, 7, links+oester_alle_1_east, links+oester_alle_2_east, links+oester_alle_2_west, links+oester_alle_1_west,
                     links+sghsvej_1_north, links+sghsvej_1_south, links+sghsvej_1_north_plusbus, links+bornholmsgade_3_north,
                     links+bornholmsgade_3_south, links+sghsvej_1_south_plusbus);

    construct_type_c(intersections + 8, 8, links+sghsvej_1_south, links+sghsvej_2_south, links+sghsvej_2_north, links+sghsvej_1_north,
                     links+kridtsleofen_east, links+bernstorffsgade_east, links+bernstorffsgade_west, links+kridtsleofen_west,
                     links+sghsvej_1_south_plusbus, links+sghsvej_2_south_plusbus, links+sghsvej_2_north_plusbus, links+sghsvej_1_north_plusbus);

}

/* Constructs a typical four way intersection without traffic lights. */
void construct_type_a(intersection *intersection, int id,
                      link *primary1_enter,   link *primary1_exit,
                      link *primary2_enter,   link *primary2_exit,
                      link *secondary1_enter, link *secondary1_exit,
                      link *secondary2_enter, link *secondary2_exit){
  int i;
  link *links[N_TYPE_A] = {primary1_enter,   secondary2_exit,
                           secondary1_enter, primary1_exit,
                           primary2_enter,   secondary1_exit,
                           secondary2_enter, primary2_exit};
  intersection->id = id;
  intersection->type = 'a';
  intersection->n = N_TYPE_A;
  for (i = 0; i < N_TYPE_A; i++){
    intersection->layout.type_a.links[i] = links[i];

    if((i + 1) % 2)
      links[i]->intersection = intersection;
  }
}

/* Constructs a T-cross intersection with separate plusbus lanes and without traffic lights. */
void construct_type_b(intersection *intersection, int id,
                      link *primary1_enter,  link *primary1_exit,
                      link *primary2_enter,  link *primary2_exit,
                      link *secondary_enter, link *secondary_exit,
                      link *plusbus1_enter,  link *plusbus1_exit,
                      link *plusbus2_enter,  link *plusbus2_exit){
  int i;
  link *links[N_TYPE_B] = {primary1_exit,  primary2_enter,
                           secondary_exit, secondary_enter,
                           primary2_exit,  primary1_enter,
                           plusbus2_enter, plusbus2_exit,
                           plusbus1_enter, plusbus1_exit};
  intersection->id = id;
  intersection->type = 'b';
  intersection->n = N_TYPE_B;

  for (i = 0; i < N_TYPE_B; i++) {
    intersection->layout.type_b.links[i] = links[i];

    if (((i < 6) && ((i + 1) % 2 == 0)) || ((i >= 6) && ((i + 1) % 2)))
      links[i]->intersection = intersection;
  }
}

/* Constructs a typical four way intersection with traffic light and with separate plusbus lanes */
void construct_type_c(intersection *intersection, int id,
                      link *primary1_enter,   link *primary1_exit,    link *primary2_enter,
                      link *primary2_exit,    link *secondary1_enter, link *secondary1_exit,
                      link *secondary2_enter, link *secondary2_exit,  link *plusbus1_enter,
                      link *plusbus1_exit,    link *plusbus2_enter,   link *plusbus2_exit){
  int i;
  link *links[N_TYPE_C] = {primary1_enter,   secondary2_exit, secondary1_enter,
                           primary1_exit,    primary2_enter,  secondary1_exit,
                           secondary2_enter, primary2_exit,   plusbus2_enter,
                           plusbus2_exit,    plusbus1_enter,  plusbus1_exit};
  intersection->id = id;
  intersection->type = 'c';
  intersection->layout.type_c.data.state = rand() % 2;

  /* Setting the state of the traffic light */
  if(intersection->layout.type_c.data.state){
    intersection->layout.type_c.data.counter = rand() % GREEN_T;
  }
  else{
    intersection->layout.type_c.data.counter = rand() % RED_T;
  }
  intersection->n = N_TYPE_C;

  for (i = 0; i < N_TYPE_C; i++) {
    intersection->layout.type_c.links[i] = links[i];

    if((i + 1) % 2)
      links[i]->intersection = intersection;
  }
}

/* Constructs a T-cross intersection with traffic light where
 * the plusbus goes from a separate lane to a shared lane  */
void construct_type_d(intersection *intersection, int id,
                      link *primary1_enter, link *primary1_exit,   link *primary2_enter,
                      link *primary2_exit,  link *secondary_enter, link *secondary_exit,
                      link *plusbus_enter,  link *plusbus_exit){
  int i;
  link *links[N_TYPE_D] = {primary2_exit,   primary1_enter, secondary_exit,
                           secondary_enter, primary1_exit,  primary2_enter,
                           plusbus_exit,    plusbus_enter};
  intersection->id = id;
  intersection->type = 'd';
  intersection->layout.type_d.data.state = rand() % 2;
  if(intersection->layout.type_d.data.state){
    intersection->layout.type_d.data.counter = rand() % GREEN_T;
  }
  else{
    intersection->layout.type_d.data.counter = rand() % RED_T;
  }
  intersection->n = N_TYPE_D;
  for (i = 0; i < N_TYPE_D; i++) {
    intersection->layout.type_d.links[i] = links[i];

    if ((i + 1) % 2 == 0)
      links[i]->intersection = intersection;
  }

}
 /* Constructs a cross intersection with traffic lights
  * One of the ingoing roads are bus only, and the opposite road has a separated plusbus lane*/
void construct_type_e(intersection *intersection, int id,
                      link *primary1_enter, link *primary1_exit,   link *primary2_enter,
                      link *primary2_exit,  link *secondary_enter, link *secondary_exit,
                      link *plusbus1_enter, link *plusbus1_exit,   link *plusbus2_enter,
                      link *plusbus2_exit){
  int i;
  link *links[N_TYPE_E] = {primary1_enter, secondary_enter, secondary_exit,
                           primary1_exit,  primary2_enter,  primary2_exit,
                           plusbus2_enter, plusbus2_exit,   plusbus1_enter,
                           plusbus1_exit};
  intersection->id = id;
  intersection->type = 'e';
  intersection->layout.type_e.data.state = rand() % 2;
  if(intersection->layout.type_e.data.state){
    intersection->layout.type_e.data.counter = rand() % GREEN_T;
  }
  else{
    intersection->layout.type_e.data.counter = rand() % RED_T;
  }
  intersection->n = N_TYPE_E;
  for (i = 0; i < N_TYPE_E; i++) {
    intersection->layout.type_e.links[i] = links[i];

    if ((i == 0 || i == 1) || ((i >= 4) && ((i + 1) % 2)))
      links[i]->intersection = intersection;
  }
}

/* Finds the links connected to the intersections depending on the intersection type */
link** get_links(intersection *intersection){
  link **links;
  switch (intersection->type) {
    case 'a': links = intersection->layout.type_a.links; break;
    case 'b': links = intersection->layout.type_b.links; break;
    case 'c': links = intersection->layout.type_c.links; break;
    case 'd': links = intersection->layout.type_d.links; break;
    case 'e': links = intersection->layout.type_e.links; break;
  }
  return links;
}

/* Finds the internal index the link has in the intersection */
int internal_index(intersection *intersection, int link_id) {
  int i, n = intersection->n;
  link **link = get_links(intersection);

  for (i = 0; i < n; i++){
    if (link[i]->id == link_id)
      return i;
  }
}

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you turn right at the intersection */
link* right_turn(intersection *intersection, int link_id) {
  link *result;
  link **links = get_links(intersection);
  if (intersection->type == 'e')
    result = links[(internal_index(intersection, link_id) == 1) ? 3 : 2];
  else
    result = links[(internal_index(intersection, link_id) + RIGHT) % 8];

  return result;
}

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you turn left at the intersection */
link* left_turn(intersection *intersection, int link_id) {
  link *result;
  link **links = get_links(intersection);
  if (intersection->type == 'e')
    result = links[(internal_index(intersection, link_id) == 1) ? 5 : 2];
  else
    result = links[(internal_index(intersection, link_id) + LEFT) % 8];

  return result;
}

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you don't turn at the intersection */
link* go_forward(intersection *intersection, int link_id) {
  link *result;
  link **links = get_links(intersection);
  if (intersection->type == 'e'){
    if (internal_index(intersection, link_id) == 0)
      result = links[(internal_index(intersection, link_id) + 3)];
    else
      result = links[(internal_index(intersection, link_id) + 1)];
  }
  else
    result = links[(internal_index(intersection, link_id) + FORWARD) % 8];

  return result;
}

/* Calculates the upcoming link for the plusbus */
link* plusbus_dec(intersection *intersection, int link_id) {
  link *result;
  link **links = get_links(intersection);
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

/* Calculates the upcoming link for the conventional bus */
link* bus_dec(intersection *intersection, int link_id) {
  link *result;
  link **links = get_links(intersection);
  switch (intersection->type) {
    case 'a' :
      result = links[((internal_index(intersection, link_id) == 0) ? 3 : 7)];
      break;

    case 'b' : case 'c' :
      result = links[(internal_index(intersection, link_id) + FORWARD) % 8];
      break;

    case 'd' :
      result = links[(internal_index(intersection, link_id) + RIGHT) % 8];
      break;

    case 'e' :
      result = links[(internal_index(intersection, link_id) == 6) ? 2 : 9];
      break;
  }

  return result;
}

/* Decides what a vehicle will do at the upcoming intersection */
turn_dir decide_turn_dir(link *link, int is_plusbus, int is_bus) {
  int dir = rand() % 100 + 1;

  if (is_plusbus)
    return plusbus;
  else if (is_bus)
    return bus;
  else if (dir <= link->left_chance)
    return left;
  else if (dir <= link->left_chance + link->right_chance)
    return right;
  else
    return forward;
}

/* Decides what calculations should be done based on what a vehicle will do
 * at the upcoming intersection */
link* turn(turn_dir dir, intersection *intersection, int link_id) {
  link *result = 0;
  switch (dir) {
    case left:    result = left_turn(intersection, link_id);   break;
    case right:   result = right_turn(intersection, link_id);  break;
    case forward: result = go_forward(intersection, link_id);  break;
    case plusbus: result = plusbus_dec(intersection, link_id); break;
    case bus:     result = bus_dec(intersection, link_id);     break;
  }
  return result;
}
