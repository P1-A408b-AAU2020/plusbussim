struct vehicle{
    int id;
    int v;
    int active;
};

void init_actors(int*, int, struct vehicle*);
void time_step(int*, int, struct vehicle*);
void accellerate(int*, int, struct vehicle*);
void decelerate(int*, int, struct vehicle*);
void move(int*, int, struct vehicle*);
int lead_gap(int*, int, int);
