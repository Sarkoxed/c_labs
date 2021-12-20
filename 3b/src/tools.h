#include <stdio.h>

#ifndef TOOLS
#define TOOLS

#define green  "\x1b[92m"
#define blue   "\x1b[96m"
#define red    "\x1b[91m"
#define white  "\x1b[0m"
#define un     "\x1b[21m"
#define fat    "\x1b[1m"

void print_suc(char *, int);
void print_war(char *, int);
void print_err(char *, int);
void print_und(char *, int);
void print_fat(char *);
#endif
