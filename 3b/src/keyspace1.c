#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keyspace1.h"

key_s1 * del_root_1(key_s1 *orig){
  key_s1 *p;
  p = orig;
  orig = orig->next;
  free(p);
  return orig;
}

key_s1 * del_1(key_s1 *orig, unsigned key){
    key_s1 *tmp, *p1;

    tmp = get_ks_1(orig, key);
    p1 = next_need_1(tmp, key);
    if (!tmp){
      print_war("THERE IS NO SUCH A KEY", -1);
      printf("\n");
      return orig;
    }
    if(p1 == orig){
      orig = del_root_1(p1);
    }
    else{
      tmp->next = p1->next;
      free(p1);
    }
    return orig;
}

key_s1 * next_need_1(key_s1 *el,unsigned key){
  key_s1 *tmp = el;
  unsigned next_key;

  if(tmp && tmp->next){
    fseek(tmp->info->fp, tmp->next->key_tab, 0);
    fread(&next_key, sizeof(unsigned), 1, tmp->info->fp);
    if(next_key == key){
      tmp = tmp->next;
    }
  }

  return tmp;
}

key_s1 * add_1(key_s1 *orig, unsigned key, Item *x){
  key_s1 *tmp;

  if(!get_ks_1(orig, key)){
    tmp = (key_s1 *)calloc(1, sizeof(key_s1));
    tmp->next = orig;
    tmp->info = x;
    tmp->key_tab = x->key1_tab;
    tmp->info->p1 = tmp;
  }
  else{
    print_war("THERE IS SUCH A KEY ALREADY!", -1);
    printf("\n");
    tmp = orig;
  }

  return tmp;
}

key_s1 * get_ks_1(key_s1 *orig, unsigned key){
    key_s1 *tmp;
    int c = 0;
    unsigned k1;
    tmp = orig;

    if(!tmp){
      return NULL;
    }
    fseek(orig->info->fp, orig->key_tab, 0);
    fread(&k1, sizeof(int), 1, orig->info->fp);
    if(k1 == key){
      return tmp;
    }

    while(tmp->next && !c){
      fseek(tmp->next->info->fp, tmp->next->key_tab, 0);
      fread(&k1, sizeof(int), 1, tmp->next->info->fp);
      if(k1 == key){
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
      }
      else if (!c){
        new = (key_s1 *)calloc(1, sizeof(key_s1));
        new->info = tmp->info;
        new->key_tab = new->info->key1_tab;
        new->next = NULL;
        p = new;
        ++c;
      }
      else{
        new->next = (key_s1 *)calloc(1, sizeof(key_s1));
        new = new->next;
        new->next = NULL;
        new->key_tab = tmp->info->key1_tab;
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
        free(tmp->info);
        free(tmp);
      }
  }

void print_keyspace_1(key_s1 *orig){
  int lenin;
  unsigned key;
  float f1, f2;
  char *in;
      while(orig){
        fseek(orig->info->fp, orig->info->key1_tab, 0);
        fread(&key, sizeof(unsigned), 1, orig->info->fp);
        fread(&lenin, sizeof(int), 1, orig->info->fp);
        in = (char *)calloc(lenin+1, sizeof(char));
        fread(in, sizeof(char), lenin, orig->info->fp);
        fread(&f1, sizeof(float), 1, orig->info->fp);
        fread(&f2, sizeof(float), 1, orig->info->fp);

        printf("         (key: %d, value: {%s, %f, %f})\n", key, in, f1,f2);
        orig = orig->next;
        free(in);
      }
  }
