#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "tools.h"

#ifndef MAIN_LIB
#define MAIN_LIB

typedef struct Item{
  char *string;
  float f1;
}Item;

typedef struct node{
  int key;

  struct node *left;
  struct node *right;

  struct node *par;

  struct node *prev;
  struct node *next;


  struct Item *info;

  int amo;
}node;

Item * init_item(char *string, float f1);
node * init(int key, Item *x);
node * add(node *orig, int key, Item *x, int *suc);
node * delete(node *orig, int key, int *suc);
node * get(node *orig, int key, int *suc);
node * get_next(node *orig, int key, int *suc);
int el_count(node *orig, int c);
int depth(node *orig);
void tree_save(node *orig, FILE *fp);
void save(node *orig);
void free_tree(node *orig);
void show_tree(node *orig, int, int);

node * init_new(node *orig);
void tree_save_1(node *orig, FILE *fp);
void save_1(node *orig);

#endif
