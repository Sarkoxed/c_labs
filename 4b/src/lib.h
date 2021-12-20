#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "tools.h"

#ifndef MAIN_LIB
#define MAIN_LIB

typedef struct Item{
  char *string1;
  char *string2;

  struct Item *next;
}Item;

typedef struct node{
  unsigned key;

  struct node *left;
  struct node *right;

  struct node *par;

  struct Item *info;

  int kef, rs, ls;
  int N;

  int amo;
}node;

#define difference 100;

Item * init_item(char *,char *);
node * init(unsigned key, Item *x);

node * add_node(node *orig, unsigned key, Item *x, int *suc);
node * add(node *orig, unsigned key, Item *x, int *suc);

node * delete_node(node *orig, unsigned key, int *suc);
node * delete(node *orig, unsigned key, int *suc);

Item ** get(node *orig, unsigned key, int *suc, int *);
Item ** max(node *orig, int *, int*);
int el_count(node *orig, int c);
int depth(node *orig);
void tree_save(node *orig, FILE *fp);
void save(node *orig);
void free_tree(node *orig);
void free_tree_1(node *orig);
void show_tree(node *orig);
void free_list(Item *x);

node * left_rot(node *orig);
node * right_rot(node *orig);


node * init_new(node *orig);
void tree_save_1(node *orig, FILE *fp);
void save_1(node *orig);
node * add_node_1(node *orig, unsigned key, Item *x, int *suc);
#endif
