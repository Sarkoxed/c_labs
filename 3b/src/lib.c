#include "lib.h"

int check_cal(char *t){
  if(t == NULL){
    print_err("You need more ram for such a string, repeat please with less amount of characters", -1);
    printf("\n");
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
      print_war("I NEED A NUMBER!!!", -1);
      printf("\n");
      scanf("%*[^\n]");
    }
    else if(a < 0){
      print_war("I NEED A NATURAL!", -1);
      printf("\n");
      scanf("%*[^\n]");
      n = 0;
    }
    else if(n < 0){
      scanf("%*c");
      return 0;
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
      print_war("I NEED A NUMBER!!!", -1);
      printf("\n");
      scanf("%*[^\n]");
    }
    else if(n < 0){
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

int getFile(char *fname, FILE **ff){
  FILE *fp = fopen(fname, "r+b");

  if(!fp){
    print_err("Error : ", errno);
    printf(" ");
    print_err(strerror(errno), -1);
    printf("\n");
    return 0;
  }
  print_suc("SUCCESSFULLY OPENED FILE: ", -1);
  print_suc(fname, -1);
  printf("\n");
  *ff  = fp;
  return 1;
}

int init_table(table *man){
  table temp = *man;

  FILE *fp = man->ff;
  FILE *fk;

  getFile(man->filestruct, &fk);
  man->fk = fk;

  int ind;
  key_s2 *p2;
  key_s1 *p1, *px1 = NULL;
  key_s2 **px2;

  fread(&temp.msize2, sizeof(int), 1, fk);
  fread(&temp.csize2, sizeof(int), 1, fk);
  fread(&temp.last, sizeof(int),1 ,fk);

  px2 = (key_s2 **)calloc(temp.msize2, sizeof(key_s2 *));

  temp.ks2 = init_vector(temp.msize2);
  temp.ks1 = NULL;

  while(1){
    p1 = (key_s1 *)calloc(1,sizeof(key_s1));
    p2 = (key_s2 *)calloc(1, sizeof(key_s2));
    p1->info = (Item *)calloc(1, sizeof(Item));

    if(!fread(p1->info, sizeof(Item), 1, fk)){
      free(p1->info);
      free(p2);
      free(p1);
      break;
    }

    fread(&ind, sizeof(int), 1,fk);
    p1->key_tab = p1->info->key1_tab;
    p2->key_tab = p1->info->key2_tab;
    p2->key_len = p1->info->key2_len;
    p2->rel_tab = p1->info->rel_tab;

    p1->info->fp = fp;
    p1->info->fk = fk;
    p1->info->p1 = p1;
    p1->info->p2 = p2;

    p2->info = p1->info;

    if(!temp.ks1){
      temp.ks1 = p1;
      px1 = p1;
    }
    else{
      px1->next = p1;
      px1 = px1->next;
    }
    if(!temp.ks2[ind]){
      temp.ks2[ind] = p2;
      px2[ind] = p2;
    }
    else{
      px2[ind]->next = p2;
      px2[ind] = px2[ind]->next;
    }

    fseek(fk, sizeof(int), 1);
}

if(px1){
 px1->next = NULL;
}

 for(int i = 0; i < temp.msize2; i++){
   if(px2[i]){
     px2[i]->next = NULL;
  }
 }
 free(px2);
 *man = temp;
 return 1;
}

void save_table(table man){
  char *newname = (char *)calloc(strlen(man.filestruct)+5, sizeof(char)), *key;
  key_s1 *p1 = man.ks1;
  int len, has;
  int *lis = (int *)calloc(man.msize2, sizeof(int));

  strcat(newname, man.filestruct);
  strcat(newname, "_new");
  FILE *fp = fopen(newname, "w+b");

  fwrite(&man.msize2, sizeof(int), 1, fp);
  fwrite(&man.csize2, sizeof(int), 1, fp);
  fwrite(&man.last, sizeof(int), 1, fp);

  while(p1){
    fwrite(p1->info, sizeof(Item), 1, fp);

    fseek(man.ff, p1->info->key2_len, 0);
    fread(&len, sizeof(int),1 , man.ff);
    key = (char *)calloc(len+1, sizeof(char));
    fread(key, sizeof(char), len, man.ff);
    has = hash(key, man.msize2);

    lis[has] = lis[has]+1;
    fwrite(&has, sizeof(int),1, fp);
    fwrite(&lis[has], sizeof(int), 1, fp);
    p1 = p1->next;
    free(key);
  }


  fclose(fp);
  free(lis);
  free(newname);
}

int search_item(unsigned key1, char *key2, table man, Item **x){
  key_s2 *tmp2;
  int ind = hash(key2, man.msize2), len;
  unsigned k1;
  char *k2;

  tmp2 = man.ks2[ind];

  while(tmp2){
    fseek(man.ff, tmp2->key_len, 0);
    fread(&len, sizeof(int), 1, man.ff);
    k2 = (char *)calloc(len+1, sizeof(char));
    fread(k2, sizeof(char), len, man.ff);
    if(strcmp(k2, key2) == 0){
      fread(&k1, sizeof(unsigned), 1, man.ff);
      if(k1 == key1){
        *x = tmp2->info;
        free(k2);
        return 1;
      }
    }
    tmp2 = tmp2 -> next;
    free(k2);
  }
  return -1;

}


int search_uns(table man, unsigned key1, Item **x){
  key_s1 *tmp;

  tmp = next_need_1(get_ks_1(man.ks1, key1), key1);

  if(!tmp){
    return 0;
  }

  *x = (tmp->info);
  return 1;
}

key_s2 * search_str(table man, char *key2, int rel){
  key_s2 *tmp;
  int ind = hash(key2, man.msize2);

  if(rel == 0){
    tmp = get_all(man.ks2[ind], key2);
  }
  else{
    tmp = next_need_2(get_release(man.ks2[ind], key2, rel), key2, rel);
  }

  return tmp;
}


int add_el(unsigned key1,char *key2, char *info, table *man, float a, float b){
  int n = 0, tab = man->last;
  Item *x;

  if(man->ks1 && get_ks_1(man->ks1, key1)){
    return 0;                                                     // Found out that key already exists
  }

  fseek(man->ff, tab, 0);
  int rel = 1, lenk = strlen(key2), leni = strlen(info);

  fwrite(&lenk, sizeof(int), 1, man->ff);
  fwrite(key2, sizeof(char), lenk, man->ff);
  fwrite(&key1, sizeof(unsigned), 1, man->ff);
  fwrite(&leni, sizeof(int), 1, man->ff);
  fwrite(info, sizeof(char), leni, man->ff);
  fwrite(&a, sizeof(float), 1, man->ff);
  fwrite(&b, sizeof(float), 1, man->ff);
  fwrite(&rel, sizeof(int), 1, man->ff);

  x = (Item *)calloc(1, sizeof(Item));

  x->key2_len = tab;
  tab += sizeof(int);
  x->key2_tab = tab;
  tab += sizeof(char) * lenk;
  x->key1_tab = tab;
  tab += sizeof(unsigned);
  x->info_len = tab;
  tab+= sizeof(int);
  x->info_tab = tab;
  tab += sizeof(char)*leni;
  x->dub1_tab = tab;
  tab+=sizeof(float);
	x->dub2_tab = tab;
  tab+= sizeof(float);
  x->rel_tab = tab;
  tab += sizeof(int);
  x->fp = man->ff;

  man->last = tab;

  man->ks1 = add_1(man->ks1, key1, x);                               // Added new element at the beginning of the first keyspace

  man->ks2 = add(key2, man->msize2, man->ks2, &n, x);    // Added new element at the beginning of the second keyspace

  if(n){
    man->csize2 += 1;                                                // New branch were created
  }

  return 1;
}

void del_el(unsigned key1, char *key2, table *man){
  Item *x;

  int ind = hash(key2, man->msize2);

  if(!(man->ks1 && man->ks2[ind])){
    print_war("YOU'VE GOT EMPTY TABLE", -1);
    printf("\n");
    return;
  }

  if(!search_item(key1, key2, *man, &x)){
    print_war("NO SUCH A PAIR OF KEYS", -1);
    printf("\n");
    return;
  }

  del_uns(man, key1);
}


int del_uns(table *man, unsigned key1){
  key_s1 *tmp1, *p1, *px1;
  key_s2 *tmp2, *p2, *px2;
  Item *x;
  char *key2, *k3;
  int ind, len, rel;

  if(!(man->ks1)){
    return -1;
  }


  p1 = get_ks_1(man->ks1, key1);
  if(!p1){
    return 0;
  }

  px1 = p1;
  p1 = next_need_1(p1, key1);

  fseek(man->ff, p1->info->key2_len, 0);
  fread(&len, sizeof(int), 1, man->ff);
  key2 = (char *)calloc(len+1, sizeof(char));
  fread(key2, sizeof(char), len, man->ff);
  fseek(man->ff, p1->info->rel_tab, 0);
  fread(&rel, sizeof(int), 1, man->ff);
  ind = hash(key2, man->msize2);

  tmp1 = man->ks1;
  tmp2 = man->ks2[ind];
  x = p1->info;

  if(p1 == tmp1){
    man->ks1 = p1->next;
    free(p1);
  }
  else{
    px1->next = p1->next;
    free(p1);
  }

  px2 = get_release(tmp2, key2, rel);
  p2 = next_need_2(px2, key2, rel);

  fseek(man->ff, p2->rel_tab, 0);
  fread(&rel, sizeof(int), 1, man->ff);

  if(p2 == tmp2){
    man->ks2[ind] = p2->next;
    free(p2);
  }
  else{
    px2->next = p2->next;
    free(p2);
  }

  free(x);                 // Freeing info in Item

  px2 = man->ks2[ind];

  int c = 0;
  while(px2 && !c){
    fseek(man->ff, px2->key_len, 0);
    fread(&len, sizeof(int),1, man->ff);
    k3 = (char *)calloc(len+1, sizeof(char));
    fread(k3, sizeof(char), len, man->ff);
    if(strcmp(k3, key2) == 0){
      c++;
    }
    free(k3);
    px2 = px2->next;
  }
  if(c){
    shift_ind(man->ks2[ind], key2);
  }

  if(!man->ks2[ind]){
    man->csize2--;
  }
  free(key2);
  return 1;
}

int del_str(table *man,char *key2, int rel){
  key_s2 *tmp2, *p2;

  unsigned key1;
  int ind = hash(key2, man->msize2);

  if(!(man->ks2[ind])){
    return -1;
  }

  if (rel == 0){
    tmp2 = get_all(man->ks2[ind], key2);

    if(!tmp2){
      return 0;
    }

    while(tmp2){
      p2 = tmp2;
      fseek(man->ff, tmp2->info->key1_tab, 0);
      fread(&key1, sizeof(unsigned), 1, man->ff);
      del_uns(man, key1);
      tmp2 = tmp2->next;
      free(p2);
    }
  }
  else{
    tmp2 = next_need_2(get_release(man->ks2[ind], key2, rel), key2, rel);
    if(!tmp2){
      return 0;
    }
    else{
      fseek(man->ff, tmp2->info->key1_tab, 0);
      fread(&key1, sizeof(int), 1, man->ff);
      del_uns(man, key1);
    }
  }

return 1;
}


void show_table(table man, int n){
  key_s1 *tmp;

  if(n == 1){
    printf("\n--------------------");
    print_und("YOUR FIRST KEYSPACE", -1);
    printf("--------------------\n");
    if(man.ks1){
      print_keyspace_1(man.ks1);
    }
    else{
      print_war("                        EMPTY KEYSPACE", -1);
    }
    printf("\n-----------------------------------------------------------\n");

    printf("\n--------------------");
    print_und("YOUR SECOND KEYSPACE", -1);
    printf("-------------------\n");
    for (int i=0; i < man.msize2; i++){
      printf("%d:\n", i+1);
      if(man.ks2[i]){
        print_keyspace_2(man.ks2[i]);
      }
      else{
        print_war("                        EMPTY BRANCH", -1);
        printf("\n");
      }
      printf("\n");
    }
    printf("-----------------------------------------------------------\n");
  }

  printf("\n------------------------");
  print_und("YOUR TABLE", -1);
  printf("-------------------------\n");

  tmp = man.ks1;
  print_suc("               CURRENT COUNT OF KS2 ELEMENTS: ", man.csize2);
  printf("\n\n");
  int k1;
  float f1,f2;
  char *k2, *info;
  int lenk, leni;

  while(tmp){
    fseek(man.ff, tmp->info->key2_len, 0);
    fread(&lenk, sizeof(int), 1, man.ff);
    k2 = (char *)calloc(lenk+1, sizeof(char));
    fread(k2, sizeof(char), lenk, man.ff);
    fread(&k1, sizeof(unsigned), 1, man.ff);
    fread(&leni, sizeof(int), 1, man.ff);
    info = (char *)calloc(leni+1, sizeof(char));
    fread(info, sizeof(char), leni, man.ff);
    fread(&f1, sizeof(float), 1, man.ff);
    fread(&f2, sizeof(float), 1, man.ff);

    printf("Ks1: %d Ks2: \'%s\' Value: {%s, %f, %f}\n", k1, k2, info, f1, f2);
    free(info);
    free(k2);
    tmp = tmp->next;
  }
  printf("\n-----------------------------------------------------------\n");
}

void free_table(table *man){
  free_keyspace_1(man->ks1);
  free_vec(man->ks2, man->msize2);
  fclose(man->ff);
}
