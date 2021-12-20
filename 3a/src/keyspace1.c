#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keyspace1.h"

key_s1 * init_1(unsigned x, Item *y){
    key_s1 *tmp;
    tmp = (key_s1 *)calloc(1, sizeof(key_s1));
    tmp->key = x;
    tmp->info = y;
    tmp->next = NULL;
    return tmp;
} // probably not necessary

key_s1 * del_1(key_s1 *orig, unsigned key){
    key_s1 *tmp, *p;

    tmp = get_ks_1(orig, key);
    if (!tmp){
      printf("THERE IS NO SUCH A KEY\n");
    }
    else if (tmp == orig && tmp->key == key){
      orig = orig->next;
      free(tmp);
    }
    else {
      p = tmp->next;
      tmp->next = p->next;
      free(p);
    }
    return orig;
} // probably not necessary


key_s1 * next_need_1(key_s1 *el,unsigned key){
  key_s1 *tmp = el;

  if(tmp && tmp->next && tmp->next->key == key){
    tmp = tmp->next;
  }

  return tmp;
}

key_s1 * add_1(key_s1 *orig, char *info , unsigned key, float a, float b){
  key_s1 *tmp;

  if(!get_ks_1(orig, key)){
    tmp = (key_s1 *)calloc(1, sizeof(key_s1));
    tmp->next = orig;

    tmp->info = (Item *)calloc(1, sizeof(Item));

    tmp->info->key1 = key;
    tmp->info->info_i = info;
    tmp->info->p1 = tmp;
    tmp->info->dub1 = a;
    tmp->info->dub2 = b;

    tmp->key = key;
  }
  else{
    printf("THERE IS SUCH A KEY ALREADY!\n");
    tmp = orig;
  }

  return tmp;
}

key_s1 * get_ks_1(key_s1 *orig, unsigned key){
    key_s1 *tmp;
    int c = 0;
    tmp = orig;

    if(!tmp){
      return NULL;
    }

    if(tmp && tmp->key == key){
      return tmp;
    }

    while(tmp->next && !c){
      if((tmp->next)->key == key){
        ++c;
      }
      else{
        tmp = tmp->next;
      }
    }

    if(c == 0){
      return NULL;
    }
    else{
      return tmp;
    }

} // returns previous address el


key_s1 * search_range(key_s1 * orig, int beg, int end){
  key_s1 *tmp, *new, *p;
  int c = 0;
  p = NULL;
  for(int i = beg; i <= end; i++){
    tmp = next_need_1(get_ks_1(orig, (unsigned int)i),(unsigned int)i);
    if(!tmp){
      printf("NO KEY %d FOUND\n", i);
    }

    else if (!c){
      new = init_1((unsigned int)i, tmp->info);
      p = new;
      ++c;
    }
    else{
      new->next = (key_s1 *)calloc(1, sizeof(key_s1));
      new = new->next;
      new->next = NULL;
      new->key = (unsigned int)i;
      new->info = tmp->info;
    }
  }
 return p;
 }

void free_keyspace_1(key_s1 *orig){
      key_s1 *tmp;
      while(orig){
        tmp = orig;
        orig = orig->next;
        free(tmp->info->key2);
        free(tmp->info->info_i);
        free(tmp->info);
        free(tmp);
      }
  }

void print_keyspace_1(key_s1 *orig){
      while(orig){
        printf("         (key: %d, value: {%s, %f, %f})\n", orig->key, orig->info->info_i,orig->info->dub1, orig->info->dub2);
        orig = orig->next;
      }
  }
