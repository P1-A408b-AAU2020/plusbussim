#include "node.h"
#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void) {
    time_t seed = time(NULL);
    srand(seed);

    link links[AMOUNT_LINKS];
    intersection nodes[2];
    vehicle vehicles[CARS];
    build_network(nodes, links);
    initialize_actors(vehicles, links, AMOUNT_LINKS);

    print_vehicles(vehicles, AMOUNT_VEHICLES);
    for (int j = 0; j < TIME_STEPS; ++j) {
        simulate_all_links(links, vehicles);
    }

    for (int j = 0; j < AMOUNT_LINKS; ++j) {
        free(links[j].road);
    }
    return EXIT_SUCCESS;
}


