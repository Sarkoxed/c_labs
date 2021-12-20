#include "lib.h"

Item * init_item(char *string, float f1){
  Item *x = (Item *)calloc(1, sizeof(Item));
  char *a = (char *)calloc(strlen(string)+1, sizeof(char));
  strcat(a, string);
  x->string = a;
  x->f1 = f1;
  return x;
}

node * init(int key, Item *x){
  node *new = (node *)calloc(1, sizeof(node));
  new->par = NULL;
  new->info = x;
  new->key = key;
  return new;
}

node * inorder_predecessor(node *cur){
  node *p = cur, *y;
  if (p->left){
    p = p->left;
    while(p->right){
      p=p->right;
    }
    return p;
  }

  y = p->par;
  while(y && p == y->left){
    p = y;
    y = y->par;
  }

  return y;
}

node * inorder_successor(node *cur){
  node *p = cur, *y;
  if (p->right){
    p = p->right;
    while(p->left){
      p=p->left;
    }
    return p;
  }

  y = p->par;
  while(y && p == y->right){
    p = y;
    y = y->par;
  }

  return y;
}


node * add(node *orig, int key, Item *x, int *suc){
  node *p = orig, *tmp;
  if(!orig){
    *suc = 1;
    return init(key, x);
  }
  while(1){
    if(p->key > key){
      if(p->left){
        p = p->left;
      }
      else{
        break;
      }
    }
    else if(p->key < key){
      if(p->right){
        p = p->right;
      }
      else{
        break;
      }
    }
    else if(p->key == key){
      *suc = 0;
      free(x);
      return orig;
    }
  }

  *suc = 1;
  tmp = init(key, x);
  tmp->par = p;

  if(p->key > key){
    p->left = tmp;
  }
  else if(p->key < key){
    p->right = tmp;
  }
  tmp->next = inorder_successor(tmp);
  if(tmp->next){
    tmp->next->prev = tmp;
  }
  tmp->prev = inorder_predecessor(tmp);
  if(tmp->prev){
    tmp->prev->next = tmp;
  }
 return orig;
}

node * delete(node *orig, int key, int *suc){
  if(!orig){
    *suc = 0;
    return orig;
  }
  node *p = orig;

  while(1){
    if(p->key > key){
      if(p->left){
        p = p->left;
      }
      else{
        *suc = 0;
        return orig;
      }
    }
    else if(p->key < key){
      if(p->right){
        p = p->right;
      }
      else{
        *suc = 0;
        return orig;
      }
    }
    else if(p->key == key){
      *suc = 1;
      break;
    }
  }

  if(!(*suc)){
    return orig;
  }

  node *par = p->par, *prev = p->prev, *next = p->next, *s;
  if(!p->left && !p->right){
    if(par->left == p){
      free(p->info->string);
      free(par->left->info);
      free(par->left);
      par->left = NULL;
    }
    else if(par->right == p){
      free(p->info->string);
      free(par->right->info);
      free(par->right);
      par->right = NULL;
    }
    if(prev){
      prev->next = next;
    }
    if(next){
      next->prev = prev;
    }
  }
  else if(!p->left || !p->right){
    if(!p->left){
      if(par->left == p){
        par->left = p->right;
      }
      else if(par->right == p){
        par->right = p->right;
      }
      p->right->par = par;
  }
  else if(!p->right){
    if(par->left == p){
      par->left = p->left;
    }
    else if(par->right == p){
      par->right = p->left;
    }
    p->left->par = par;
  }
  if(prev){
    prev->next = next;
  }
  if(next){
    next->prev = prev;
  }
  free(p->info->string);
  free(p->info);
  free(p);
  }
  else{
    s = p->next;
    free(p->info->string);
    free(p->info);
    p->info = s->info;
    p->key = s->key;

    if(s->par->left == s){
      s->par->left = s->right;
    if(s->right){
      s->right->par = s->par;
    }
  }
  else{
    s->par->right = s->right;
  if(s->right){
    s->right->par = s->par;
  }
  }

  if(s->prev)
  s->prev->next = p;
  if(s->next)
  s->next->prev = p;

  p->next = s->next;
  free(s);
  }

return orig;
}

node * get(node *orig, int key, int *suc){
  node *p = orig;
  while(1){
    if(p->key > key){
      if(p->left){
        p = p->left;
      }
      else{
        *suc = 0;
        return NULL;
      }
    }
    else if(p->key < key){
      if(p->right){
        p = p->right;
      }
      else{
        *suc = 0;
        return NULL;
      }
    }
    else if(p->key == key){
      *suc = 1;
      return p;
    }
  }


  return orig;
}

node * get_next(node *orig, int key, int *suc){ //O(n)
  if(!orig){
    *suc = 0;
    return NULL;
  }

  while(orig->left){
    orig = orig->left;
  }
  while(orig && orig->key <= key){
    orig = orig->next;
  }
  if(!orig){
    *suc = 0;
    return NULL;
  }
  *suc = 1;
  return orig;

}

int el_count(node *orig, int c){
  while(orig->left){
    orig = orig->left;
  }
  int n = 0;
  while(orig){
    orig = orig->next;
    n++;
  }
  return n;
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
  fprintf(fp, "[%d, \"%s\", %f],", orig->key, orig->info->string, orig->info->f1);

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
  char *name = (char *)calloc(20, sizeof(char));

  //sprintf(name, "%d_tree", el_count(orig, 0));
  printf("Current amount: %d and %d for func\n", orig->amo, el_count(orig, 0));
  sprintf(name, "%d_tree", el_count(orig, 0));
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
  free(orig->info->string);
  free(orig->info);
  free(orig);
  free_tree(tmp);
}

void show_tree(node *orig, int b, int e){
  if(!orig){
   return;
  }
  while(orig->left){
    orig = orig->left;
  }
  while(orig){
    if(orig->key <= e && orig->key >= b){
      printf("key: %03d Value: {%s, %f}\n", orig->key, orig->info->string, orig->info->f1);
    }
    orig = orig->next;
  }
}

node * init_new(node *orig){
  int n, key;
  printf("Insert filename: ");
  char *name = getStr(&n), *info;
  node *lol = orig;
  float f1;
  Item *x;
  FILE *fp = fopen(name, "r+b");
  while(fread(&key, sizeof(int),1,fp)){
    fread(&n, sizeof(int),1,fp);
    info = calloc(n+1,sizeof(char));
    fread(info, sizeof(char), n, fp);
    fread(&f1, sizeof(float), 1, fp);
    x = init_item(info, f1);
    lol = add(lol, key, x, &n);
    free(info);
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
  int n = strlen(orig->info->string);
  fwrite(&n, sizeof(int), 1, fp);
  fwrite(orig->info->string, sizeof(char), n, fp);
  fwrite(&orig->info->f1, sizeof(float), 1, fp);

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
