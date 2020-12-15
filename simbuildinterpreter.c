#include "simbuildinterpreter.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "node.h"
#define MAX_LINE_LENGTH 500 /* Probably overkill */

void interpret_node(const char* str, intersection*);
void interpret_link(const char *str, link* link, intersection*);
void build_link(link *link, int id, int len, double left_chance, double right_chance, intersection *to, intersection *from);

union interpretation{
  intersection intersection;
  link link;
};

/* Returns whether reading the next line was successful */
int read_line(FILE *file, union interpretation *interp, intersection* nodes);

internal_name link_name(char prim, int dir, int to) {
  internal_name result;
  if (!to)
    switch (prim) {
      case 'p':
        result = dir == 1 ? p1i : p2i; break;
      case 's':
        result = dir == 1 ? s1i : s2i; break;
      case 'b':
        result = dir == 1 ? b1i : b2i; break;
    }
  else
    switch (prim) {
      case 'p':
        result = dir == 1 ? p1o : p2o; break;
      case 's':
        result = dir == 1 ? s1o : s2o; break;
      case 'b':
        result = dir == 1 ? b1o : b2o; break;
    }
  return result;
}
void interpret_node(const char *str, intersection* node) {
  sscanf(str, " node %d: type_%c, %d", &node->id, &node->type, &node->n);


    if (node->type == 'c') {
      node->layout.type_c.data.counter = 0;
      node->layout.type_c.data.state = 0;
    }
    else if(node->type == 'd') {
      node->layout.type_d.data.counter = 0;
      node->layout.type_d.data.state = 0;
    }
    else if(node->type == 'e') {
      node->layout.type_e.data.counter = 0;
      node->layout.type_e.data.state = 0;
    }
}

int read_line(FILE *file, union interpretation *interp, intersection* nodes) {
  char curr_line[MAX_LINE_LENGTH], temp[5] = {0};

  if (!feof(file)){

    fgets(curr_line, MAX_LINE_LENGTH, file);

    /* Check if line is commented out */
    if (curr_line[0] == '#'){
      return -1;
    }

    /* Get the first word on the line. */
    sscanf(curr_line, " %s", temp);

    /* Is the line a node definition? */
    if (strcmp(temp, "node") == 0){
      interpret_node(curr_line, &interp->intersection);
      return 1;
    }

    /* Is the line a link definition? */
    else if (strcmp(temp, "link") == 0){
      interpret_link(curr_line, &interp->link, nodes);
      return 2;
    }

    /* it must be a comment */
    else
      return -1;

  }

  else
    return 0;
}
int scan_buffer(const char* ptr, int *pos, char* buffer){
  int res = sscanf(ptr += *pos, " %s%n", buffer, &pos);
  return res;
}

void interpret_link(const char *str, link *link, intersection* nodes) {
  char buffer[50], dest = 0, prim, to_prim, from_prim;
  const char* ptr = str;
  int pos = 0, id, len, node, dir, to_dir, from_dir, from_node = -1, to_node = -1, index;
  double r_chance = 0, l_chance = 0, spawn_chance = 0;
  intersection* tmp_node;

  sscanf(str, " link %d: %d%n", &id, &len, &pos);
  printf("link %d: %d ", id, len);

  while(sscanf(ptr += pos, " %s%n", buffer, &pos) != EOF){

    /* Stop interpretation if it is a comment */
    if (buffer[0] == '#')
      break;

    if (buffer[0] == ',')
      continue;

    //printf("%c:", buffer[0]);

    if (isdigit(buffer[0])){
      if (dest == 0){
        sscanf(ptr, " %lf, %lf%n", &r_chance, &l_chance, &pos);
        printf("%lf, %lf ", r_chance, l_chance);
      }
      else{
        sscanf(ptr, " %lf%n", &spawn_chance, &pos);
        printf("%lf ", spawn_chance);
      }
   }

    else {
      sscanf(ptr, " %c: %d[%c%d]%n", &dest, &node, &prim, &dir, &pos);
      printf("%c: %d[%c%d]", dest, node, prim, dir);

      if (dest == 't'){
        to_node = node;
        to_dir = dir;
        to_prim = prim;
      }
      else if (dest == 'f'){
        from_node = node;
        from_dir = dir;
        from_prim = prim;
      }

    }

  }

    link->id = id;
    link->len = len;
    link->left_chance = l_chance;
    link->right_chance = r_chance;
    link->spawn_chance = spawn_chance;

    /* initialization */
    link->time_step = 0;
    link->road=(int*)calloc(len,sizeof(int));

    if (to_node > -1){
      tmp_node = nodes + to_node;
      link->intersection = tmp_node;
      index = get_link_index(link_name(to_prim, to_dir, 1), tmp_node->type);
      get_links(tmp_node)[index] = link;

    }

    if(from_node > -1){
      tmp_node = nodes + from_node;
      index = get_link_index(link_name(from_prim, from_dir, 0), tmp_node->type);
      get_links(tmp_node)[index] = link;
    }


    printf("\n");

}

/*

void build_link(link *link, int id, int len, double left_chance, double right_chance, intersection *to, char prim, int dir, intersection *from) {
  link->id    = id;
  link->len   = len;
  link->road  = (int*)calloc(len, sizeof(int));
  link->time_step    = 0;
  link->intersection = to;
  link->left_chance  = 0;
  link->right_chance = 0;

  if(to != NULL)
    get_link(link_name(to, prim, dir), to) = link;
}

void count_nodes_and_links(const char* filepath, int* nodes, int* links){
  char curr_line[MAX_LINE_LENGTH], temp[5];
  FILE* file = fopen(filepath, "r");
  while (!feof(file)){

  fgets(curr_line, MAX_LINE_LENGTH, file);
  if (curr_line[0] == '#')
    continue;

  fscanf(file, " %s", temp);
  }

  fclose(file);
}
*/

void interpret_file(FILE *file, intersection *nodes, link *links) {
  union interpretation interp;
  int res;

  intersection *nptr = nodes;
  link *lptr = links;

  do{
    res = read_line(file, &interp, nodes);

    if (res == 1)
      *nptr++ = interp.intersection;


    else if (res == 2)
      *lptr++ = interp.link;
  }
  while (res);

}

void setup_intersection(intersection* intersection, char type){

}