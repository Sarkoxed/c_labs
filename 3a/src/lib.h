#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keyspace1.h"
#include "keyspace2.h"

#ifndef MY_TABLE_H
#define MY_TABLE_H

typedef struct Table{
		key_s1 	*ks1;
		key_s2 	**ks2;

		int msize2;
		int csize2;
}table;


int getInt(int *a);

int getFloat(float *x);

char * getStr(int *);

int check_cal(char *t);


table init_table(int);

void options();

int add_el(unsigned key1, char *key2, char *info, table *man, float a, float b);


int search_item(unsigned key1, char *key2, table man, Item *x);

int search_uns(table man, unsigned key1, Item *x);

key_s2 * search_str(table man,char *key2, int rel);


void del_el(unsigned key1, char *key2, table *man);

void del_uns(table *man, unsigned key1);

void del_str(table *man,char *key2, int rel);


void show_table(table man, int n);

void free_table(table *man);

#endif
