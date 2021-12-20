#include <stdio.h>
#include <stdlib.h>

#include "lib.h"
#include "keyspace1.h"
#include "keyspace2.h"

void free_all(char ***tmp);
void options();

void free_all(char ***tmp){
  for (int i = 0; i < 5; i++){
    if(*tmp[i]){
      free(*tmp[i]);
      *tmp[i] = NULL;
    }
  }
}

void options(){
  printf("Type \'");
  print_fat("help");
  printf("\'     if you need my options\n");

  printf("Type \'");
  print_fat("add");
  printf("\'      if you need to insert an element in table\n");

  printf("Type \'");
  print_fat("get_one");
  printf("\'  if you want to get an element via single key\n");
  printf("Type \'");
  print_fat("range");
  printf("\' if you want to get an element via single key\n");
  printf("Type \'");
  print_fat("search");
  printf("\'   if you want to get an element via pair of keys\n");

  printf("Type \'");
  print_fat("del_one");
  printf("\'  if you want to delete elements via single key\n");
  printf("Type \'");
  print_fat("delete");
  printf("\'   if you want to delete an element via pair of keys\n");

  printf("Type \'");
  print_fat("show");
  printf("\'     if you want to see your table\n");

  printf("Type \'");
  print_fat("exit");
  printf("\'     if you want to end this round\n");
}

int main(){
    table man;

    char *opt = NULL, *key2 = NULL, *info = NULL, *type = NULL, *ans = NULL, *in;
    char *filename, *name;
    char ***free_string = calloc(5, sizeof(char **));
    free_string[0] = &opt;
    free_string[1] = &key2;
    free_string[2] = &info;
    free_string[3] = &type;
    free_string[4] = &ans;

    unsigned key1;

    int n = 1, rel, fil, leni, n1 = 1, b, e;  // n for input check, rel for releases, z for file, v for vendetta
    Item *com;

    key_s1 *range, *p1;
    key_s2 *tab_search, *p;
    float dub1, dub2;

    print_suc("HELLO\nI AM YOUR TABLE MAKER!", -1);
    printf("\n");
    print_suc("I HAVE TWO KEYSPACES", -1);
    printf("\n");
    print_suc("FIRST: UNSIGNED INTEGERS", -1);
    printf("\n");
    print_suc("SECOND: STRINGS WITH VARIABLE LENGTH", -1);
    printf("\n");
    print_suc("IF YOU WANT TO SEE MY OPTIONS - TYPE \'help\'", -1);
    printf("\n");

    printf("INSERT YOUR TABLE'S FILENAME: ");
    filename = getStr(&fil);
    if(fil <= 0){
      print_err("WRONG INPUT", -1);
      printf("\n");
    }

    n1 = getFile(filename, &man.ff);
    man.filename = filename;

    if(n1){
      name = (char *)calloc(strlen(man.filename) + 8, sizeof(char));
      strcat(name, man.filename);
      strcat(name, "_struct");
      man.filestruct = name;
      init_table(&man);
    }

    while(fil && n1){
      free_all(free_string);

      printf("\nWHAT SHELL I DO?\n");
      printf("-> ");

      opt = getStr(&n);
      if (n == -1){
        print_err("REACHED EOF", -1);
        printf("\n");
        break;
      }

      if(strcmp(opt, "help") == 0){
        options();
      }
      else if(strcmp(opt, "search") == 0){

        printf("INSERT FIRST KEY: ");

        if(!getInt(&rel)){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }

        key1 = (unsigned int)rel;

        printf("\nINSERT SECOND KEY: ");

        key2 = getStr(&n);

        if (n == -1){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }
        else if(n == 0){
          print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
          printf("\n");
          continue;
        }

        printf("\n");
        n = search_item(key1, key2, man, &com);
        if(n == 0){
          print_war("SEEMS THAT THERE IS NO SUCH A TYPE 1 KEY!", -1);
          printf("\n");
        }
        else if(n == -1){
          print_war("SEEMS THAT THERE IS NO SUCH A TYPE 2 KEY", -1);
          printf("\n");
        }
        else{
          fseek(man.ff, com->info_len, 0);
          fread(&leni, sizeof(int), 1, man.ff);
          in = (char *)calloc(leni+1, sizeof(char));
          fread(&dub1, sizeof(float), 1, man.ff);
          fread(&dub2, sizeof(float), 1, man.ff);

          print_suc("THERE IS YOUR ITEM", -1);
          printf("\n");
          printf("{%s, %f, %f}\n", in, dub1, dub2);
          free(in);
        }
      }
      else if(strcmp(opt, "add") == 0){
        printf("INSERT FIRST KEY: ");

        if(!getInt(&rel)){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }

        key1 = (unsigned int)rel;
        printf("\nINSERT SECOND KEY: ");

        key2 = getStr(&n);

        if (n == -1){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }
        else if(n == 0){
          print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
          printf("\n");
          continue;
        }

        printf("\nINSERT INFO STRING: ");

        info = getStr(&n);

        if (n == -1){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }
        else if(n == 0){
          print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
          printf("\n");
          continue;
        }

        printf("INSERT FIRST FLOAT: ");

        if(!getFloat(&dub1)){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }

        printf("INSERT SECOND FLOAT: ");

        if(!getFloat(&dub2)){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }
        printf("\n");


        printf("\n");

        n = add_el(key1, key2, info, &man, dub1, dub2);
        if(!n){
          print_war("THERE IS ALREADY SUCH A TYPE 1 KEY", -1);
          printf("\n");
        }
        else{
          print_suc("SUCCESSFULLY ADDED NEW ELEMENT", -1);
          printf("\n");
        }
      }
      else if(strcmp(opt, "delete") == 0){
        printf("INSERT FIRST KEY: ");

        if(!getInt(&rel)){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }

        key1 = (unsigned int)rel;
        printf("\nINSERT SECOND KEY: ");

        key2 = getStr(&n);

        if (n == -1){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }
        else if(n == 0){
          print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
          printf("\n");
          continue;
        }
        printf("\n");
        del_el(key1, key2, &man);
        printf("deleted %d %s", key1, key2);

      }
      else if(strcmp(opt, "get_one") == 0){
        printf("INSERT THE TYPE OF KEY(uns/str): ");

        type = getStr(&n);


        if (n == -1){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }
        else if(n == 0){
          print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
          printf("\n");
          continue;
        }
        printf("\n");
        if (strcmp(type, "str") != 0 && strcmp(type, "uns") != 0){
          print_war("WARNING! NO SUCH AN OPTION. CONTINUE", -1);
          printf("\n");
          continue;
        }

        if(strcmp(type, "uns") == 0){
          printf("INSERT KEY: ");

          if(!getInt(&rel)){
            print_err("REACHED EOF", -1);
            printf("\n");
            break;
          }

          key1 = (unsigned int)rel;

          printf("\n");

          if(!man.ks1){
            print_war("YOU'VE GOT EMPTY TABLE", -1);
            printf("\n");
            continue;
          }

          n = search_uns(man, key1, &com);
          if(!n){
            print_war("NO SUCH A KEY 1 FOUND", -1);
            printf("\n");
          }
          else{
            fseek(man.ff, com->info_len, 0);
            fread(&leni, sizeof(int), 1, man.ff);
            in = (char *)calloc(leni+1, sizeof(char));
            fread(in, sizeof(char), leni, man.ff);
            fread(&dub1, sizeof(float), 1, man.ff);
            fread(&dub2, sizeof(float), 1, man.ff);
            print_suc("THERE\'S YOUR ITEM: ", -1);
            printf("{%s, %f, %f}", in, dub1, dub2);
            free(in);
          }
        }

        else if(strcmp(type, "str") == 0){
          printf("INSERT KEY: ");

          key2 = getStr(&n);

          if (n == -1){
            print_err("REACHED EOF", -1);
            printf("\n");
            break;
          }
          else if(n == 0){
            print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
            printf("\n");
            continue;
          }

          printf("DO YOU WANT TO SEARCH FOR SPECIFIC RELEASE?(y/n): ");

          ans = getStr(&n);

          printf("\n");
          if (n == -1){
            print_err("REACHED EOF", -1);
            printf("\n");
            break;
          }
          else if(n == 0){
            print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
            printf("\n");
            continue;
          }

          if(strcmp(ans, "y") != 0 && strcmp(ans, "n") != 0){
            print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
            printf("\n");
            continue;
          }

          if(strcmp(ans, "y") == 0){
            printf("INSERT RELEASE NUMBER: ");

            if (!getInt(&rel)){
              print_err("REACHED EOF", -1);
              printf("\n");
              break;
            }

          }
            else{
              rel = 0;
            }
            printf("\n");


          if(!(man.ks2[hash(key2, man.msize2)])){
            print_war("YOU'VE GOT EMPTY BRANCH", -1);
            printf("\n");
            continue;
          }

          tab_search = search_str(man, key2, rel);
          if(!tab_search){
            print_war("NO SUCH A KEY 2 FOUND", -1);
            printf("\n");
          }
          else{
            if(rel == 0 && tab_search->next){
              print_suc("YOUR ITEMS:", -1);
              printf("\n");
              print_keyspace_2(tab_search);

              while(tab_search){
                p = tab_search;
                tab_search = tab_search->next;
                free(p);
              }
            }
            else if(rel == 0 && !tab_search->next){
              print_suc("THERE\'S YOUR ITEM: ", -1);
              fseek(man.ff, tab_search->info->info_len, 0);
              fread(&leni, sizeof(int), 1, man.ff);
              in = (char *)calloc(leni+1, sizeof(char));
              fread(in, sizeof(char), leni, man.ff);
              fread(&dub1, sizeof(float), 1, man.ff);
              fread(&dub2, sizeof(float), 1, man.ff);
              printf("{%s, %f, %f}\n", in, dub1, dub2);
              free(in);
              free(tab_search);
            }

            else{
              print_suc("THERE\'S YOUR ITEM: ", -1);

              fseek(man.ff, tab_search->info->info_len, 0);
              fread(&leni, sizeof(int), 1, man.ff);
              in = (char *)calloc(leni+1, sizeof(char));
              fread(in, sizeof(char), leni, man.ff);
              fread(&dub1, sizeof(float), 1, man.ff);
              fread(&dub2, sizeof(float), 1, man.ff);
              printf("{%s, %f, %f}\n", in, dub1, dub2);
              free(in);
            }
          }
      }

    }
      else if(strcmp(opt, "del_one") == 0){
        printf("INSERT THE TYPE OF KEY(uns/str): ");

        type = getStr(&n);


        if (n == -1){
          print_err("REACHED EOF", -1);
          printf("\n");
          break;
        }
        else if(n == 0){
          print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
          printf("\n");
          continue;
        }

        printf("\n");
        if (strcmp(type, "str") != 0 && strcmp(type, "uns") != 0){
          print_war("WARNING! NO SUCH AN OPTION. CONTINUE", -1);
          printf("\n");
          continue;
        }

        if(strcmp(type, "uns") == 0){
          printf("INSERT KEY: ");

          if(!getInt(&rel)){
            print_err("REACHED EOF", -1);
            printf("\n");
            break;
          }

          key1 = (unsigned int)rel;
          printf("\n");
          n = del_uns(&man, key1);
          if(n == -1){
            print_war("YOU'VE GOT EMPTY TABLE", -1);
            printf("\n");
          }
          else if(n == 0){
            print_war("NOTHING TO DELETE", -1);
            printf("\n");
          }
          else{
            print_suc("SUCCESSFULLY DELETED ELEMENT", -1);
            printf("\n");
          }

        }
        else if(strcmp(type, "str") == 0){
          printf("INSERT KEY: ");

          key2 = getStr(&n);


          if (n == -1){
            print_err("REACHED EOF", -1);
            printf("\n");
            break;
          }
          else if(n == 0){
            print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
            printf("\n");
            continue;
          }

          printf("DO YOU WANT TO DELETE SPECIFIC RELEASE?(y/n): \n");

          ans = getStr(&n);

          if (n == -1){
            print_err("REACHED EOF", -1);
            printf("\n");
            break;
          }
          else if(n == 0){
            print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
            printf("\n");
            continue;
          }

          if(strcmp(ans, "y") != 0 && strcmp(ans, "n") != 0){
            print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
            printf("\n");
            continue;
          }

          printf("\n");

          if(strcmp(ans, "y") == 0){
            printf("INSERT RELEASE: ");

            if (!getInt(&rel)){
              print_err("REACHED EOF", -1);
              printf("\n");
              break;
            }

          }
            else{
              rel = 0;
            }

          n  = del_str(&man, key2, rel);
          if(n == -1){
            print_war("YOU'VE GOT EMPTY BRANCH", -1);
            printf("\n");
          }
          if(n == 0){
            print_war("NO SUCH A KEY 2 FOUND", -1);
            printf("\n");
          }
          else{
            print_suc("SUCCESSFULLY DELETED", -1);
            printf("\n");
          }
        }
        }
      else if(strcmp(opt, "show") == 0){
          printf("DO YOU WANT ME TO SHOW YOUR KEYSPACES?(y/n): ");

          ans = getStr(&n);


          printf("\n");
          if (n == -1){
            print_err("REACHED EOF", -1);
            printf("\n");
            break;
          }
          else if(n == 0){
            print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
            printf("\n");
            continue;
          }

          if(strcmp(ans, "y") != 0 && strcmp(ans, "n") != 0){
            print_war("WARNING!! WRONG INPUT. CONTINUE.", -1);
            printf("\n");
            continue;
          }
          n = 0;
          if(strcmp(ans, "y") == 0){
             n = 1;
          }
          printf("\n");
          show_table(man, n);
        }
       else if(strcmp(opt, "range") == 0){
          printf("INSERT THE BEGINNING POINT: ");
          if(!getInt(&b)){
            print_err("REACHED EOF", -1);
            printf("\n");
            break;
          }
          printf("INSERT THE ENDING POINT: ");
          if(!getInt(&e)){
            print_err("REACHED EOF", -1);
            printf("\n");
            break;
          }

          range = search_range(man.ks1, b, e);
          print_suc("YOUR ITEMS:", -1);
          printf("\n");
          print_keyspace_1(range);

          while(range){
            p1 = range;
            range = range->next;
            free(p1);
          }

        }
      else if(strcmp(opt, "exit") == 0){
          print_suc("GOODBYE, SEE YA!", -1);
          printf("\n");
          break;
        }
      else{
          print_war("I DO NOT UNDERSTAND WHAT DO YOU WANT FOR ME", -1);
          printf("\n");
          print_war("PLEASE TRY AGAIN OR TYPE \'HELP\'", -1);
          printf("\n");
        }
    }

    if(fil){
      if(n1){
        save_table(man);
        free_table(&man);
        free(name);
      }
    free(filename);
    }

    free_all(free_string);
    free(free_string);
    return 0;
    }
