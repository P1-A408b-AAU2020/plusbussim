#include "node.h"
#include "debug.h"
#include "trafficlights.h"

#include <stdlib.h>
#include <time.h>

int main(void) {
    time_t seed = time(NULL);
    srand(seed);

    link links[AMOUNT_LINKS];
    intersection nodes[1];
    vehicle vehicles[CARS];
    build_network(nodes, links);
    initialize_actors(vehicles, links, 12);

    for (int j = 0; j < TIME_STEPS; ++j) {
        printf("seed: %-5d\n", seed);
        print_link(links, vehicles);
        time_step(links, vehicles);
    }

    for (int j = 0; j < AMOUNT_LINKS; ++j) {
        free(links[j].road);
    }
    return EXIT_SUCCESS;
}


