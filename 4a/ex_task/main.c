#include "fin.h"

int main(){
  int n;
  unsigned a;
  char *name;
  printf("Tell me a filename: ");
  name = getStr(&n);

  FILE *fp;
  node *tree = NULL, *node;
  Item *x;
  getFile(name, &fp);
  free(name);

  while(fread(&a, sizeof(unsigned), 1, fp)){
    node = get(tree, (int)a, &n);
    if(n){
      node->info->count = node->info->count + 1;
    }else{
      x = init_item();
      tree = add(tree, a, x, &n);
      tree->amo = tree->amo + 1;
    }
  }

  save(tree);
  free_tree(tree);
  return 0;

}
