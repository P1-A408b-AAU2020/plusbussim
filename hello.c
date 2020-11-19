/* Hello from the other siiide! lul*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROAD_SIZE 100
#define AMOUNT_VEHICLES 40
#define V_MAX 5
#define TIME_STEPS 20
#define DECELERATE_CHANCE 20
#define MIN_SPEED_RANDOM_DECELERATE 2

struct vehicle{
  int id;
  int v;
  int active;
};

void print_actors(struct vehicle* actors);
void print_lane(int*, int, struct vehicle*);
void init_actors(int*, int, struct vehicle*);
void time_step(int*, int, struct vehicle*);
void accellerate(int*, int, struct vehicle*);
void decelerate(int*, int, struct vehicle*);
void move(int*, int, struct vehicle*);
int lead_gap(int*, int, int);

int main(void){
  int i, active = 0, disabled = 0;
  
  /* Main setup */
  int* link = (int*)calloc(ROAD_SIZE, sizeof(int));
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

/* Places vehicles on the road. The vehicles are randomly generated and placed. */
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

/* Each time step of the simulation, this is run. */
void time_step(int* link, int len, struct vehicle* actors){
  move(link, len, actors);
  accellerate(link, len, actors);
  decelerate(link, len, actors);
  print_lane(link, ROAD_SIZE, actors);
}

/* Accelerates all vehicles */
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

/* Decelerates all vehicles */
void decelerate(int* link, int len, struct vehicle* actors){
  int i, v, gap;
  for(i = 0; i < len; i++){
    v = actors[link[i]].v;
    gap = lead_gap(link, len, i);

    if(gap < v)
      actors[link[i]].v = gap;
    else if(rand() % 100 <= DECELERATE_CHANCE && v > MIN_SPEED_RANDOM_DECELERATE)
      actors[link[i]].v--;    
  }
}

/* Returns the lead gap in front of given position */
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
  /* If the car reaches the end of the road */
  return V_MAX; 
}

/* Moves all vehicles by their speed. Removes them from the road if they reach the end. */
void move(int* link, int len, struct vehicle* actors){
  int i, a, mov;
  for(i = len-1; i >= 0; i--){
    a = link[i];
    if (a > 0){  
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

void print_actors(struct vehicle* actors){
  int i;
  for(i = 1; i < AMOUNT_VEHICLES+1; i++){
    printf("Car %d:\n  v: %d\n", actors[i].id, actors[i].v);
  }
}

/* Prints out A SINGLE LANE of the simulation. */
void print_lane(int* link, int len, struct vehicle* actors){
  int i;
  char print;
  for(i = 0; i < len; i++){
      print = link[i] > 0 ? actors[link[i]].v + '0' : '.';
      printf("%c", print);
  }
  printf("\n");
}
