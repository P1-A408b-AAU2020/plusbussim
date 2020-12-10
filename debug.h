#include "node.h"
#include <stdio.h>
void print_link(link* link, vehicle* vehicles);

void print_vehicles(vehicle* vehicles, int len);

void print_status(vehicle*, long int, link* link, int timer);
int check_status(link* link, int amount);

void print_timestep(int i);

void print_i_data(intersection *intersection);

void new_line();
void print_int(char name[], int p);