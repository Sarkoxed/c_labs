#include "lib.h"

void free_all(char ***tmp, int n);
void options();

void free_all(char ***tmp, int n){
  for (int i = 0; i < n; i++){
    if(*tmp[i]){
      free(*tmp[i]);
      *tmp[i] = NULL;
    }
  }
}

void options(){
printf("Type \'" fat "add" white "\'    to add new node\n");
printf("Type \'" fat "delete" white "\' to delete a nod\n");
printf("Type \'" fat "search" white "\' to get a nod via key\n");
printf("Type \'" fat "next" white "\'   to get a nod via key\n");

printf("Type \'" fat "show" white "\'   to show the table in your range\n");
printf("Type \'" fat "save" white "\'   to save a tree\n");

printf("Type \'" fat "exit" white "\'   to finish\n");

printf("Type \'" fat "new" white "\'    to read tree from file\n");
}

int main(){

int n, key, cou, t,t0, beg, end;
float f1, diff;
Item *x;
node *tree = NULL, *src;
char *opt = NULL, *info = NULL;
char ***free_string = (char ***)calloc(2, sizeof(char **));
free_string[0] = &opt;
free_string[1] = &info;

t0 = clock();
while(1){
  free_all(free_string, 2);

  printf("\nWhat shall i do?\n->");
  opt = getStr(&n);
  if(n == -1){
    break;
  }

  if(!strcmp(opt, "add")){
    printf("Insert key: ");
    if(!getInt(&key)){
      break;
    }
    printf("Insert info: ");
    info = getStr(&n);
    if(n < 0){
      break;
    }
    if(n == 0){
      fprintf(stdout, blue "Warning! Null string. Continue.\n" white);
      continue;
    }
    printf("Insert float: ");
    if(!getFloat(&f1)){
      break;
    }

    x = init_item(info, f1);
    n = 0;
    t = clock();

    tree = add(tree, key, x, &n);
    diff = (float)(clock() - t)/ CLOCKS_PER_SEC;

    if(!n){
      fprintf(stdout, blue "Seems that there is already such a key\n" white);
      free(x->string);
      free(x);
    }
    else{
      tree->amo += 1;
      fprintf(stdout, green "Successfully added node with key %d\n" white, key);
    }
    timer(diff, tree->amo, 2);

  }
  else if(!strcmp(opt, "delete")){
    printf("Insert key: ");
    if(!getInt(&key)){
      break;
    }
    cou  = tree->amo;
    n = 1;
    t = clock();
    tree = delete(tree, key, &n);
    diff = (float)(clock() - t)/ CLOCKS_PER_SEC;
    if(!n){
      fprintf(stdout, blue "Nothing to delete\n" white);
    }
    else{
      tree->amo = cou - 1;
      fprintf(stdout, green "Successfully deleted node with key %d\n" white, key);
    }
    timer(diff, tree->amo, 2);

  }
  else if(!strcmp(opt, "search")){
    printf("Insert key: ");
    if(!getInt(&key)){
      break;
    }
    t = clock();
    n = 1;
    src = get(tree, key, &n);
    diff = (float)(clock() - t)/ CLOCKS_PER_SEC;
    timer(diff, tree->amo, 2);
    if(!n){
      fprintf(stdout, blue "There's no such a key\n" white);
    }
    else{
      fprintf(stdout, green "Here's your item: \n" white);
      printf("key: %d Value: {%s, %f}\n", src->key, src->info->string, src->info->f1);
    }
  }
  else if(!strcmp(opt, "show")){
    if(!tree){
      fprintf(stdout, blue "Empty tree\n" white);
    }
    else{
      printf("Insert a begining integer: ");
      if(!getInt(&beg)){
        break;
      }
      printf("Insert an ending integer: ");
      if(!getInt(&end)){
        break;
      }

      printf(un "Current table size: %d\n" white, tree->amo);
      t = clock();
      show_tree(tree, beg, end);
      diff = (float)(clock() - t)/ CLOCKS_PER_SEC;
      timer(diff, tree->amo, 1);
    }
  }
  else if(!strcmp(opt, "save")){
    save(tree);
    save_1(tree);
  }
  else if(!strcmp(opt, "exit")){
    save(tree);
    save_1(tree);

    fprintf(stdout, fat "GOODBYE, SEE YA!\n" white);
    break;
  }
  else if(!strcmp(opt, "help")){
    options();
  }
  else if(!strcmp(opt, "new")){
    tree = init_new(tree);
  }
  else if(!strcmp(opt, "next")){
    printf("Insert integer: ");
    if(!getInt(&key)){
      break;
    }
    n = 1;
    t = clock();
    src = get_next(tree, key, &n);

    diff = (float)(clock() - t)/ CLOCKS_PER_SEC;
    timer(diff, tree->amo, 1);
    if(!src){
      fprintf(stdout, blue "Seems that your value is too high\n" white);
    }
    else{
      fprintf(stdout, green "Here's your item: \n" white);
      printf("key: %d Value: {%s, %f}\n", src->key, src->info->string, src->info->f1);
    }
  }
  else{
    fprintf(stdout, blue "I do not understand what do you want for me\n");
    fprintf(stdout, "Type \'help\' to check out my options\n" white);
  }
}

diff = (float)(clock() - t0)/ CLOCKS_PER_SEC;
//timer(diff, tree->amo, 3);
free_tree(tree);
free_all(free_string, 2);
free(free_string);
}
