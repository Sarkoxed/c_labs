#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

typedef struct Item{
  int count;
}Item;

typedef struct node{
  int key;

  struct node *left;
  struct node *right;

  struct node *par;

  struct Item *info;

  int amo;
}node;

Item * init_item();
node * init(int key, Item *x);
node * add(node *orig, int key, Item *x, int *suc);

node * get(node *orig, int key, int *suc);

int tree_save(node *orig, FILE *fp, int cou);

void save(node *orig);

void free_tree(node *orig);

int depth(node *orig);
