#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>


#include "tools.h"

#ifndef MAIN_LIBRARY
#define MAIN_LIBRARY

/*
#define STEP 65521
#define H_SIZE 262139
#define SKIP 21876
*/
/*
#define STEP 17364
#define H_SIZE 65521
#define SKIP 9011
*/
#define INF 20000.0


#define STEP 17
#define H_SIZE 653
#define SKIP 9


typedef struct vertex{
    float x, y;
    char *name;

    float dist;
    int pred;

    int disc;

    struct list *next;
}vertex;

typedef struct hashtable{
  struct vertex *space;
  int size;
  int full;
}htab;

typedef struct list{
    int me;
    float w;
    float flow;
    int res_n;
    struct list *next;
}list;


typedef struct graph{
    struct hashtable vers;
    int count;
}grph;

typedef struct queue{
  int *pos,rear, frnt;
}que;

int hash(char *key);
htab h_init();
int h_find(char *key, htab t);

que init_que(int n);
void insert_q(que *q, int x);
int isempty(que q);
int pop_q(que *q);

void init_graph(grph *g, FILE *fp);
void add_ver(grph *g, char *name, float x, float y, int *suc);
void add_edg(grph *g, char *first, char *second, float w, int *suc);
void del_ver(grph *g, char *name, int *suc);
void del_edg(grph *g, char *first, char *second, int *suc);
void bfs(grph *g, char *first , int *suc);
vertex ** bfs_path(grph g, char *first ,char *second, int *suc);
vertex ** min_path(grph g, char *first,char *  second, int *suc, int *len, int c);
grph cpy_graph(grph g);
float min_cf(grph g, vertex **path);
void add_or_rewrite_edg(grph *g,float cf, vertex **path);
grph res_net(grph g, char *first, char *second, float *, int *);
void show_graph(grph g);
void free_graph(grph g);
void save(grph g);
void save_1(grph g, int o, vertex **, int);
grph make(FILE *fp,int  n);


char * get_by_coords(grph g,float x,float y, int *);
#endif
