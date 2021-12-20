#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

int check_cal(char *t){
  if(t == NULL){
    printf("You need more ram for such a string, repeat please with less amount of characters\n");
    scanf("%*[^\n]");
    scanf("%*c");
    return 0;
  }
  return 1;
}


void initialize(list *le_string, char *s){
  for(int i = 1; i < strlen(s); i++){
    le_string = add(le_string, s[i]);
    }
}


list * new_list(list *le_string, char b, char e){
  int k = 1;
  list *orig, *beg_end = NULL;

  while((le_string != NULL)&&(k == 1)){              //first appearence of beg
    if (le_string->c != b){
      le_string = del_root(le_string);
    }
    else{
      k--;
    }
  }

  orig = le_string;                                //remembering origin

  if (le_string == NULL){
    return le_string;
  }

  while(le_string != NULL){
    if((le_string->c == b)&&(!k)){

      if (le_string == orig){
         le_string = del_root(le_string);
         orig = le_string;

         beg_end = le_string;                       //first appearence og beg or not

      }else{
         le_string = del(le_string, orig);
      }

      k = 1;

    }

    else if((le_string->c == e)&&(k)){
      le_string = del(le_string, orig);
      le_string = add(le_string, ' ');

      beg_end = le_string;                      //first appearence of new beg

      k = 0;
    }

    else if(k == 0){
      le_string = del(le_string, orig);
    }

    if(le_string != NULL){
      le_string = le_string->next;
    }

  }

  if(k == 1){                            //if beg appeared but no end came
    le_string = beg_end;

    if(beg_end == orig){                //string of type "begbeg..."" with no end

      while(le_string != NULL){
        le_string = del_root(le_string);
      }
      return le_string;
    }


    else{
      while(le_string != NULL){
        le_string = del(le_string, orig);
        le_string = le_string->next;
      }
   }
 }

  le_string = orig;
  return le_string;
}


list * init(char x){
  list *a;
  a = malloc(sizeof(list));
  a->c = x;
  a->next = NULL;
  return a;
}


list * add(list *a, char c){
  list *tmp, *p;
  tmp = malloc(sizeof(list));
  p = a->next;
  a->next = tmp;
  tmp->c = c;
  tmp->next = p;
  return tmp;
}


list * del(list *a, list *orig){
  list *tmp;
  tmp = orig;

  while(tmp->next != a){
    tmp = tmp->next;
  }

  tmp->next = a->next;
  free(a);
  return tmp;

}


list * del_root(list *orig){
   list *tmp;
   tmp = orig->next;
   free(orig);
   return tmp;
}


void print_list(list *a){
  list *p;
  p = a;
  while(p != NULL){
    printf("%c", p->c);
    p = p->next;
  }
}


void free_list(list *orig){
  list *p;
  while(orig != NULL){
    p = orig->next;
    free(orig);
    orig = p;
  }
}
