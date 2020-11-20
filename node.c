#include <stdlib.h>
#include "node.h"
#include "datatypes.h"
#include "variables.h"
#include <string.h>

#define RIGHT 1
#define LEFT -1
#define FORWARD 0

/* TODO: This should be cleaned up */
void construct_node(node *n, int id, char *name, int primary1_enter, int primary1_exit, int primary2_enter,
                    int primary2_exit, int secondary1_enter, int secondary1_exit, int secondary2_enter,
                    int secondary2_exit) {
    n->id = id;
    strcpy(n->name, name);
    n->links[0] = primary1_enter;
    n->links[1] = secondary2_exit;
    n->links[2] = secondary1_enter;
    n->links[3] = primary1_exit;
    n->links[4] = primary2_enter;
    n->links[5] = secondary1_exit;
    n->links[6] = secondary2_enter;
    n->links[7] = primary2_exit;
}

void add_node_to_matrix(node *n, matrix *m) {
    int i;
    for (i = 0; i < 8; i+=2) {
        m->grid[n->links[i]][n->links[(i+3) % 7]] = FORWARD;
        m->grid[n->links[i]][n->links[(i+1) % 7]] = RIGHT;
        m->grid[n->links[i]][n->links[(i+5) % 7]] = LEFT;
    }
}

int right_turn(int lnk_id, matrix *m) {
    return search_matrix(lnk_id, RIGHT, m);
}

int left_turn(int lnk_id, matrix *m) {
    return search_matrix(lnk_id, LEFT, m);
}

int forward(int lnk_id, matrix *m) {
    return search_matrix(lnk_id, FORWARD, m);
}

matrix nodes(){
    matrix m = {AMOUNT_LINKS, AMOUNT_LINKS};
    m.grid[0][1] = RIGHT; /* More than half the array slots are never used. */
}

int search_matrix(int lnk_id, int dir, matrix *m) {
    int i;
    for (i = dir + 1; i < m->size_y; ++i) {
        if(m->grid[lnk_id][i] == dir)
            return i;
    }
}
