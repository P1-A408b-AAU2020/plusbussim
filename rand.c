int my_prob(int i, int prob){
  if(i < prob)
    return 1;
  else
    return 0;
}


void turn_off_lane(int* link, struct vehicle* actors, int prob, int len){
  int r = rand() % 100;
  int i = (rand() % AMOUNT_VEHICLES) +1;
  int pos = rand() % len;
  if(my_prob(r, prob) == 1){
    actors[i].v = 0;
    actors[i].id = 0;
  }
}

