#include "node.h"
#include <string.h>
#include <stdio.h>

#define RIGHT 1
#define LEFT 5
#define FORWARD 3

/* The contents of this function are predefined. Make changes to how network here. */
void build_network(link* links, node* n){
    int a[25], b[25], c[25], d[25], e[25], f[25], g[25], h[25], j[25], k[25], l[25], m[25], o[25], p[25], q[25], r[25];
    int* A[25] ={a, b, c, d, e, f, g, h, j, k, l, m, o, p, q, r};
    int i;

    for(i = 0; i < 8; i++){
        links[i].id = 0;
        links[i].road = A[i];
        links[i].len = 25;
    }
    construct_node(n, 0, "TEST_NODE_1",0,3,4,7,2,5,6,1);

    for(i = 8; i < 16; i++){
        links[i].id = 0;
        links[i].road = A[i];
        links[i].len = 25;
    }
    construct_node(n, 1, "TEST_NODE_2",3,11,12,4,10,13,14,9);

}

/* TODO: This should be cleaned up */
void construct_node(node *n, int id, char *name, int primary1_enter, int primary1_exit, int primary2_enter,
                    int primary2_exit, int secondary1_enter, int secondary1_exit, int secondary2_enter,
                    int secondary2_exit) {
    (n+id)->id = id;
    strcpy(n[id].name, name);
    n[id].links[0] = primary1_enter;
    n[id].links[1] = secondary2_exit;
    n[id].links[2] = secondary1_enter;
    n[id].links[3] = primary1_exit;
    n[id].links[4] = primary2_enter;
    n[id].links[5] = secondary1_exit;
    n[id].links[6] = secondary2_enter;
    n[id].links[7] = primary2_exit;
}

int continues(int out, int in, node *n) {
    int idx_in = link_index_of(in, n), idx_out = link_index_of(out, n);
    if(idx_in == -1 || idx_out == -1 || (idx_in + idx_out) % 7 == 0)
        return 0;
    else
        return !(out % 2);
}

int link_index_of(int id, node *n) {
    int i;
    for (i = 0; i < 8; ++i) {
        if(n->links[i] == id)
            return i;
    }
    return -1;
}

int right_turn(int lnk_id, node *n) {
    return n->links[(link_index_of(lnk_id, n) + RIGHT) % 7];
}

int left_turn(int lnk_id, node *n) {
    int res = (link_index_of(lnk_id, n) + LEFT) % 7;
    return 0 ? n->links[7] : n->links[res];
}

int forward(int lnk_id, node *n) {
    return n->links[(link_index_of(lnk_id, n) + FORWARD) % 7];
}

/* int* new_link(int road_size) {
    return (int*)calloc(road_size, sizeof(int));
} */