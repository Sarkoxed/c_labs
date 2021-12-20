#include "lib.h"

Item * init_item(int tab){
  Item *x = (Item *)calloc(1, sizeof(Item));
  x->tab = tab;
  x->next = NULL;
  return x;
}

node * init(unsigned key, Item *x){
  node *new = (node *)calloc(1, sizeof(node));
  new->par = NULL;
  new->info = x;
  new->key = key;
  new->kef = 0;
  new->N = difference;
  return new;
}

node * rot_check(node *orig){
  if(orig->kef == -orig->N - 1){
    orig = left_rot(orig);
  }
  else if (orig->kef == orig->N + 1){
    orig = right_rot(orig);
  }
  return orig;
}

node * right_rot(node *orig){
  node *tmp, *tmpl, *tmpr;
  int count  = orig->rs + orig->ls + 1;
  int left_diff = orig->left->kef;
  int max_diff = orig->N;

  if(orig->left->kef >= 0){
    tmp = orig->left;
    tmpr = tmp->right;

    tmp->par = NULL;
    tmp->kef = (-count + 2*left_diff + max_diff) / 2;

    tmp->right = orig;
    orig->par = tmp;
    orig->left = tmpr;
    tmpr->par = orig;
    orig->kef = (-count + 2 - 2*left_diff + 3*max_diff) / 4;
    tmp->amo = orig->amo;
    orig->amo = 0;
    return tmp;
  }

  int left_right_diff = orig->left->right->kef;

  tmp = orig->left->right;
  tmpl = tmp->left;
  tmpr = tmp->right;

  tmp->par = NULL;
  orig->par = tmp;
  orig->left->par = tmp;

  tmp->left = orig->left;
  tmp->right = orig;

  orig->left = tmpr;
  tmp->left->right = tmpl;

  orig->kef = (-3*count + 2 - 2*left_diff + 5*max_diff - 4*left_right_diff) / 8;
  tmp->right->kef = (6*left_diff + max_diff + count - 4*left_right_diff + 2) / 8;

  tmp->kef = (4*left_right_diff - count +2*left_diff + 2 + 3*max_diff) / 4;

  tmp->amo = orig->amo;
  orig->amo = 0;

  return tmp;
}

node * left_rot(node *orig){
  node *tmp, *tmpl, *tmpr;
  int count  = orig->rs + orig->ls + 1;
  int right_diff = orig->right->kef;
  int max_diff = orig->N;

  if(orig->right->kef <= 0){
    tmp = orig->right;
    tmpl = tmp->left;

    tmp->par = NULL;
    tmp->kef = (count + 2*right_diff - max_diff) / 2;

    tmp->left = orig;
    orig->par = tmp;
    orig->right = tmpl;
    tmpl->par = orig;
    orig->kef = (count -2 - 2*right_diff - 3*max_diff) / 4;
    tmp->amo = orig->amo;
    orig->amo = 0;

    return tmp;
  }

  int right_left_diff = orig->right->left->kef;

  tmp = orig->right->left;
  tmpl = tmp->left;
  tmpr = tmp->right;

  tmp->par = NULL;
  orig->par = tmp;
  orig->right->par = tmp;

  tmp->right = orig->right;
  tmp->left = orig;

  orig->right = tmpl;
  tmp->right->left = tmpr;

  orig->kef = (3*count - 2 - 2*right_diff -5*max_diff - 4*right_left_diff) / 8;
  tmp->right->kef = (6*right_diff - max_diff - count - 4*right_left_diff - 2) / 8;

  tmp->kef = (4*right_left_diff + count +2*right_diff - 2 - 3*max_diff) / 4;

  tmp->amo = orig->amo;
  orig->amo = 0;

  return tmp;
}


node * add_node(node *orig, unsigned key, Item *x, int *suc){
  if(!orig){
    *suc = 1;
    return init(key, x);
  }
  if(orig->key < key){
    orig->right = add_node(orig->right, key, x, suc);
    orig->right->par = orig;
    if(suc){
      orig->kef = orig->kef - 1;
      orig->rs = orig->rs +1;
      orig = rot_check(orig);
    }
  }
  else if(orig->key > key){
    orig->left = add_node(orig->left, key, x, suc);
    orig->left->par = orig;
    if(suc){
      orig->kef = orig->kef + 1;
      orig->ls = orig->ls +1;
      orig = rot_check(orig);
    }
  }
  if(orig->key == key){
    *suc = 0;
    x->next = orig->info;
    orig->info = x;
  }
 return orig;
}

node * add(node *orig, unsigned key, Item *x, int *suc){
*suc = 0;
orig = add_node(orig, key, x, suc);

if(*suc){
  orig->amo += 1;
}
return orig;
}

node * delete_node(node *orig, unsigned key, int *suc){
  node *tmp;

  if(!orig){
    *suc = 0;
    return orig;
  }

  if(orig->key > key){
    orig->left = delete_node(orig->left, key, suc);
    if(suc){
      orig->kef = orig->kef - 1;
      orig->ls = orig->ls - 1;
      orig = rot_check(orig);
    }
    return orig;
  }

  if(orig->key < key){
    orig->right = delete_node(orig->right, key, suc);
    if(suc){
      orig->kef = orig->kef + 1;
      orig->rs = orig->rs +1;
      orig = rot_check(orig);
    }
    return orig;
  }

  if(!orig->left && !orig->right){
    free_list(orig->info);
    free(orig);
    return NULL;
  }

  if(!orig->left){
    tmp = orig->right;

    free_list(orig->info);
    free(orig);
    return tmp;
  }

  if(!orig->right){
    tmp = orig->left;

    free_list(orig->info);
    free(orig);
    return tmp;
  }

  node *tmpr = orig->right, *tmpl = orig->left;

  while(tmpr->left){
    tmpr = tmpr->left;
  }

  tmpr->par = orig->par;
  tmpr->left = tmpl;
  tmpl->par = tmpr;

  tmp = orig->right;

  free_list(orig->info);
  free(orig);

  return tmp;
}

node * delete(node *orig, unsigned key, int *suc){
  int lo = orig->amo;
  *suc = 1;
  orig = delete_node(orig, key, suc);

  if(*suc){
    orig->amo = lo - 1;
  }

  return orig;
}

Item ** get(node *orig, unsigned key, int *suc, int *a){ //O(log(n))
  if(!orig){
    *suc = 0;
    return NULL;
  }
  if(orig->key > key){
    return get(orig->left,  key, suc, a);
  }
  if(orig->key < key){
    return get(orig->right, key, suc, a);
  }
  *suc = 1;

  Item **x = (Item **)calloc(1, sizeof(Item *)), *tmp;
  int n = 0;
  tmp = orig->info;

  while(tmp){
    x = (Item **)realloc(x, (n+1)*sizeof(Item *));
    x[n] = tmp;
    n++;
    tmp = tmp->next;
  }
  *a = n;
  return x;
}

Item ** max(node *orig, int *a){
  while(orig->right){
    orig = orig->right;
  }
  Item **x = (Item **)calloc(1, sizeof(Item *)), *tmp;
  int n = 0;
  tmp = orig->info;
  while(tmp){
    x = (Item **)realloc(x, (n+1)*sizeof(Item *));
    x[n] = tmp;
    n++;
    tmp = tmp->next;
  }
  *a = n;
  return x;

}

int el_count(node *orig, int c){
  if(!orig){
    return c;
  }
  c++;
  c = el_count(orig->left, c);
  c = el_count(orig->right, c);
  return c;
}

int depth(node *orig){
if(!orig){
  return 0;
}

int lch = depth(orig->left);
int rch = depth(orig->right);

if(lch <= rch){
  return rch+1;
}
else{
  return lch+1;
}

}

void tree_save(node *orig, FILE *fp){
  if(!orig){
    return;
  }
  fprintf(fp, "[%d, \"%d\", \"%d\", \"%d\"],", orig->key, orig->info->tab, orig->info->tab, orig->kef);

  if(orig->left){
    tree_save(orig->left,fp);
  }

  if(orig->right){
    tree_save(orig->right,fp);
  }

  return;
}

void save(node *orig){
  FILE *fp;
  if(!orig){
    return;
  }
  char *name = (char *)calloc(20, sizeof(char));

  sprintf(name, "%d_tree", orig->amo);
  getFile(name, &fp);

  fprintf(fp, "[%d, ", depth(orig));
  tree_save(orig, fp);
  fprintf(fp, "]");

  fclose(fp);
  free(name);

}

void free_tree(node *orig){
  if(!orig){
    return;
  }
  free_tree(orig->left);
  node *tmp = orig->right;
  free_list(orig->info);
  free(orig);
  free_tree(tmp);
}

void show_tree(node *orig){
  if(!orig){
   return;
  }
  show_tree(orig->right);
  printf("key: %03d\n", orig->key);
  Item *x = orig->info;
  while(x){
    printf("Value: {%d}\n", x->tab);
    x = x->next;
  }
  show_tree(orig->left);
}

void free_list(Item *x){
  Item *tmp;
  while(x){
    tmp = x;
    x = x->next;
    free(tmp);
  }

}



node * init_new(node *orig){
  int key, tab = 0, n1;
  printf("Insert filename: ");
  char *name = getStr(&n1);
  node *lol = orig;
  Item *x;
  FILE *fp = fopen(name, "r+b");

  while(fread(&key, sizeof(unsigned),1,fp)){
    x = init_item(tab);
    tab += sizeof(unsigned);
    lol = add_node(lol, key, x, &n1);
    lol->amo = el_count(lol, 0);
    save(lol);
    save_1(lol);
  }
  lol->amo = el_count(lol, 0);
  free(name);
  return lol;
}

void tree_save_1(node *orig, FILE *fp){
  if(!orig){
    return;
  }
  fwrite(&orig->key, sizeof(int), 1, fp);

  if(orig->left){
    tree_save_1(orig->left,fp);
  }

  if(orig->right){
    tree_save_1(orig->right,fp);
  }
}

void save_1(node *orig){
  FILE *fp;
  char *name = (char *)calloc(20, sizeof(char));

  sprintf(name, "%d_tree_bin", el_count(orig, 0));
  fp = fopen(name, "w+b");

  tree_save_1(orig, fp);

  fclose(fp);
  free(name);

}


node * add_node_1(node *orig, unsigned key, Item *x, int *suc){
  if(!orig){
    *suc = 1;
    return init(key, x);
  }
  if(orig->key < key){
    orig->right = add_node_1(orig->right, key, x, suc);
    orig->right->par = orig;
    if(suc){
      orig->kef = orig->kef - 1;
      orig->rs = orig->rs+1;
    }
  }
  else if(orig->key > key){
    orig->left = add_node_1(orig->left, key, x, suc);
    orig->left->par = orig;
    if(suc){
      orig->kef = orig->kef + 1;
      orig->ls = orig->ls +1;
    }
  }
  if(orig->key == key){
    x->next = orig->info;
    orig->info = x;
  }
 return orig;
}
