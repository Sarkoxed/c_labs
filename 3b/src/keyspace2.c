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

void free_vec(key_s2 ** vec, int size){
  for(int i = 0; i < size; i++){
    free_keyspace_2(vec[i]);
  }
  if(vec){
    free(vec);
  }
}

key_s2 * init_2(int ktab, int klen,int reltab, Item *x){
  key_s2 *p1 = (key_s2 *)calloc(1, sizeof(Item));
  p1->key_tab = ktab;
  p1->key_len = klen;
  p1->rel_tab = reltab;
  p1->info = x;
  return p1;
}

key_s2 ** add(char *key, int size, key_s2 **vec, int *sizeup, Item *x){
  int ind;

  ind = hash(key, size);

  if(!vec[ind]){
    print_suc("ADDING NEW ROOT", -1);
    printf("\n");
    *sizeup += 1;
  }
  vec[ind] = add_2(vec[ind], x, key);

  return vec;
}

key_s2 * add_2(key_s2 *orig, Item *info, char *key){
  key_s2 *p, *p2;
  char *k3;
  int len;

  p = (key_s2 *)calloc(1, sizeof(key_s2));
  p->next = orig;

  p->info = info;
  p->key_tab = info->key2_tab;
  p->key_len = info->key2_len;
  p->rel_tab = info->rel_tab;
  p->info->p2 = p;

  p2 = orig;
  int c = 0;
  while(p2 && !c){
    fseek(p2->info->fp, p2->key_len, 0);
    fread(&len, sizeof(int),1, p2->info->fp);
    k3 = (char *)calloc(len+1, sizeof(char));
    fread(k3, sizeof(char), len, p2->info->fp);
    if(strcmp(k3, key) == 0){
      c++;
    }
    free(k3);
    p2 = p2->next;
  }
  if(c){
    shift_ind(p, key);
  }

  return p;
}


key_s2 * get_release(key_s2 *orig ,char *key , int release){
  key_s2 *tmp;
  int c = 0, len, rel;
  char *k2;
  tmp = orig;
  fseek(orig->info->fp, orig->key_len, 0);
  fread(&len, sizeof(int), 1, orig->info->fp);
  k2 = (char *)calloc(len+1, sizeof(char));
  fread(k2, sizeof(char), len, orig->info->fp);
  fseek(orig->info->fp, orig->rel_tab, 0);             /////////////////////////////
  fread(&rel, sizeof(int), 1, orig->info->fp);

  if(orig && strcmp(k2, key) == 0 && rel == release){
    free(k2);
    return orig;
  }
  free(k2);
  while(tmp->next && !c){
    fseek(tmp->next->info->fp, tmp->next->key_len, 0);
    fread(&len, sizeof(int), 1, tmp->info->fp);
    k2 = (char *)calloc(len+1, sizeof(char));
    fread(k2, sizeof(char), len, tmp->next->info->fp);
    fseek(tmp->next->info->fp, tmp->next->rel_tab, 0);
    fread(&rel, sizeof(int), 1, tmp->next->info->fp);

    if(strcmp(k2, key) == 0 && rel == release){
      ++c;
    }
    else{
      tmp = tmp->next;
    }
    free(k2);
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
  char *k2;
  int c = 0, len;
  p = NULL;
  tmp = orig;
  while(tmp){
    fseek(tmp->info->fp, tmp->key_len, 0);
    fread(&len, sizeof(int), 1, orig->info->fp);
    k2 = (char *)calloc(len+1, sizeof(char));
    fread(k2, sizeof(char), len, orig->info->fp);

    if(strcmp(k2, key) == 0 && !c){
      ++c;
      new = init_2(tmp->key_tab, tmp->key_len, tmp->rel_tab, tmp->info);
      p = new;
    }
    else if (strcmp(k2, key) == 0){
      new->next = (key_s2 *)calloc(1, sizeof(key_s2));
      new = new->next;
      new->next = NULL;
      new->key_tab = tmp->key_tab;
      new->rel_tab = tmp->rel_tab;
      new->key_len = tmp->key_len;
      new->info = tmp->info; // тут мб ошибка
      }
    free(k2);
    tmp = tmp->next;

  }
  return p;
}


key_s2 * next_need_2(key_s2 *el, char *key, int rel){
  key_s2 *tmp = el;
  int r, len;
  char *k2;

  if(tmp && tmp->next){
    fseek(el->next->info->fp, el->next->info->key2_len, 0);
    fread(&len, sizeof(int), 1, el->next->info->fp);
    k2 = (char *)calloc(len+1, sizeof(char));
    fread(k2, sizeof(char), len, el->next->info->fp);
    fseek(el->next->info->fp, el->next->rel_tab, 0);
    fread(&r, sizeof(int), 1, el->next->info->fp);

    if(strcmp(k2, key) == 0 && r == rel){
      tmp = tmp->next;
    }
  free(k2);
  }
  return tmp;
}

void shift_ind(key_s2 *orig, char *key){
  int n = 1, len;
  char *k2;

  while(orig){
    fseek(orig->info->fp, orig->info->key2_len, 0);
    fread(&len, sizeof(int), 1, orig->info->fp);
    k2 = (char *)calloc(len+1, sizeof(char));
    fread(k2, sizeof(char), len, orig->info->fp);

    if(strcmp(k2, key) == 0){
      fseek(orig->info->fp, orig->rel_tab, 0);
      fwrite(&n, sizeof(int), 1, orig->info->fp);
      n++;
    }
    free(k2);
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
  int rel;
  float f1,f2;
  char *k2, *info;
  int lenk, leni;
    while(orig){
      fseek(orig->info->fp, orig->key_len, 0);
      fread(&lenk, sizeof(int), 1, orig->info->fp);
      k2 = (char *)calloc(lenk+1, sizeof(char));
      fread(k2, sizeof(char), lenk, orig->info->fp);
      fseek(orig->info->fp, orig->info->info_len, 0);
      fread(&leni, sizeof(int), 1, orig->info->fp);
      info = (char *)calloc(leni+1, sizeof(char));
      fread(info, sizeof(char), leni, orig->info->fp);
      fread(&f1, sizeof(float), 1, orig->info->fp);
      fread(&f2, sizeof(float), 1, orig->info->fp);
      fread(&rel, sizeof(int), 1, orig->info->fp);

      printf("         (key: \'%s\', r: %d, value: {%s, %f, %f}) \n", k2,rel, info,f1,f2);
      orig = orig->next;
      free(k2);
      free(info);
    }
}


void del_release(key_s2 *orig, char *key, int release){
   key_s2 *tmp, *p;
   p = get_release(orig, key, release);
   tmp = next_need_2(p, key, release);

   if(!tmp){
     print_err("NO SUNCH A KEY FOUND", -1);
     printf("\n");
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
  int c = 0, lenk;
  char *k2;

  tmp = orig;
  fseek(tmp->info->fp, tmp->key_len, 0);
  fread(&lenk, sizeof(int), 1, tmp->info->fp);
  k2 = (char *)calloc(lenk+1, sizeof(char));
  fread(k2, sizeof(char), lenk, tmp->info->fp);
  while(tmp && strcmp(k2, key) == 0){
    p = tmp;
    tmp = tmp->next;
    free(k2);
    fseek(tmp->info->fp, tmp->key_len, 0);
    fread(&lenk, sizeof(int), 1, tmp->info->fp);
    k2 = (char *)calloc(lenk+1, sizeof(char));
    fread(k2, sizeof(char), lenk, tmp->info->fp);
    free(p);
    ++c;
  }
  free(k2);

  orig = tmp;

  while(tmp->next){
    fseek(tmp->next->info->fp, tmp->next->key_len, 0);
    fread(&lenk, sizeof(int), 1, tmp->next->info->fp);
    k2 = (char *)calloc(lenk+1, sizeof(char));
    fread(k2, sizeof(char), lenk, tmp->next->info->fp);

    if(strcmp(k2, key) == 0){
      p = tmp->next;
      tmp->next = p->next;
      free(p);
    }
    free(k2);
    tmp = tmp->next;
  }
  if(c){
    print_suc("SUCCESSFULLY DELETED ALL RELEASES OF KEY ", -1);
    print_suc(key, -1);
    printf("\n");
  }
  else{
    print_war("NO RELEASES FOUND", -1);
    printf("\n");
  }

  return orig;
}
