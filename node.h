#pragma once
#define ROAD_LENGTH 50
#define V_MAX 5
#define PLUS_BUS_LENGTH 5
#define DECELERATE_CHANCE 0
#define MIN_SPEED_RANDOM_DECELERATE 2
#define AMOUNT_LINKS 64
#define AMOUNT_VEHICLES 10
#define TIME_STEPS 70
#define CELL_LEN 4.629
#define JYLGADE_1_LEN (int)(round(200/CELL_LEN))
#define JYLGADE_2_LEN (int) (round(120/CELL_LEN))
#define AAGADE_LEN (int) (round(150/CELL_LEN))
#define JYLGADE_3_LEN (int) (round(120/CELL_LEN))
#define NIELS_EBS_GADE_LEN (int) (round(120/CELL_LEN))
#define DAG_HAM_GADE_1_LEN (int) (round(70/CELL_LEN))
#define JYLGADE_4_LEN (int) (round(300/CELL_LEN))
#define DAG_HAM_GADE_2_LEN (int) (round(100/CELL_LEN))
#define SDRBRO_LEN (int) (round(300/CELL_LEN))
#define FYENSGADE_LEN (int) (round(180/CELL_LEN))
#define KJELRUPSGADE_LEN (int) (round(160/CELL_LEN))
#define KAROLUNDSVEJ_LEN (int) (round(350/CELL_LEN))
#define BORNHOLMSGADE_1_LEN (int) (round(110/CELL_LEN))
#define FAEROESGADE_1_LEN (int) (round(160/CELL_LEN))
#define BORNHOLMSGADE_2_LEN (int) (round(190/CELL_LEN))
#define FAEROESGADE_2_LEN (int) (round(230/CELL_LEN))
#define SJAELGADE_1_LEN (int) (round(160/CELL_LEN))
#define BORNHOLMSGADE_3_LEN (int) (round(220/CELL_LEN))
#define SJAELGADE_2_LEN (int) (round(250/CELL_LEN))
#define OESTER_ALLE_1_LEN (int) (round(250/CELL_LEN))
#define SGHSVEJ_1_LEN (int) (round(300/CELL_LEN))
#define OESTER_ALLE_2_LEN (int) (round(300/CELL_LEN))
#define KRIDTSJLFEN_LEN (int) (round(100/CELL_LEN))
#define SGHSVEJ_2_LEN (int) (round(400/CELL_LEN))
#define BERNSTFFGADE_LEN (int) (round(280/CELL_LEN))

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

typedef struct pocket {
    int pos;
    int* road;
    int len;
} pocket;

typedef struct link {
    int id;
    int *road;
    int len;
    int time_step;
    intersection *intersection;
    pocket left_pocket;
    pocket right_pocket;
    int spawn_lane;
    double spawn_chance;
    float right_chance;
    float left_chance;
} link;

/* Data type for all the different vehicle types. */
typedef struct vehicle{
    int id;
    int v;
    int active;
    int is_plusbus;
    turn_dir turn_direction;
    int has_moved;
} vehicle;


typedef struct cross_intersection{
    link* links[8];
} type_a;

typedef struct plusbus_t_intersection {
    link* links[10];
} type_b;

typedef struct plusbus_cross_intersection_trafficlight {
    link* links[12];
    int state;
} type_c;

typedef struct plusbus_t_intersection_trafficlight {
    link* links[8];
    int state;
} type_d;

typedef struct plusbus_cross_intersection_trafficlight_only_bus_way{
    link* links[10];
    int state;
} type_e;

typedef union intersection_types{
    type_a type_a;
    type_b type_b;
    type_c type_c;
    type_d type_d;
    type_e type_e;
} intersection_types;

typedef struct intersection{
    char type;
    int id;
    intersection_types layout;
} intersection;

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

link* right_turn_type_a(intersection* intersection, int link_id);
link* left_turn_type_a(intersection* intersection, int link_id);
link* forward_type_a(intersection* intersection, int link_id);

link* right_turn_type_b(intersection* intersection, int link_id);
link* left_turn_type_b(intersection* intersection, int link_id);
link* forward_type_b(intersection* intersection, int link_id);

link* plusbus_type_c(intersection *intersection, int link_id);
link* forward_type_c(intersection *intersection, int link_id);
link* left_turn_type_c(intersection *intersection, int link_id);
link* right_turn_type_c(intersection *intersection, int link_id);

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you turn left at the intersection */
link* left_turn(intersection* intersection, int link_id);

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you don't turn at the intersection */
link* go_forward(intersection* intersection, int link_id);

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you turn right at the intersection */
link* right_turn(intersection* intersection, int link_id);

link* plusbus_dec(intersection *intersection, int link_id);

int lead_gap(link* link, int pos);

turn_dir decide_turn_dir(link* link, int is_plsubus);
void spawn_car(link* link, vehicle* vehicles);