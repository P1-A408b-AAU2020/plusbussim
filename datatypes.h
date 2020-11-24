#pragma once
#include "variables.h"

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

typedef struct matrix{
    int size_x, size_y;
    int grid[AMOUNT_LINKS][AMOUNT_LINKS];
} matrix;

typedef struct node {
    int id;
    char name[NODE_NAME_MAX_SIZE];
    int links[8];

}node;
