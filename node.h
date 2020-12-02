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

typedef enum turn_dir{forward, right, left} turn_dir;

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
} vehicle;


typedef struct cross_intersection{
    link links[8];
} type_a;

typedef struct t_intersection {
    link links[6];
} type_b;

typedef struct plusbus_cross_intersection {
    link links[12];
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
void construct_type_a(intersection* intersection, int id, link* primary1_enter, link* primary1_exit, link* primary2_enter,
                      link* primary2_exit, link* secondary1_enter, link* secondary1_exit, link* secondary2_enter,
                      link* secondary2_exit);

/* Constructs a T-cross intersection without traffic lights. */
void construct_type_b(intersection* intersection, int id, int primary1_enter, int primary1_exit, int primary2_enter,
                      int primary2_exit, int secondary1_enter, int secondary1_exit);

/* Constructs a typical four way intersection with traffic light and with separate plusbus lanes*/
void construct_type_c(intersection* intersection, int id, int primary1_enter, int primary1_exit, int primary2_enter,
                      int primary2_exit, int secondary1_enter, int secondary1_exit, int secondary2_enter,
                      int secondary2_exit, int plusbus1_enter, int plusbus1_exit, int plusbus2_enter, int plusbus2_exit);

/* Returns the internal index in the node of the road that has the given id*/
int internal_index_a(intersection* intersection, int link_id);
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

/* Populates the roads with vehicles */
void initialize_actors(vehicle* actors, link* links, int len);

/* Returns the gap between position and the vehicle in front with a range of V_MAX */
int lead_gap(link* link, int pos);

/* Accelerates all vehicles on the link. */
void accelerate_link(link* link, vehicle* vehicles);

int current_time_step(int increase);

void simulate_all_links(link* links, vehicle* vehicles);

/* Moves all vehicles on the link. */
/*void move_link(link* link, vehicle* vehicles);*/

/* decelerates all vehicles on the link. */
void decelerate_link(link* link, vehicle* vehicles);

/* Runs the next time step. */
void time_step(link* links, vehicle* vehicles);