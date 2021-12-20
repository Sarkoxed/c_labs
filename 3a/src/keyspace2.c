#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keyspace2.h"

int hash(char *el, int col){
    int n = strlen(el), len;
    len = n;

    for(int i = 0; i < n; i++){
      len += (int)el[i];
    }

    return (len % col);
}

key_s2 ** init_vector(int size){
  key_s2 **tmp;
  tmp = (key_s2 **)calloc(size, sizeof(key_s2 *));
  return tmp;
}

key_s2 ** add(char *key, int size, key_s2 **vec, int *sizeup, Item *x){
  int ind;

  ind = hash(key, size);

  if(!vec[ind]){
    vec[ind] = init_2(key, x);
    printf("ADDING NEW ROOT\n");
    *sizeup += 1;
  }
  else{
    vec[ind] = add_2(vec[ind], x, key);
  }

  return vec;
}

void free_vec(key_s2 ** vec, int size){
  for(int i = 0; i < size; i++){
    free_keyspace_2(vec[i]);
  }
  if(vec){
    free(vec);
  }
}


key_s2 * init_2(char *key, Item *info){
  key_s2 *p;

  p = (key_s2 *)calloc(1, sizeof(key_s2));
  p->key = key;
  p->next = NULL;

  p->info = info;
  p->info->p2 = p;
  p->info->key2 = key;

  p->release = 1;
  return p;
}

key_s2 * add_2(key_s2 *orig, Item *info, char *key){
  key_s2 *p;

  p = (key_s2 *)calloc(1, sizeof(key_s2));
  p->next = orig;
  p->key = key;
  p->release = 1;

  p->info = info;
  p->info->p2 = p;
  p->info->key2 = key;

  shift_ind(p, key);

  return p;
}


key_s2 * get_release(key_s2 *orig ,char *key , int release){
  key_s2 *tmp;
  int c = 0;
  tmp = orig;

  if(orig && strcmp(orig->key, key) == 0 && orig->release == release){
    return orig;
  }

  while(tmp->next && !c){
    if(strcmp((tmp->next)->key, key) == 0 && (tmp->next)->release == release){
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
}

key_s2 * get_all(key_s2 *orig, char *key){
  key_s2 *tmp, *p, *new;
  int c = 0;
  p = NULL;
  tmp = orig;
  while(tmp){
    if(strcmp(tmp->key, key) == 0 && !c){
      ++c;

      new = init_2(tmp->key, tmp->info);
      new->info->p2 = tmp;                            // THIS IS A RETARDED ACTION
      p = new;
    }
    else if (strcmp(tmp->key, key) == 0){
      new->next = (key_s2 *)calloc(1, sizeof(key_s2));
      new = new->next;
      new->next = NULL;
      new->key = tmp->key;
      new->release = tmp->release;
      new->info = tmp->info;
    }
    tmp = tmp->next;

  }
  return p;
}


key_s2 * next_need_2(key_s2 *el, char *key, int rel){
  key_s2 *tmp = el;

  if(tmp && tmp->next && strcmp(tmp->next->key, key) == 0 && el->release == rel){
    tmp = tmp->next;
  }

  return tmp;
}

void shift_ind(key_s2 *orig, char *key){
  int n = 1;
  while(orig){
    if(strcmp(orig->key, key) == 0){
      orig->release = n++;
    }
    orig = orig->next;
  }
}

void free_keyspace_2(key_s2 *orig){
    key_s2 *tmp;
    while(orig){
      tmp = orig;
      orig = orig->next;
      free(tmp);
    }

}

void print_keyspace_2(key_s2 *orig){
    while(orig){
      printf("         (key: \'%s\', r: %d, value: {%s, %f, %f}) \n", orig->key, orig->release, orig->info->info_i, orig->info->dub1, orig->info->dub2);
      orig = orig->next;
    }
}


void del_release(key_s2 *orig, char *key, int release){
   key_s2 *tmp, *p;
   p = get_release(orig, key, release);
   tmp = next_need_2(p, key, release);

   if(!tmp){
     printf("NO SUNCH A KEY FOUND\n");
     return;
   }
   if(tmp == orig){
     orig = orig->next;
     free(tmp);
   }
   else{
     p->next = tmp->next;
     free(tmp);
   }
   shift_ind(orig, key);
 }
// Do not use

key_s2 * del_all(key_s2 *orig, char *key){
  key_s2 *tmp, *p;
  int c = 0;
  tmp = orig;
  while(tmp && strcmp(tmp->key, key) == 0){
    p = tmp;
    tmp = tmp->next;
    free(p);
    ++c;
  }
  orig = tmp;

  while(tmp->next){
    if(strcmp((tmp->next)->key, key) == 0){
      p = tmp->next;
      tmp->next = p->next;
      free(p);
    }
  }
  if(c){
    printf("SUCCESSFULLY DELETED ALL RELEASES OF KEY \'%s\'\n", key);
  }
  else{
    printf("NO RELEASES FOUND\n");
  }

  return orig;
}
// Do not use
