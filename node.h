#pragma once
#include "datatypes.h"

void build_network(link* links, node* n);

/* Does out continue in? I.e can you drive from in to out? */
int continues(int out, int in, node *n);

/* Returns the internal index of the id in the node*/
int link_index_of(int id, node* n);

/* Returns the id of the link that is the next turn in direction dir. */
int search_matrix(int lnk_id, int dir, matrix* m);

/* sets up a node correctly if given the correct input. */
void construct_node(node* n, int id, char* name, int primary1_enter, int primary1_exit,
                    int primary2_enter, int primary2_exit, int secondary1_enter,
                    int secondary1_exit, int secondary2_enter, int secondary2_exit);

/* Adds a given node to a given node matrix */
void add_node_to_matrix(node* n, matrix* m);

/* Given a road, returns the left road at the next node*/
int left_turn(int lnk_id, node *n);

/* Given a road, returns the right road at the next node*/
int right_turn(int lnk_id, node *n);

/* Given a road, returns the forward road at the next node*/
int forward(int lnk_id, node *n);

/* int* new_link(int road_size); */