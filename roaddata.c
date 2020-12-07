#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NUM_OF_LINKS 64
#define CELL_LEN 4.629
#define JYLGADE_1_LEN (int)(round(200/CELL_LEN))
#define JYLGADE_2_LEN (int) (round(120/CELL_LEN))
#define AAGADE_LEN (int) (round(150/CELL_LEN))
#define JYLGADE_3_LEN (int) (round(120/CELL_LEN))
#define NIELS_EBS_GADE_LEN (int) (round(120/CELL_LEN))
#define DAG_HAM_GADE_1_LEN (int) (round(70/CELL_LEN))
#define JYLGADE_4_LEN (int) (round(300/CELL_LEN))
#define DAG_HAM_GADE_2_LEN (int) (round(100/CELL_LEN))
#define SDRBRO_LEN (int) (round(300/CELL_LEN))
#define FYENSGADE_LEN (int) (round(180/CELL_LEN))
#define KJELRUPSGADE_LEN (int) (round(160/CELL_LEN))
#define KAROLUNDSVEJ_LEN (int) (round(350/CELL_LEN))
#define BORNHOLMSGADE_1_LEN (int) (round(110/CELL_LEN))
#define FAEROESGADE_1_LEN (int) (round(160/CELL_LEN))
#define BORNHOLMSGADE_2_LEN (int) (round(190/CELL_LEN))
#define FAEROESGADE_2_LEN (int) (round(230/CELL_LEN))
#define SJAELGADE_1_LEN (int) (round(160/CELL_LEN))
#define BORNHOLMSGADE_3_LEN (int) (round(220/CELL_LEN))
#define SJAELGADE_2_LEN (int) (round(250/CELL_LEN))
#define OESTER_ALLE_1_LEN (int) (round(250/CELL_LEN))
#define SGHSVEJ_1_LEN (int) (round(300/CELL_LEN))
#define OESTER_ALLE_2_LEN (int) (round(300/CELL_LEN))
#define KRIDTSJLFEN_LEN (int) (round(100/CELL_LEN))
#define SGHSVEJ_2_LEN (int) (round(400/CELL_LEN))
#define BERNSTFFGADE_LEN (int) (round(280/CELL_LEN))


typedef enum roadid {
    jylgade_1_east, jylgade_1_west_plusbus, jylgade_1_east_plusbus,
    jylgade_2_east_plusbus, jylgade_2_west_plusbus, jylgade_2_east,
    jylgade_2_west, aagade_north, aagade_south, jylgade_1_west,

    jylgade_3_east_plusbus, jylgade_3_west_plusbus, jylgade_3_east,
    jylgade_3_west, niels_ebbesens_gade_south, niels_ebbesens_gade_north,

    dag_ham_gade_1_south, dag_ham_gade_1_north,
    jylgade_4_east_plusbus, jylgade_4_west_plusbus, jylgade_4_east,
    jylgade_4_west, dag_ham_gade_2_north, dag_ham_gade_2_south,

    sdrbro_south, sdrbro_north, fyensgade_east_plusbus, fyensgade_west_plusbus,
    fyensgade_east, fyensgade_west, kjellerupsgade_north, kjellerupsgade_south,

    bornholmsgade_1_south, bornholmsgade_1_north, karolinelundsvej_north, karolinelundsvej_south,

    faereogade_1_west, faergade_1_east, bornholmsgade_2_south, bornholmsgade_2_north,
    faereogade_2_east, faereogade_2_west,

    sjaelgade_1_west, sjaelgade_1_east, bornholmsgade_3_south, bornholmsgade_3_north,
    sjaelgade_2_east, sjaelgade_2_west,

    oester_alle_1_west, oester_alle_1_east, sghsvej_1_south, sghsvej_1_south_plusbus,
    sghsvej_1_north_plusbus, sghsvej_1_north, oester_alle_2_east, oester_alle_2_west,

    kridtsleofen_west, kridtsleofen_east, sghsvej_2_south, sghsvej_2_south_plusbus,
    sghsvej_2_north_plusbus, sghsvej_2_north, bernstorffsgade_east, bernstorffsgade_west
} roadid;

typedef struct pocket {
    int pos;
    int* road;
    int len;
} pocket;

typedef struct link {
    int id;
    int* road;
    int len;
    pocket right_pocket_lane;
    pocket left_pocket_lane;
} link;

int init_road_data() {
    link links[NUM_OF_LINKS];
    int i = 0;
    int j = 0;
    int k = 0;
    /* M�ske tilf�j definiation af l�ngde af gader */
    int link_length[NUM_OF_LINKS] = { JYLGADE_1_LEN, JYLGADE_1_LEN, JYLGADE_1_LEN, JYLGADE_2_LEN, JYLGADE_2_LEN,
                                     JYLGADE_2_LEN, JYLGADE_2_LEN, AAGADE_LEN, AAGADE_LEN, JYLGADE_1_LEN,

                                     JYLGADE_3_LEN, JYLGADE_3_LEN, JYLGADE_3_LEN, JYLGADE_3_LEN,
                                     NIELS_EBS_GADE_LEN, NIELS_EBS_GADE_LEN,

                                     DAG_HAM_GADE_1_LEN, DAG_HAM_GADE_1_LEN, JYLGADE_4_LEN, JYLGADE_4_LEN,
                                     JYLGADE_4_LEN, JYLGADE_4_LEN, DAG_HAM_GADE_2_LEN, DAG_HAM_GADE_2_LEN,

                                     SDRBRO_LEN, SDRBRO_LEN, FYENSGADE_LEN, FYENSGADE_LEN, FYENSGADE_LEN,
                                     FYENSGADE_LEN, KJELRUPSGADE_LEN, KJELRUPSGADE_LEN,

                                     BORNHOLMSGADE_1_LEN, BORNHOLMSGADE_1_LEN, KAROLUNDSVEJ_LEN, KAROLUNDSVEJ_LEN,

                                     FAEROESGADE_1_LEN, FAEROESGADE_1_LEN, BORNHOLMSGADE_2_LEN, BORNHOLMSGADE_2_LEN,
                                     FAEROESGADE_2_LEN, FAEROESGADE_2_LEN,

                                     SJAELGADE_1_LEN, SJAELGADE_1_LEN, BORNHOLMSGADE_3_LEN, BORNHOLMSGADE_3_LEN,
                                     SJAELGADE_2_LEN, SJAELGADE_2_LEN,

                                     OESTER_ALLE_1_LEN, OESTER_ALLE_1_LEN, SGHSVEJ_1_LEN, SGHSVEJ_1_LEN,
                                     SGHSVEJ_1_LEN, SGHSVEJ_1_LEN, OESTER_ALLE_2_LEN, OESTER_ALLE_2_LEN,

                                     KRIDTSJLFEN_LEN, KRIDTSJLFEN_LEN, SGHSVEJ_2_LEN, SGHSVEJ_2_LEN,
                                     SGHSVEJ_2_LEN, SGHSVEJ_2_LEN, BERNSTFFGADE_LEN, BERNSTFFGADE_LEN
    };

    int right_pocket_lane[4] = { sdrbro_north, kjellerupsgade_south, oester_alle_1_east,
                                sghsvej_1_north };
    int left_pocket_lane[5] = { dag_ham_gade_1_north, dag_ham_gade_2_south, kjellerupsgade_south,
                               karolinelundsvej_south, oester_alle_2_west };

    for (i = jylgade_1_east; i <= bernstorffsgade_west; i++) {
        links[i].id = i;
        links[i].len = link_length[i];

        if (links[i].id == right_pocket_lane[j]) {
            /* set this to a pocket lane */
            links[i].right_pocket_lane = 1;
            j++;
        }
        else
            /* default value for no pocket lane */
            links[i].right_pocket_lane = 0;

        if (links[i].id == left_pocket_lane[k]) {
            links[i].left_pocket_lane = 1;
            k++;
        }
        else
            links[i].left_pocket_lane = 0;
    }

    for (i = 0; i < NUM_OF_LINKS; i++) {
        printf("LINK %d\nid = %d \nlength = %d \nright pocket lane = %d\nleft pocket lane = %d\n\n",
            i + 1, links[i].id, links[i].len, links[i].right_pocket_lane, links[i].left_pocket_lane);
    }

    return EXIT_SUCCESS;
}
