#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "struct.h"

#ifndef MY_LIST_TABLE_H
#define MY_LIST_TABLE_H

key_s1 * init_1(unsigned x, Item *y);


key_s1 * del_root_1(key_s1 *orig);

key_s1 * del_1(key_s1 *orig, unsigned k);


key_s1 * next_need_1(key_s1 *el,unsigned key1);

key_s1 * add_1(key_s1 *orig ,unsigned key1, Item *);

key_s1 * get_ks_1(key_s1 *orig, unsigned k);


void free_keyspace_1(key_s1 *orig);

void print_keyspace_1(key_s1 *orig);

key_s1 * search_range(key_s1 * orig, int a, int b);

#endif
