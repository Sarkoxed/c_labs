#include "tools.h"

void print_suc(char *m, int a){
  printf(green);
  printf("%s ", m);
  if(a+1){
    printf("%d", a);
  }
  printf(white);
}

void print_war(char *m, int a){
  printf(blue);
  printf("%s", m);
  if(a+1){
    printf("%d", a);
  }
  printf(white);
}

void print_err(char *m,int a){
  printf(red);
  printf("%s", m);
  if(a+1){
    printf("%d", a);
  }
  printf(white);
}

void print_und(char *m, int a){
  printf(un);
  printf("%s", m);
  if(a+1){
    printf("%d", a);
  }
  printf(white);
}

void print_fat(char *m){
  printf(fat);
  printf("%s",m);
  printf(white);
}
