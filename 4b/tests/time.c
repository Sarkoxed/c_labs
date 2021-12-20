#include "lib.h"

int main(){
  node *tree = NULL, *src;
  int n = 5,suc, key[10000], key1[10000], k, cnt = 1000000, i,j, m;
  clock_t f, l;
  Item *o;
  srand(time(NULL));
  while(n-- > 0){
    printf("started adding\n");

    for (i = 0; i<10000; i++){
      key[i] = rand() * rand();
    }
    for(i = 0; i < cnt * (10 - n); ){
      k = rand()*rand();
      suc = 0;
      o = calloc(1, sizeof(Item));
      tree = add(tree, k, o, &suc);
      if(suc){
        if(100000<=i && i<110000)
        key1[i-100000]=k;
        i++;
      }
    }
    m = 0;
    printf("added all, start searching\n");
    f = clock();
    for(i = 0; i<10000; i++){
      suc = 0;
      get(tree, key[i], &suc, &j);
      l = clock();
      if(suc){
        m++;
      }
    }
    printf("added all, start searching\n");
    f = clock();
    for(i = 0; i<10000; i++){
      suc = 0;
      get(tree, key1[i], &suc, &j);
      l = clock();
      if(suc){
        m++;
      }
    }
      printf("%d items were found\n", m);
      printf("Test %d, num of nodes: %d, time: %ld %f, depth: %d\n", 10 - n, (10 - n)*cnt, l-f, (float)(l - f)/CLOCKS_PER_SEC, depth(tree));

    free_tree_1(tree);
    tree = NULL;
  }
  return 0;
}
