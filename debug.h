#pragma once
#include "datatypes.h"
#include <stdio.h>
#include "datatypes.h"
#include "variables.h"

void print_actors(struct vehicle* actors);
void print_lane(const int*, int, struct vehicle*);
void print_status(struct vehicle*, long int);