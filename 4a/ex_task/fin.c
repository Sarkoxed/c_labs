#include "fin.h"

Item * init_item(){
  Item *x = (Item *)calloc(1, sizeof(Item));
  x->count = 0;
  return x;
}

node * init(int key, Item *x){
  node *new = (node *)calloc(1, sizeof(node));
  new->par = NULL;
  new->info = x;
  new->key = key;
  new->info->count = 1;
  return new;
}

node * add(node *orig, int key, Item *x, int *suc){  //O(log(n))
  if(!orig){
    *suc = 1;
    return init(key, x);
  }
  if(orig->key < key){
    orig->right = add(orig->right, key, x, suc);
    orig->right->par = orig;
  }
  else if(orig->key > key){
    orig->left = add(orig->left, key, x, suc);
    orig->left->par = orig;
  }
  else{
    orig->info->count = orig->info->count+1;
  }
 return orig;
}

node * get(node *orig, int key, int *suc){ //O(log(n))
  if(!orig){
    *suc = 0;
    return NULL;
  }
  if(orig->key > key){
    return get(orig->left,  key, suc);
  }
  if(orig->key < key){
    return get(orig->right, key, suc);
  }
  *suc = 1;
  return orig;
}

int tree_save(node *orig, FILE *fp, int cou){
  if(!orig){
    return cou;
  }
  fprintf(fp, "[%d, %d],", orig->key, orig->info->count);
  cou++;

  if(orig->left){
    cou = tree_save(orig->left,fp, cou);
  }

  if(orig->right){
    cou = tree_save(orig->right,fp, cou);
  }

  return cou;
}

int tree_save_1(node *orig, FILE *fp, int cou){
  if(!orig){
    return cou;
  }
  cou++;

  if(orig->left){
    cou = tree_save_1(orig->left,fp, cou);
  }
  fprintf(fp, "%d: %d\n", orig->key, orig->info->count);


  if(orig->right){
    cou = tree_save_1(orig->right,fp, cou);
  }

  return cou;
}

void save(node *orig){
  FILE *fp, *fk = fopen("Task.txt", "w+t");
  char *name = (char *)calloc(20, sizeof(char));

  sprintf(name, "Task%d.txt", orig->amo);
  fp = fopen(name, "w+t");

  fprintf(fp, "[%d, ", depth(orig));
  tree_save(orig, fp, 0);
  tree_save_1(orig, fk, 0);
  fprintf(fp, "]");

  fclose(fp);
  fclose(fk);
  free(name);
}

void free_tree(node *orig){
  if(!orig){
    return;
  }
  free_tree(orig->left);
  node *tmp = orig->right;
  free(orig->info);
  free(orig);
  free_tree(tmp);
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
