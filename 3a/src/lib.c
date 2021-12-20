#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "keyspace1.h"
#include "keyspace2.h"

int check_cal(char *t){
  if(t == NULL){
    printf("You need more ram for such a string, repeat please with less amount of characters");
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
      printf("I NEED A NUMBER!!!\n");
      scanf("%*[^\n]");
    }
    else if(n < 0){
      printf("REACHED EOF\n");
      scanf("%*c");
      return 0;
    }
    else if(a < 0){
      printf("I NEED A NATURAL!\n");
      scanf("%*[^\n]");
      n = 0;
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
      printf("I NEED A NUMBER!!!\n");
      scanf("%*[^\n]");
    }
    else if(n < 0){
      printf("REACHED EOF\n");
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
      free(tmp);
      printf("\nREACHED EOF\n");
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


table init_table(int size){
  table temp;
  temp.msize2 = size;
  temp.csize2 = 0;
  temp.ks2 = init_vector(size);
  temp.ks1 = NULL;
  return temp;
}


int search_item(unsigned key1, char *key2, table man, Item *x){
  key_s1 *tmp1;

  tmp1 = next_need_1(get_ks_1(man.ks1, key1), key1);

  if(!tmp1){
    return 0;
  }

  if(strcmp((tmp1->info)->key2, key2) != 0){
    return -1;
  }
  *x = *(tmp1->info);
  return 1;
}

int search_uns(table man, unsigned key1, Item *x){
  key_s1 *tmp;

  if(!(man.ks1)){
    printf("YOU'VE GOT EMPTY TABLE\n");
    return 0;
  }

  tmp = next_need_1(get_ks_1(man.ks1, key1), key1);

  if(!tmp){
    return 0;
  }

  *x = *(tmp->info);
  return 1;
}

key_s2 * search_str(table man, char *key2, int rel){
  key_s2 *tmp;
  int ind = hash(key2, man.msize2);

  if(!(man.ks2[ind])){
    printf("YOU'VE GOT EMPTY BRANCH\n");
    return NULL;
  }

  if(rel == 0){
    tmp = get_all(man.ks2[ind], key2);
  }
  else{
    tmp = next_need_2(get_release(man.ks2[ind], key2, rel), key2, rel);
  }

  return tmp;
}


int add_el(unsigned key1,char *key2, char *info, table *man, float a, float b){
  int n = 0, ind = hash(key2, man->msize2);
  char *k2, *i1;

  if(man->ks1 && get_ks_1(man->ks1, key1)){
    return 0;                                                     // Found out that key already exists
  }

  k2 = (char *)calloc(strlen(key2)+1, sizeof(char));
  strcpy(k2, key2);
  i1 = (char *)calloc(strlen(info)+1, sizeof(char));
  strcpy(i1, info);

  man->ks1 = add_1(man->ks1, i1, key1, a, b);                        // Added new element at the beginning of the first keyspace

  man->ks2 = add(k2, man->msize2, man->ks2, &n, man->ks1->info);    // Added new element at the beginning of the second keyspace

  if(n){
    man->csize2 += 1;                                                // New branch were created
  }

  man->ks1->info->p2 = man->ks2[ind];                                 // Pointer to the key2

  return 1;
}

void del_el(unsigned key1, char *key2, table *man){
  key_s1 *tmp1;
  int ind = hash(key2, man->msize2);

  if(!(man->ks1 && man->ks2[ind])){
    printf("YOU'VE GOT EMPTY TABLE\n");
    return;
  }

  tmp1 = next_need_1(get_ks_1(man->ks1, key1), key1);

  if(!tmp1 || strcmp((tmp1->info)->key2, key2) != 0){
    printf("NOTHING TO DELETE\n");
  }
  else{
    del_uns(man, tmp1->key);
  }
}


void del_uns(table *man, unsigned key1){
  key_s1 *tmp1, *p1, *px1;
  key_s2 *tmp2, *p2, *px2;
  Item *x;
  char *key2;;
  int n = 1, ind;

  if(!(man->ks1)){
    printf("YOU'VE GOT EMPTY TABLE\n");
    return;
  }


  p1 = get_ks_1(man->ks1, key1);
  if(!p1){
    printf("NOTHING TO DELETE\n");
    return;
  }
  px1 = p1;
  p1 = next_need_1(p1, key1);

  key2 = p1->info->key2;
  ind = hash(p1->info->key2, man->msize2);


  tmp1 = man->ks1;
  tmp2 = man->ks2[ind];
  p2 = p1->info->p2;
  x = p1->info;

  if(p1 == tmp1){
    man->ks1 = p1->next;
    free(p1);
  }
  else{
    px1->next = p1->next;
    free(p1);
  }

  px2 = get_release(tmp2, key2, p2->release);

  if(p2 == tmp2){
    man->ks2[ind] = p2->next;
    free(p2);
  }
  else{
    px2->next = p2->next;
    free(p2);
  }

  free(x->info_i);
  free(x);                 // Freeing info in Item

  shift_ind(man->ks2[ind], key2);

  if(n == 1){            // Checks if there is no more els with this key
    free(key2);

    if(!man->ks2[ind]){
      man->csize2--;
    }
  }
  printf("SUCCESSFULLY DELETED ELEMENT\n");
}

void del_str(table *man,char *key2, int rel){
  key_s2 *tmp2, *p2;
  unsigned key1;
  int ind = hash(key2, man->msize2);

  if(!(man->ks2[ind])){
    printf("YOU'VE GOT EMPTY BRANCH\n");
    return;
  }

  if (rel == 0){
    tmp2 = get_all(man->ks2[ind], key2);

    if(!tmp2){
      printf("NO SUCH A KEY 2 FOUND");
    }
    while(tmp2){
      p2 = tmp2;
      tmp2 = tmp2->next;
      key1 = p2->info->key1;
      del_uns(man, key1);
      free(p2);
    }
  }
  else{
    tmp2 = next_need_2(get_release(man->ks2[ind], key2, rel), key2, rel);
    if(!tmp2){
      printf("NO SUCH A KEY 2 FOUND\n");
    }
    else{
      key1 = tmp2->info->key1;
      del_uns(man, key1);
    }
  }
}


void options(){
  printf("Type \'help\'          if you need my options\n");

  printf("Type \'add\'           if you need to insert an element in table\n");

  printf("Type \'get_one\'       if you want to get an element via single key\n");
  printf("Type \'get_uns_range\' if you want to get a ks1 table via range of uns keys\n");
  printf("Type \'search\'        if you want to get an element via pair of keys\n");

  printf("Type \'del_one\'       if you want to delete elements via single key\n");
  printf("Type \'delete\'          if you want to delete an element via pair of keys\n");

  printf("Type \'show\'          if you want to see your table\n");

  printf("Type \'exit\'          if you wanr to end this round\n");
}

void show_table(table man, int n){
  key_s1 *tmp;

  if(n == 1){
    printf("\n--------------------YOUR FIRST KEYSPACE--------------------\n");
    if(man.ks1){
      print_keyspace_1(man.ks1);
    }
    else{
      printf("                        EMPTY KEYSPACE");
    }
    printf("\n-----------------------------------------------------------\n");

    printf("\n--------------------YOUR SECOND KEYSPACE-------------------\n");
    for (int i=0; i < man.msize2; i++){
      printf("%d:\n", i+1);
      if(man.ks2[i]){
        print_keyspace_2(man.ks2[i]);
      }
      else{
        printf("                        EMPTY BRANCH\n");
      }
      printf("\n");
    }
    printf("-----------------------------------------------------------\n");
  }

  printf("\n------------------------YOUR TABLE-------------------------\n");

  tmp = man.ks1;
  printf("               CURRENT COUNT OF KS2 ELEMENTS: %d\n\n", man.csize2);

  while(tmp){
    printf("Ks1: %d Ks2: \'%s\' Value: {%s, %f, %f}\n", tmp->key, (tmp->info)->key2, (tmp->info)->info_i, (tmp->info)->dub1, (tmp->info)->dub2);
    tmp = tmp->next;
  }
  printf("\n-----------------------------------------------------------\n");
}

void free_table(table *man){
  free_keyspace_1(man->ks1);
  free_vec(man->ks2, man->msize2);
}
