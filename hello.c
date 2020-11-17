/* Hello from the other siiide! lul*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROAD_SIZE 50
#define AMOUNT_VEHICLES 10
#define V_MAX 5

struct vehicle{
  int id;
  int v;
};

void printlane(int*, int, struct vehicle* );
void initactors(int*, int, struct vehicle*);
void tstep(int*, int, struct vehicle*);
void acc(int* link, int len, struct vehicle* actors);
void move(int* link, int len, struct vehicle* actors);

int main(void){
  int i;
  
  /* Main setup */
  int* link = (int*)calloc(ROAD_SIZE, sizeof(int));
  
  /* + 1 because idx 0 is reserved for empty grid */
  struct vehicle* actors = (struct vehicle*)calloc(ROAD_SIZE + 1, sizeof(struct vehicle)); 

  srand(time(NULL));
  initactors(link, ROAD_SIZE, actors);

  /* Print initial lane */
  printlane(link, ROAD_SIZE, actors);

  for(i = 0; i < 10; i++)
    tstep(link, ROAD_SIZE, actors);
}

void initactors(int* link, int len, struct vehicle* actors){
  int i, j = AMOUNT_VEHICLES, pos = 0;

  /* Generate actors _WORK IN PROGRESS_ */
  for(i = 1; i <= AMOUNT_VEHICLES; i++){
    actors[i].id = i - 1;
    actors[i].v = 0;
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

void tstep(int* link, int len, struct vehicle* actors){
  acc(link, len, actors);
  move(link, len, actors);
  printlane(link, ROAD_SIZE, actors);
}

void acc(int* link, int len, struct vehicle* actors){
  int i;
  for(i = 0; i < AMOUNT_VEHICLES; i++)
    if (actors[i].v < V_MAX)
      actors[i].v++;
}

void move(int* link, int len, struct vehicle* actors){
  int i, a;
  for(i = len; i >= 0; i--){
    a = link[i];
    if (link[i] > 0)
      if(actors[a].v > 0){
	link[i] = 0;
	link[i + actors[a].v] = a;
      }
  }
}

void printlane(int* link, int len, struct vehicle* actors){
  int i;
  char prnt;
  for(i = 0; i < len; i++){
    prnt = link[i] > 0? actors[link[i]].v + '0' : '.';
    printf("%c", prnt);
  }
  printf("\n");
}

