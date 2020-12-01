
#include <stdlib.h>
#include "node.h"

turn_dir decide_turn_dir(link* link){
  int dir = rand()%100 + 1;
  if (dir < link->left_chance)
    return left;
  else if (dir < link->left_chance + link->right_chance)
    return right;
  else
    return forward
  }



  return dir;
}