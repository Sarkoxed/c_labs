#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

int main(){
  list *le_string = NULL, *orig;
  char *temp;
  char beg, end;
  int num = 2;

  printf("Begining symbol is: ");   //если а = а то аba bnbna -> b, можно исправить двойным циклом
  beg = getchar();
  scanf("%*c");
  printf("Begining symbol is: ");
  end = getchar();
  scanf("%*c");

  printf("\nYour 1 string: ");

  while(scanf("%m[^\n]", &temp) != EOF){
    if (temp == NULL){
      printf("No words found");
    }

    else{
      le_string = init(temp[0]);
      orig = le_string;
      initialize(le_string, temp);
      le_string = new_list(le_string, beg, end);

      if(le_string == NULL){
        printf("There're no pairs of such a symbols in this string\n ");
      }
      else{
        printf("New string is: ");
        print_list(le_string);
        free_list(le_string);
      }
   }

    printf("\n#################################################\n");

    printf("Your %d string: ", num++);
    scanf("%*c");

    free(temp);

  }
  free(temp);

  printf("\n\n\n-------------------Input ended.-------------------\n");

return 0;
}

/* Test cases
for a, b

aaaaaaaaaaaaaa -> none
bbbbbbbb -> none
ajkub -> jku
amkmkb aaaaaa -> mkmk
anb amb alb aaa -> n m l
*/
