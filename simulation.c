#include "node.h"
#include "debug.h"
#include <stdlib.h>
#include <time.h>

int main(void) {
    time_t seed = time(NULL);
    srand(seed);

    link links[AMOUNT_LINKS];
    intersection nodes[2];
    vehicle vehicles[CARS];
    build_network(nodes, links);
    initialize_actors(vehicles, links, AMOUNT_LINKS);

    for (int j = 0; j < TIME_STEPS; ++j) {
        print_link(links, vehicles);
        time_step(links, vehicles);
    }

    for (int j = 0; j < AMOUNT_LINKS; ++j) {
        free(links[j].road);
    }
    return EXIT_SUCCESS;
}


