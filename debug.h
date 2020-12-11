#include "node.h"
#include <stdio.h>
#ifndef DEBUG_H
#define DEBUG_H
void print_link(link* link, vehicle* vehicles);

void print_vehicles(vehicle* vehicles, int len);

void print_status(vehicle*, long int, link* link, int timer);
int check_status(link* link, int amount);
#endif