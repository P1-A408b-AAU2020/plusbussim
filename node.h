#pragma once
#define CARS 40
#define ROAD_LENGTH 25
#define V_MAX 5
#define PLUS_BUS_LENGTH 5
#define DECELERATE_CHANCE 20
#define MIN_SPEED_RANDOM_DECELERATE 2
#define AMOUNT_LINKS 16
#define AMOUNT_VEHICLES 20
#define TIME_STEPS 20

/* Data type for all the different vehicle types. */
typedef struct vehicle{
    int id;
    int v;
    int active;
    int is_plusbus;
} vehicle;

typedef struct pocket {
    int pos;
    int* road;
    int len;
} pocket;

typedef struct link{
    int id;
    int* road;
    int len;
    pocket left_pocket;
    pocket right_pocket;
    float right_chance;
    float left_chance;
} link;

typedef struct cross_intersection{
    int links[8];
} type_a;

typedef struct t_intersection {
    int links[6];
} type_b;

typedef struct plusbus_cross_intersection {
    int links[12];
    int state;
} type_c;

typedef union intersection_types{
    type_a type_a;
    type_b type_b;
    type_c type_c;
} intersection_types;

typedef struct intersection{
    char type;
    int id;
    intersection_types layout;
} intersection;

/* Builds the networks. Hardcoded to make the network we want to simulate. */
void build_network(intersection* intersections, link* links);

/* Constructs a typical four way intersection without traffic lights. */
void construct_type_a(intersection* intersection, int id, int primary1_enter, int primary1_exit, int primary2_enter,
                      int primary2_exit, int secondary1_enter, int secondary1_exit, int secondary2_enter,
                      int secondary2_exit);

/* Constructs a T-cross intersection without traffic lights. */
void construct_type_b(intersection* intersection, int id, int primary1_enter, int primary1_exit, int primary2_enter,
                      int primary2_exit, int secondary1_enter, int secondary1_exit);

/* Constructs a typical four way intersection with traffic light and with separate plusbus lanes*/
void construct_type_c(intersection* intersection, int id, int primary1_enter, int primary1_exit, int primary2_enter,
                      int primary2_exit, int secondary1_enter, int secondary1_exit, int secondary2_enter,
                      int secondary2_exit, int plusbus1_enter, int plusbus1_exit, int plusbus2_enter, int plusbus2_exit);

int right_turn_type_a(intersection* intersection, int link_id);
int right_turn_type_b(intersection* intersection, int link_id);

/* Returns the internal index in the node of the road that has the given id*/
int internal_index_a(intersection* intersection, int link_id);
int internal_index_c(intersection* intersection, int link_id);

int right_turn_type_a(intersection* intersection, int link_id);
int left_turn_type_a(intersection* intersection, int link_id);
int forward_type_a(intersection* intersection, int link_id);

int right_turn_type_b(intersection* intersection, int link_id);
int left_turn_type_b(intersection* intersection, int link_id);
int forward_type_b(intersection* intersection, int link_id);

int plusbus_type_c(intersection *intersection, int link_id);
int forward_type_c(intersection *intersection, int link_id);
int left_turn_type_c(intersection *intersection, int link_id);
int right_turn_type_c(intersection *intersection, int link_id);

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you turn left at the intersection */
int left_turn(intersection* intersection, int link_id);

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you don't turn at the intersection */
int go_forward(intersection* intersection, int link_id);

/* If you arrive at the given intersection on the given link,
 * returns the road you land on if you turn right at the intersection */
int right_turn(intersection* intersection, int link_id);

/* Populates the roads with vehicles */
void initialize_actors(vehicle* actors, link* links, int len);

/* Returns the gap between position and the vehicle in front with a range of V_MAX */
int lead_gap(link* link, int pos);

/* Accelerates all vehicles on the link. */
void accelerate_link(link* link, vehicle* vehicles);

/* Moves all vehicles on the link. */
void move_link(link* link, vehicle* vehicles);

/* decelerates all vehicles on the link. */
void decelerate_link(link* link, vehicle* vehicles);

/* Runs the next time step. */
void time_step(link* links, vehicle* vehicles);