#include "node.h"
#include <stdio.h>
#ifndef DEBUG_H
#define DEBUG_H

void print_link(link* link, vehicle* vehicles);
void print_status(vehicle*, long int, int timer);
void new_line();
void print_int(char name[], int p);

#endif
