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
printf("Type \'" fat "max" white "\'    to get a node with a maximum key\n");

printf("Type \'" fat "show" white "\'   to show the table in reverse order\n");
printf("Type \'" fat "save" white "\'   to save a tree\n");

printf("Type \'" fat "exit" white "\'   to finish\n");

printf("Type \'" fat "new" white "\'    to read tree from file\n");
}

int main(){

int n, key, t,t0, am;
float diff;
Item *x, **src;
node *tree = NULL;
char *opt = NULL, *s1 = NULL, *s2 = NULL;
char ***free_string = (char ***)calloc(3, sizeof(char **));
free_string[0] = &opt;
free_string[1] = &s1;
free_string[2] = &s2;

t0 = clock();
while(1){
  free_all(free_string, 3);

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
    printf("Insert string #1: ");
    s1 = getStr(&n);
    if(n < 0){
      break;
    }
    if(n == 0){
      fprintf(stdout, blue "Warning! Null string. Continue.\n" white);
      continue;
    }
    printf("Insert string #2: ");
    s2 = getStr(&n);
    if(n < 0){
      break;
    }
    if(n == 0){
      fprintf(stdout, blue "Warning! Null string. Continue.\n" white);
      continue;
    }

    x = init_item(s1, s2);
    t = clock();

    tree = add(tree, (unsigned)key, x, &n);
    diff = (float)(clock() - t)/ CLOCKS_PER_SEC;

    if(n){
      fprintf(stdout, green "Successfully added node with key %d\n" white, key);
    }
    else{
      fprintf(stdout, green "Successfully appended new info to node with key %d\n" white, key);
    }
    timer(diff, tree->amo, 2);

  }
  else if(!strcmp(opt, "delete")){
    printf("Insert key: ");
    if(!getInt(&key)){
      break;
    }
    t = clock();
    tree = delete(tree, (unsigned)key, &n);
    diff = (float)(clock() - t)/ CLOCKS_PER_SEC;
    if(!n){
      fprintf(stdout, blue "Nothing to delete\n" white);
    }
    else{

      fprintf(stdout, green "Successfully deleted node with  %d\n" white, key);
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
    src = get(tree, (unsigned)key, &n, &am);
    diff = (float)(clock() - t)/ CLOCKS_PER_SEC;
    if(!n){
      fprintf(stdout, blue "There's no such a key\n" white);
    }
    else{
      if(am == 1){
        fprintf(stdout, green "Here's your item: \n" white);
        printf("key: %d Value: {%s, %s}\n", key, src[0]->string1, src[0]->string2);
      }
      else{
        fprintf(stdout, green "Here're your items: \n" white);
        for(int i = 0; i < am; i++){
          printf("key: %d Value: {%s, %s}\n", key, src[i]->string1, src[i]->string2);
        }
      }
    }
    timer(diff, tree->amo, 2);

    free(src);
  }
  else if(!strcmp(opt, "show")){
    if(!tree){
      fprintf(stdout, blue "Empty tree\n" white);
    }
    else{
      printf(un "Current table size: %d\n" white, tree->amo);
      t = clock();

      show_tree(tree);

      diff = (float)(clock() - t)/ CLOCKS_PER_SEC;
      timer(diff, tree->amo, 1);
    }
  }
  else if(!strcmp(opt, "save")){
    save(tree);
    save_1(tree);
  }
  else if(!strcmp(opt, "exit")){
    fprintf(stdout, fat "GOODBYE, SEE YA!\n" white);
    break;
  }
  else if(!strcmp(opt, "help")){
    options();
  }
  else if(!strcmp(opt, "new")){
    tree = init_new(tree);
  }
  else if(!strcmp(opt, "max")){
    n = 1;
    t = clock();
    src = max(tree, &am, &key);
    diff = (float)(clock() - t)/CLOCKS_PER_SEC;
    if(!n){
      fprintf(stdout, blue "There's no such a key\n" white);
    }
    else{
      if(am == 1){
        fprintf(stdout, green "Here's your item: \n" white);
        printf("key: %d Value: {%s, %s}\n", key , src[0]->string1, src[0]->string2);
      }
      else{
        fprintf(stdout, green "Here're your items: \n" white);
        for(int i = 0; i < am; i++){
          printf("key: %d Value: {%s, %s}\n", key, src[i]->string1, src[i]->string2);
        }
      }
    }
    timer(diff, tree->amo, 2);
    free(src);
  }
  else{
    fprintf(stdout, blue "I do not understand what do you want for me\n");
    fprintf(stdout, "Type \'help\' to check out my options\n" white);
  }
}

save(tree);
save_1(tree);

//diff = (float)(clock() - t0)/ CLOCKS_PER_SEC;
//timer(diff, 1, 3);
free_tree(tree);
free_all(free_string, 3);
free(free_string);
}
