#include <stdio.h>

#ifndef ITEM_STRUCTURE
#define ITEM_STRUCTURE

typedef struct Item{
	int info_tab;
	int info_len;

	int dub1_tab;
	int dub2_tab;

	int key1_tab;

	int key2_tab;
	int key2_len;

	int rel_tab;

	FILE *fp;
	FILE *fk;

	struct KeySpace1 *p1;
	struct KeySpace2 *p2;
}Item;

#endif

#ifndef KEYSPACE_1_STRUCTURE
#define KEYSPACE_1_STRUCTURE

typedef struct KeySpace1{
		int key_tab;
		struct Item *info;
		struct KeySpace1 *next;
}key_s1;
#endif

#ifndef KEYSPACE_2_STRUCTURE
#define KEYSPACE_2_STRUCTURE
typedef struct KeySpace2{
		int key_tab;
		int key_len;
		int rel_tab;

		struct Item *info;
		struct KeySpace2 *next;
}key_s2;
#endif
