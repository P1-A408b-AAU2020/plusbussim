#pragma once
#include "datatypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "debug.h"
#include "variables.h"

void init_actors(int*, int, struct vehicle*);
void time_step(int*, int, struct vehicle*);
void accellerate(int*, int, struct vehicle*);
void decelerate(int*, int, struct vehicle*);
void move(int*, int, struct vehicle*);
int lead_gap(int*, int, int);
