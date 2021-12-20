#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MY_LIST_TABLE_H
#define MY_LIST_TABLE_H

typedef struct Item{
		char *info_i;
		float dub1;
		float dub2;

		unsigned key1;
		char *key2;

		struct KeySpace1 *p1;
		struct KeySpace2 *p2;
}Item;

typedef struct KeySpace2{
		char *key;
		int release;
		struct Item *info;
		struct KeySpace2 *next;
}key_s2;


typedef struct KeySpace1{
		unsigned key;
		struct Item *info;
		struct KeySpace1 *next;
}key_s1;


key_s1 * init_1(unsigned x, Item *y);


key_s1 * del_root_1(key_s1 *orig);

key_s1 * del_1(key_s1 *orig, unsigned k);


key_s1 * next_need_1(key_s1 *el,unsigned key1);

key_s1 * add_1(key_s1 *orig,char *info,unsigned key1, float a, float b);

key_s1 * get_ks_1(key_s1 *orig, unsigned k);


void free_keyspace_1(key_s1 *orig);

void print_keyspace_1(key_s1 *orig);

key_s1 * search_range(key_s1 * orig, int beg, int end);

#endif
