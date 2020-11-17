/* Hello from the other siiide! lul*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROAD_SIZE 100
#define AMOUNT_VEHICLES 20
#define V_MAX 5
#define TIME_STEPS 20
#define DECCELLERATE_CHANCE 20
#define MIN_SPEED_RANDOM_DECELLERATE 2

struct vehicle{
  int id;     /* could be removed? (Unused field) */
  int v;
  int active; /* could be char to save space */
};

void print_lane(int*, int, struct vehicle*);
void init_actors(int*, int, struct vehicle*);
void time_step(int*, int, struct vehicle*);
void accellerate(int*, int, struct vehicle*);
void decellerate(int*, int, struct vehicle*);
void move(int*, int, struct vehicle*);
int lead_gap(int*, int, int);

int main(void){
  int i, active = 0, disabled = 0;
  
  /* Main setup */
  int* link = (int*)calloc(ROAD_SIZE, sizeof(int));
   
  /* + 1 because idx 0 is reserved for empty grid */
  struct vehicle* actors = (struct vehicle*)calloc(ROAD_SIZE + 1, sizeof(struct vehicle)); 

  srand(time(NULL));
  init_actors(link, ROAD_SIZE, actors);

  /* Print initial lane */
  print_lane(link, ROAD_SIZE, actors);

  for(i = 0; i < TIME_STEPS; i++){
    time_step(link, ROAD_SIZE, actors);
  }

  for(i = 1; i < ROAD_SIZE + 1; i++){
    if(actors[i].active == 1)
      active++;
    else
      disabled++;
  }
  printf("%s %s %s\n%-9s%-10d%-7d%-2c%-d\n", "Status: ", "Runtime: ", "Active / disabled vehicles: ",
	 "OK", TIME_STEPS, active, '/', disabled); 
  
  free(link);
  free(actors);
  return EXIT_SUCCESS;
}

void init_actors(int* link, int len, struct vehicle* actors){
  int i, j = AMOUNT_VEHICLES, pos = 0;

  /* Generate actors */
  for(i = 1; i <= AMOUNT_VEHICLES; i++){
    actors[i].id = i;
    actors[i].v = 0;
    actors[i].active = 1;
  }
  
  /* Place actors on road */
  for(i = 0; i < AMOUNT_VEHICLES; i++){
    pos = rand()%len;
    if(link[pos] != 0)
      i--;
    else
      link[pos] = actors[j--].id;
  }
}

void time_step(int* link, int len, struct vehicle* actors){
  move(link, len, actors);
  accellerate(link, len, actors);
  decellerate(link, len, actors);
  print_lane(link, ROAD_SIZE, actors);
}

/* Accellerates all vehicles */
/* Could this be more efficient using pointers for v? */
void accellerate(int* link, int len, struct vehicle* actors){
  int i, v, gap;
  for(i = 0; i < len; i++){
    v = actors[link[i]].v;
    gap = lead_gap(link, len, i);

    if(v < V_MAX && gap > v)
      actors[link[i]].v++;
  }
}

void decellerate(int* link, int len, struct vehicle* actors){
  int i, v, gap;
  for(i = 0; i < len; i++){
    v = actors[link[i]].v;
    gap = lead_gap(link, len, i);

    if(gap < v)
      actors[link[i]].v = gap;
    if(rand() % 100 <= DECCELLERATE_CHANCE && v > MIN_SPEED_RANDOM_DECELLERATE)
      actors[link[i]].v--;    

  }
}

/* Returns the lead gap in front of position */
int lead_gap(int* link, int len, int pos){
  int i, gap = 0;
  for(i = pos + 1; i < len; i++){
    if(link[i] == 0)
      gap++;
    else
      return gap;
    if(gap > V_MAX)
      return V_MAX;
  }
  return V_MAX; /* If the car reaches the end of the road */ 
}

void move(int* link, int len, struct vehicle* actors){
  int i, a, mov;
  for(i = len; i >= 0; i--){
    a = link[i];
    if (link[i] > 0){
      if(actors[a].v > 0){
        link[i] = 0;
	mov = i + actors[a].v;
	if(mov < len){
	  link[mov] = a;
	}
	else{
	  actors[a].active = 0;
	}
      }  
    }
  }
}

void print_lane(int* link, int len, struct vehicle* actors){
  int i;
  char prnt;
  for(i = 0; i < len; i++){
    prnt = link[i] > 0? actors[link[i]].v + '0' : '.';
    printf("%c", prnt);
  }
  printf("\n");
}

