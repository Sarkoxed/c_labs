#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include <stdio.h>

int check_cal(char *t){
  if(t == NULL){
    printf("You need more ram for such a string, repeat please with less amount of characters\n");
    free(t);
    scanf("%*[^\n]");
    scanf("%*c");
    return 0;
  }
  return 1;
}

void new_words(char *word, char *a,int *a_timer, char *b, int *b_timer){
  int len = strlen(word);
  char prev, cur;
  prev = ' ';

  for(int i = 0; i < len; i++){
    cur = word[i];

    if(cur != prev){
      a[*a_timer] = cur;
      *a_timer += 1;
    }
    else{
      if((cur != b[*b_timer - 1])&&(*b_timer != 0)){
        b[*b_timer] = ' ';
        *b_timer += 1;
      }
      b[*b_timer] = cur;
      *b_timer += 1;
    }
    prev = cur;
  }
}

void new_strings(char *a, char *b, char *temp){

  int gap_count = 0, a_timer = 0, b_timer = 0, temp_timer = -1, ch = ' ', n;
  char *p, *word;

  while(temp[gap_count] == ' '){
    gap_count++;
  }

  temp += gap_count;

  while(strlen(temp) > 0){

    p = strchr(temp, ch) + 1;

    n = p - temp;
    //printf("%d %d\n", n, strlen(temp) - strlen(p));

    word = calloc(n, sizeof(char));
    strncpy(word, temp, n - 1);

    temp_timer = b_timer;
    new_words(word, a, &a_timer, b, &b_timer);

    a[a_timer++] = ' ';

    if(temp_timer != b_timer){
      b[b_timer++]=' ';
    }

    temp = p;
    gap_count = 0;

    free(word);

    while(temp[gap_count] == ' '){
      gap_count++;
    }

    temp += gap_count;
  }

}
