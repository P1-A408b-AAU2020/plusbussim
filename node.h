#ifndef NODE_H
#define NODE_H
#define V_MAX 5
#define PLUS_BUS_LENGTH 5
#define DECELERATE_CHANCE 5
#define MIN_SPEED_RANDOM_DECELERATE 2
#define AMOUNT_LINKS 64
#define AMOUNT_VEHICLES 120
#define END_LINK 59
#define AMT_PLUSBUS_LINKS 16
#define CELL_LEN 4.629

/*Bus Data*/
#define ROUTE_LEN 1
#define PLUSBUS_ROUTE_LEN 1
#define BUS_ROUTE_LEN 12
#define PLUS_OR_BUS 0

/*Traffic light Data*/
#define PLUSBUS_R 10
#define RED_T 30
#define GREEN_T 30
#define PLUSBUS_GREEN_ADJUST 1
#define PLUSBUS_RED_ADJUST 1

#define DEBUG 0

#define N_TYPE_A 8
#define N_TYPE_B 10
#define N_TYPE_C 12
#define N_TYPE_D 8
#define N_TYPE_E 10
#define JYLGADE_1_LEN       200 / CELL_LEN
#define JYLGADE_2_LEN       120 / CELL_LEN
#define AAGADE_LEN          150 / CELL_LEN
#define JYLGADE_3_LEN       120 / CELL_LEN
#define NIELS_EBS_GADE_LEN  120 / CELL_LEN
#define DAG_HAM_GADE_1_LEN  70  / CELL_LEN
#define JYLGADE_4_LEN       300 / CELL_LEN
#define DAG_HAM_GADE_2_LEN  100 / CELL_LEN
#define SDRBRO_LEN          300 / CELL_LEN
#define FYENSGADE_LEN       180 / CELL_LEN
#define KJELRUPSGADE_LEN    160 / CELL_LEN
#define KAROLUNDSVEJ_LEN    350 / CELL_LEN
#define BORNHOLMSGADE_1_LEN 110 / CELL_LEN
#define FAEROESGADE_1_LEN   160 / CELL_LEN
#define BORNHOLMSGADE_2_LEN 190 / CELL_LEN
#define FAEROESGADE_2_LEN   230 / CELL_LEN
#define SJAELGADE_1_LEN     160 / CELL_LEN
#define BORNHOLMSGADE_3_LEN 220 / CELL_LEN
#define SJAELGADE_2_LEN     250 / CELL_LEN
#define OESTER_ALLE_1_LEN   250 / CELL_LEN
#define SGHSVEJ_1_LEN       300 / CELL_LEN
#define OESTER_ALLE_2_LEN   300 / CELL_LEN
#define KRIDTSJLFEN_LEN     100 / CELL_LEN
#define SGHSVEJ_2_LEN       400 / CELL_LEN
#define BERNSTFFGADE_LEN    280 / CELL_LEN

typedef enum light_state{Red, Green}light_state;

/* A enum on the different id's for the links */
typedef enum roadid {jylgade_1_east, jylgade_1_west_plusbus, jylgade_1_east_plusbus,
                     jylgade_2_east_plusbus, jylgade_2_west_plusbus, jylgade_2_east,
                     jylgade_2_west, aagade_north, aagade_south, jylgade_1_west,

                     jylgade_3_east_plusbus, jylgade_3_west_plusbus, jylgade_3_east,
                     jylgade_3_west, niels_ebbesens_gade_south, niels_ebbesens_gade_north,

                     dag_ham_gade_1_south, dag_ham_gade_1_north,
                     jylgade_4_east_plusbus, jylgade_4_west_plusbus, jylgade_4_east,
                     jylgade_4_west, dag_ham_gade_2_north, dag_ham_gade_2_south,

                     sdrbro_south, sdrbro_north, fyensgade_east_plusbus, fyensgade_west_plusbus,
                     fyensgade_east, fyensgade_west, kjellerupsgade_north, kjellerupsgade_south,

                     bornholmsgade_1_south, bornholmsgade_1_north, karolinelundsvej_north, karolinelundsvej_south,

                     faereogade_1_west, faerogade_1_east, bornholmsgade_2_south, bornholmsgade_2_north,
                     faereogade_2_east, faereogade_2_west,

                     sjaelgade_1_west, sjaelgade_1_east, bornholmsgade_3_south, bornholmsgade_3_north,
                     sjaelgade_2_east, sjaelgade_2_west,

                     oester_alle_1_west, oester_alle_1_east, sghsvej_1_south, sghsvej_1_south_plusbus,
                     sghsvej_1_north_plusbus, sghsvej_1_north, oester_alle_2_east, oester_alle_2_west,

                     kridtsleofen_west, kridtsleofen_east, sghsvej_2_south, sghsvej_2_south_plusbus,
                     sghsvej_2_north_plusbus, sghsvej_2_north, bernstorffsgade_east, bernstorffsgade_west
} roadid;


typedef enum turn_dir{forward, right, left, plusbus} turn_dir;

typedef struct intersection intersection;

typedef struct link {
  int id;
  int *road;
  int len;
  int time_step;
  intersection *intersection;
  int spawn_lane;
  double spawn_chance;
  float right_chance;
  float left_chance;
  int plusbus_link;
} link;

/* Data type for all the different vehicle types. */
typedef struct vehicle {
  int id;
  int v;
  int active;
  int is_plusbus;
  int is_bus;
  int has_moved;
  int intersec_counter;
  turn_dir *turn_direction;
} vehicle;


typedef struct cross_intersection {
  link *links[8];
} type_a;

typedef struct plusbus_t_intersection {
  link *links[10];
} type_b;

typedef struct light_data{
    int state;
    int counter;
}light_data;

typedef struct plusbus_cross_intersection_trafficlight {
  link *links[12];
  light_data data;
} type_c;

typedef struct plusbus_t_intersection_trafficlight {
  link *links[8];
  light_data data;
} type_d;

typedef struct plusbus_cross_intersection_trafficlight_only_bus_way {
  link *links[10];
  light_data data;
} type_e;

typedef union intersection_types {
  type_a type_a;
  type_b type_b;
  type_c type_c;
  type_d type_d;
  type_e type_e;
} intersection_types;

struct intersection {
  char type;
  int id;
  int n;
  intersection_types layout;
};

/* Builds the networks. Hardcoded to make the network we want to simulate. */
void build_network(intersection* intersections, link* links);

/* Constructs a typical four way intersection without traffic lights. */
void construct_type_a(intersection* intersection, int id, link* primary1_enter, link* primary1_exit, link* primary2_enter,
                      link* primary2_exit, link* secondary1_enter, link* secondary1_exit, link* secondary2_enter,
                      link* secondary2_exit);


/* Constructs a T-cross intersection without traffic lights. */
void construct_type_b(intersection* intersection, int id, link* primary1_enter, link* primary1_exit, link* primary2_enter,
                      link* primary2_exit, link* secondary1_enter, link* secondary1_exit, link* plusbus1_enter, link* plusbus1_exit,
                      link* plusbus2_enter, link* plusbus2_exit);

/* Constructs a typical four way intersection with traffic light and with separate plusbus lanes*/
void construct_type_c(intersection* intersection, int id, link* primary1_enter, link* primary1_exit, link* primary2_enter,
                      link* primary2_exit, link* secondary1_enter, link* secondary1_exit, link* secondary2_enter,
                      link* secondary2_exit, link* plusbus1_enter, link* plusbus1_exit, link* plusbus2_enter, link* plusbus2_exit);

/*    */
void construct_type_d(intersection* intersection, int id, link* primary1_enter, link* primary1_exit, link* primary2_enter,
                      link* primary2_exit, link* secondary1_enter, link* secondary1_exit, link* plusbus_enter, link* plusbus_exit);

/*  */
void construct_type_e(intersection* intersection, int id, link* primary1_enter, link* primary1_exit, link* primary2_enter,
                      link* primary2_exit, link* secondary1_enter, link* secondary1_exit, link* plusbus1_enter, link* plusbus1_exit,
                      link* plusbus2_enter, link* plusbus2_exit);



/* Returns the internal index in the node of the road that has the given id*/
int internal_index(intersection* intersection, int link_id);
int internal_index_c(intersection* intersection, int link_id);

link* turn(turn_dir dir, intersection* intersection, int link_id);

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you turn left at the intersection */
link* left_turn(intersection* intersection, int link_id);

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you don't turn at the intersection */
link* go_forward(intersection* intersection, int link_id);

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you turn right at the intersection */
link* right_turn(intersection* intersection, int link_id);

link* plusbus_dec(intersection* intersection, int link_id);

int lead_gap(link* link, int pos);

turn_dir decide_turn_dir(link* link, int is_plsubus);
void spawn_car(link* link, vehicle* vehicles);

#endif
