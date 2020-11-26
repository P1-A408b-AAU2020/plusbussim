#pragma once
#define CARS 20
typedef struct vehicle{
    int id;
    int v;
    int active;
    int is_plusbus;
} vehicle;

typedef struct link{
    int id;
    int* road;
    int len;
} link;

typedef struct cross_intersection{
    int links[8];
} type_a;

typedef struct t_intersection {
    int links[6];
} type_b;

typedef union intersection_types{
    type_a type_a;
    type_b type_b;
} intersection_types;

typedef struct intersection{
    char type;
    int id;
    intersection_types layout;
} intersection;

void build_network(intersection* intersections, link* links);

void construct_type_a(intersection* intersection, int id, int primary1_enter, int primary1_exit, int primary2_enter,
                      int primary2_exit, int secondary1_enter, int secondary1_exit, int secondary2_enter,
                      int secondary2_exit);

void construct_type_b(intersection* intersection, int id, int primary1_enter, int primary1_exit, int primary2_enter,
                      int primary2_exit, int secondary1_enter, int secondary1_exit);

int right_turn_type_a(intersection* intersection, int link_id);
int right_turn_type_b(intersection* intersection, int link_id);

int internal_index(intersection* intersection, int link_id);

int right_turn_type_a(intersection* intersection, int link_id);
int left_turn_type_a(intersection* intersection, int link_id);
int forward_type_a(intersection* intersection, int link_id);

int right_turn_type_b(intersection* intersection, int link_id);
int left_turn_type_b(intersection* intersection, int link_id);
int forward_type_b(intersection* intersection, int link_id);

int left_turn(intersection* intersection, int link_id);
int forward(intersection* intersection, int link_id);
int right_turn(intersection* intersection, int link_id);

void initialize_actors(vehicle* actors, link* links, int len);
void print_link(link* link, vehicle* vehicles);
void print_vehicles(vehicle* vehicles, int len);