#include <stdio.h>
#include <stdlib.h>

#include "lib.h"
#include "keyspace1.h"
#include "keyspace2.h"

#define msize2 20

// delete and search change
// spaces.h

void free_all(char ***tmp);

void free_all(char ***tmp){
  for (int i = 0; i < 5; i++){
    if(*tmp[i]){
      free(*tmp[i]);
      *tmp[i] = NULL;
    }
  }
}


int main(){
    table man;

    char *opt = NULL, *key2 = NULL, *info = NULL, *type = NULL, *ans = NULL;
    char ***free_string = calloc(5, sizeof(char **));
    free_string[0] = &opt;
    free_string[1] = &key2;
    free_string[2] = &info;
    free_string[3] = &type;
    free_string[4] = &ans;

    unsigned key1;

    int n = 1, rel;  // n for input check, rel for releases, z for file, v for vendetta
    Item com;

    key_s2 *tab_search, *p;
    float dub1, dub2;

    printf("HELLO\nI AM YOUR TABLE MAKER!\n");
    printf("I HAVE TWO KEYSPACES\n");
    printf("FIRST: UNSIGNED INTEGERS\n");
    printf("SECOND: STRINGS WITH VARIABLE LENGTH\n");
    printf("IF YOU WANT TO SEE MY OPTIONS - TYPE \'help\'\n");

    man = init_table(msize2);

    while(1){
      free_all(free_string);

      printf("\nWHAT SHELL I DO?\n");
      printf("-> ");

      opt = getStr(&n);
      if (n == -1){
        break;
      }

      if(strcmp(opt, "help") == 0){
        options();
      }
      else if(strcmp(opt, "search") == 0){

        printf("INSERT FIRST KEY: ");

        if(!getInt(&rel)){
          break;
        }

        key1 = (unsigned int)rel;

        printf("\nINSERT SECOND KEY: ");

        key2 = getStr(&n);

        if (n == -1){
          break;
        }
        else if(n == 0){
          printf("WARNING!! WRONG INPUT. CONTINUE.\n");
          continue;
        }

        printf("\n");
        n = search_item(key1, key2, man, &com);
        if(n == 0){
          printf("SEEMS THAT THERE IS NO SUCH A TYPE 1 KEY!\n");
        }
        else if(n == -1){
          printf("SEEMS THAT THERE IS NO SUCH A TYPE 2 KEY\n");
        }
        else{
          printf("THERE IS YOUR ITEM: {%s, %f, %f}\n", com.info_i, com.dub1, com.dub2);
        }
      }
      else if(strcmp(opt, "add") == 0){
        printf("INSERT FIRST KEY: ");

        if(!getInt(&rel)){
          break;
        }

        key1 = (unsigned int)rel;
        printf("\nINSERT SECOND KEY: ");

        key2 = getStr(&n);

        if (n == -1){
          break;
        }
        else if(n == 0){
          printf("WARNING!! WRONG INPUT. CONTINUE.\n");
          continue;
        }

        printf("\nINSERT INFO STRING: ");

        info = getStr(&n);

        if (n == -1){
          break;
        }
        else if(n == 0){
          printf("WARNING!! WRONG INPUT. CONTINUE.\n");
          continue;
        }

        printf("INSERT FIRST FLOAT: ");

        if(!getFloat(&dub1)){
          break;
        }

        printf("INSERT SECOND FLOAT: ");

        if(!getFloat(&dub2)){
          break;
        }
        printf("\n");


        printf("\n");

        n = add_el(key1, key2, info, &man, dub1, dub2);
        if(!n){
          printf("THERE IS ALREADY SUCH A TYPE 1 KEY\n");
        }
        else{
          printf("SUCCESSFULLY ADDED NEW ELEMENT\n");
        }
      }
      else if(strcmp(opt, "delete") == 0){
        printf("INSERT FIRST KEY: ");

        if(!getInt(&rel)){
          break;
        }

        key1 = (unsigned int)rel;
        printf("\nINSERT SECOND KEY: ");

        key2 = getStr(&n);

        if (n == -1){
          break;
        }
        else if(n == 0){
          printf("WARNING!! WRONG INPUT. CONTINUE.\n");
          continue;
        }
        printf("\n");
        del_el(key1, key2, &man);

      }
      else if(strcmp(opt, "get_one") == 0){
        printf("INSERT THE TYPE OF KEY(uns/str): ");

        type = getStr(&n);


        if (n == -1){
          break;
        }
        else if(n == 0){
          printf("WARNING!! WRONG INPUT. CONTINUE.\n");
          continue;
        }
        printf("\n");
        if (strcmp(type, "str") != 0 && strcmp(type, "uns") != 0){
          printf("WARNING! NO SUCH AN OPTION. CONTINUE\n");
          continue;
        }

        if(strcmp(type, "uns") == 0){
          printf("INSERT KEY: ");

          if(!getInt(&rel)){
            break;
          }

          key1 = (unsigned int)rel;

          printf("\n");
          n = search_uns(man, key1, &com);
          if(!n){
            printf("NO SUCH A KEY 1 FOUND\n");
          }
          else{
            printf("THERE\'S YOUR ITEM: {%s, %f, %f}", com.info_i, com.dub1, com.dub2);
          }
        }

        else if(strcmp(type, "str") == 0){
          printf("INSERT KEY: ");

          key2 = getStr(&n);

          if (n == -1){
            break;
          }
          else if(n == 0){
            printf("WARNING!! WRONG INPUT. CONTINUE.\n");
            continue;
          }

          printf("DO YOU WANT TO SEARCH FOR SPECIFIC RELEASE?(y/n): ");

          ans = getStr(&n);

          printf("\n");
          if (n == -1){
            break;
          }
          else if(n == 0){
            printf("WARNING!! WRONG INPUT. CONTINUE.\n");
            continue;
          }

          if(strcmp(ans, "y") != 0 && strcmp(ans, "n") != 0){
            printf("WARNING!! WRONG INPUT. CONTINUE.\n");
            continue;
          }

          if(strcmp(ans, "y") == 0){
            printf("INSERT RELEASE NUMBER: ");

            if (!getInt(&rel)){
              break;
            }

          }
            else{
              rel = 0;
            }
            printf("\n");


          tab_search = search_str(man, key2, rel);
          if(!tab_search){
            printf("NO SUCH A KEY 2 FOUND\n");
          }
          else{
            if(rel == 0 && tab_search->next){
              printf("YOUR ITEMS: ");
              print_keyspace_2(tab_search);

              while(tab_search){
                p = tab_search;
                tab_search = tab_search->next;
                free(p);
              }
            }
            else if(rel == 0 && !tab_search->next){
              printf("THERE\'S YOUR ITEM: ");
              printf("{%s, %f, %f}\n", tab_search->info->info_i, tab_search->info->dub1, tab_search->info->dub2);
              free(tab_search);
            }

            else{
              printf("THERE\'S YOUR ITEM: ");
              printf("{%s, %f, %f}\n", tab_search->info->info_i, tab_search->info->dub1, tab_search->info->dub2);
            }
          }
      }

    }
      else if(strcmp(opt, "del_one") == 0){
        printf("INSERT THE TYPE OF KEY(uns/str): ");

        type = getStr(&n);


        if (n == -1){
          break;
        }
        else if(n == 0){
          printf("WARNING!! WRONG INPUT. CONTINUE.\n");
          continue;
        }

        printf("\n");
        if (strcmp(type, "str") != 0 && strcmp(type, "uns") != 0){
          printf("WARNING! NO SUCH AN OPTION. CONTINUE\n");
          continue;
        }

        if(strcmp(type, "uns") == 0){
          printf("INSERT KEY: ");

          if(!getInt(&rel)){
            break;
          }

          key1 = (unsigned int)rel;
          printf("\n");
          del_uns(&man, key1);
        }
        else if(strcmp(type, "str") == 0){
          printf("INSERT KEY: ");

          key2 = getStr(&n);


          if (n == -1){
            break;
          }
          else if(n == 0){
            printf("WARNING!! WRONG INPUT. CONTINUE.\n");
            continue;
          }

          printf("DO YOU WANT TO DELETE SPECIFIC RELEASE?(y/n): \n");

          ans = getStr(&n);


          if (n == -1){
            break;
          }
          else if(n == 0){
            printf("WARNING!! WRONG INPUT. CONTINUE.\n");
            continue;
          }

          if(strcmp(ans, "y") != 0 && strcmp(ans, "n") != 0){
            printf("WARNING!! WRONG INPUT. CONTINUE.\n");
            continue;
          }

          printf("\n");

          if(strcmp(ans, "y") == 0){
            printf("INSERT RELEASE: ");

            if (!getInt(&rel)){
              break;
            }

          }
            else{
              rel = 0;
            }

          del_str(&man, key2, rel);
        }
        }
      else if(strcmp(opt, "show") == 0){
          printf("DO YOU WANT ME TO SHOW YOUR KEYSPACES?(y/n): ");

          ans = getStr(&n);


          printf("\n");
          if (n == -1){
            break;
          }
          else if(n == 0){
            printf("WARNING!! WRONG INPUT. CONTINUE.\n");
            continue;
          }

          if(strcmp(ans, "y") != 0 && strcmp(ans, "n") != 0){
            printf("WARNING!! WRONG INPUT. CONTINUE.\n");
            continue;
          }
          n = 0;
          if(strcmp(ans, "y") == 0){
             n = 1;
          }
          printf("\n");
          show_table(man, n);
        }
      else if(strcmp(opt, "exit") == 0){
          printf("GOODBYE, SEE YA!\n");
          break;
        }
      else{
          printf("I DO NOT UNDERSTAND WHAT DO YOU WANT FOR ME\n");
          printf("PLEASE TRY AGAIN OR TYPE \'HELP\'\n");
        }
    }

      free_all(free_string);
      free(free_string);
      free_table(&man);

      return 0;
    }
