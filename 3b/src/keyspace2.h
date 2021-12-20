#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tools.h"

#ifndef MY_HASH_TABLE_H
#define MY_HASH_TABLE_H

int hash(char *el, int col);

key_s2 ** init_vector(int size);

void free_vec(key_s2 ** vec, int size);


key_s2 ** add(char *key, int size, key_s2 **vec, int *l, Item *info);

key_s2 * add_2(key_s2 *orig, Item *info, char *k);

key_s2 * del_root_2(key_s2 *orig);

key_s2 * del_all(key_s2 *orig, char *key);

void del_release(key_s2 *orig, char *key, int rel);

key_s2 * next_need_2(key_s2 *el,char *key, int rel);

void shift_ind(key_s2 *orig,char *key);


key_s2 * get_release(key_s2 *orig,char *key,int release);

int get_latest_release(key_s2 *orig, char *key);

key_s2 * get_all(key_s2 *orig, char *key);

void free_keyspace_2(key_s2 *orig);

void print_keyspace_2(key_s2 *orig);

#endif
