#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void new_strings(char *a, char *b, char *c, int len);


void new_strings(char *a, char *b, char *c, int len){
  char prev, temp;
  int k = 0, l = 0, r = 1, t1 = 0, t2 = 0;

  // k - first non gap, l - gap dublication
  // r - dublications, t_i - timers for strings

  while(c[k] == ' '){
      k++;
  }

  prev = ' ';

  for(int i = k; i < len; i++){
    temp = c[i];
    if (temp != ' '){
       l = 0;

       if(temp == prev){
           r = 0;
           b[t2++] = temp;
       }

       else{

         if (!r){
           b[t2++] = ' ';
           r++;
         }

         a[t1++] = temp;
         prev = temp;
       }
    }

    else{
      if(!l){
        prev = ' ';
        a[t1++] = ' ';
        l++;
      }
    }
  }

}


int main(){
  char *temp, *new_string, *repeated;
  int n, num = 2;

  printf("Your 1 string: ");

  while(scanf("%m[^\n]", &temp) != EOF){
    n = strlen(temp);
    // дописать про память
    new_string = calloc(n,sizeof(char));
    repeated = calloc(n,sizeof(char));

    new_strings(new_string, repeated, temp, n);

    if(strlen(new_string) > 0){
      printf("\nNew string, without dublication: %s", new_string);
    }
    else{
      printf("\nNo words Found in original string");
    }
    if(strlen(repeated) > 0){
    printf("\nAll Dublications:                %s\n", repeated);    }
    else{
      printf("\nNo Dublications Found");
    }

    printf("\n#################################################\n");
    free(temp);
    free(repeated);
    free(new_string);
    printf("Your %d string: ", num++);
    scanf("%*[\n]");

  }
  free(temp);

  printf("\n\n\n-------------------Input ended.-------------------\n");

return 0;
}
