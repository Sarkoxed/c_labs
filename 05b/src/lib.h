#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list{
    char c;
    struct list *next;
}list;

list * init(char x);
list * add(list *a, char n);
list * del(list *a, list *orig);
list * del_root(list *orig);
void print_list(list *a);
void initialize(list *le_string, char *s);
list * new_list(list *le_string, char b, char e);
void free_list(list *orig);
int check_cal(char *t);
