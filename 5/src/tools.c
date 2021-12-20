#include "tools.h"

int check_cal(char *t){
  if(t == NULL){
    fprintf(stderr, red "You need more ram for such a string, repeat please with less amount of characters");
    scanf("%*[^\n]");
    scanf("%*[\n]");
    return 0;
  }
  return 1;
}

int getInt(int *b){
  int n = 0, a;
  while(!n){
    n = scanf("%d", &a);
    if (n == 0){
      fprintf(stdout, blue "I NEED A NUMBER!!!\n" white);
      scanf("%*[^\n]");
    }
    else if(n < 0){
      fprintf(stderr, red "REACHED EOF\n" white);
      scanf("%*c");
      return 0;
    }
  }
  scanf("%*c");
  *b = a;
  return 1;
}

int getFloat(float *x){
  int n = 0;
  while(!n){
    n = scanf("%f", x);
    if (n == 0){
      fprintf(stdout, blue "I NEED A NUMBER!!!\n" white);
      scanf("%*[^\n]");
    }
    else if(n < 0){
      fprintf(stderr, red "REACHED EOF\n" white);
      scanf("%*c");
      return 0;
    }
  }
  scanf("%*c");
  return 1;
}

char * getStr(int *flag){
  char *tmp = (char *)calloc(1,1);
  char buf[129];
  int n = 1, len = 0;
  *tmp = '\0';


  while(n > 0){
    n = scanf("%128[^\n]", buf);

    if (n == 0){
      scanf("%*c");
      *flag = 0;
    }
    else if(n < 0){
      fprintf(stderr, red "REACHED EOF\n" white);
      free(tmp);
      tmp = NULL;
      *flag = -1;

    }
    else {
      len += strlen(buf);
      tmp = (char *)realloc(tmp, len + 1);
      strcat(tmp, buf);
    }


  }
 if(tmp != NULL){
   *flag = 1;
 }

 if (tmp && strlen(tmp) == 0){
   *flag = 0;
 }

 return tmp;
}

int getFile(char *fname, FILE **ff, int n){
  FILE *fp;
  if(n == 1){
    fp = fopen(fname, "w+t");
  }
  else if(n == 2){
    fp = fopen(fname, "r+b");
  }
  else{
    fp = fopen(fname, "w+b");
  }

  if(!fp){
    fprintf(stderr, red "ERROR: %d %s\n" white, errno, strerror(errno));
    return 0;
  }
  fprintf(stdout, green "SUCCESSFULLY OPENED FILE: %s\n" white, fname);
  *ff  = fp;
  return 1;
}

void free_all(char ***tmp, int n){
  for (int i = 0; i < n; i++){
    if(*tmp[i]){
      free(*tmp[i]);
      *tmp[i] = NULL;
    }
  }
}

void timer(float t){
  fprintf(stdout, fat "\n-------------------------------------------------------\n"white);
  fprintf(stdout, fat "Passed:" white green" %f\n" white, t);
  fprintf(stdout, fat "-------------------------------------------------------\n"white);


}
