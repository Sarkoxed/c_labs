#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#ifndef TOOLS
#define TOOLS

#define green  "\x1b[92m"
#define blue   "\x1b[96m"
#define red    "\x1b[91m"
#define white  "\x1b[0m"
#define un     "\x1b[21m"
#define fat    "\x1b[1m"
#define pink   "\x1b[95m"

void print_suc(char *);
void print_war(char *);
void print_err(char *);
void print_und(char *);
void print_fat(char *);

int check_cal(char *t);
int getInt(int *b);
int getFloat(float *x);
char * getStr(int *flag);
int getFile(char *fname, FILE **ff, int);
void timer(float);

void free_all(char ***tmp, int);
#endif
