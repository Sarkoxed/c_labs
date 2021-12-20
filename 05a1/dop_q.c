#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include <stdio.h>

int main(){
  char *temp, *temp1, *new_string, *repeated;
  int n, num = 1;

  printf("Your %d string: ", num++);

  while(scanf("%m[^\n]", &temp) != EOF){

    if(!check_cal(temp)){
      printf("Your %d string: ", num);
      continue;
    }
    n = strlen(temp);

    temp1 = calloc(strlen(temp)+2, sizeof(char));

    if (!check_cal(temp1)){
      printf("Your %d string: ", num);
      continue;
    }

    strcat(temp1, temp);
    temp1[strlen(temp)] = ' ';                     //appending gap to temp
    free(temp);

    new_string = calloc(n + 1,sizeof(char));

    if (!check_cal(new_string)){
      printf("Your %d string: ", num);
      continue;
    }
    repeated = calloc(n + 1,sizeof(char));

    if (!check_cal(repeated)){
      printf("Your %d string: ", num);
      continue;
    }


    new_strings(new_string, repeated, temp1);

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
    free(temp1);
    free(repeated);
    free(new_string);
    printf("Your %d string: ", num++);
    scanf("%*[\n]");

  }
  free(temp);

  printf("\n\n\n-------------------Input ended.-------------------\n");

return 0;
}
