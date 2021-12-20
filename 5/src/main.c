#include "lib.h"

void options(){
printf("Type \'" fat "add_v" white "\'     to add new vertex\n");
printf("Type \'" fat "add_e" white "\'     to add new edge\n");

printf("Type \'" fat "del_v" white "\'     to delete a vertex\n");
printf("Type \'" fat "del_e" white "\'     to delete an edge\n");

printf("Type \'" fat "search" white "\'    to get a vertex\n");

printf("Type \'" fat "show" white "\'      to show a graph\n");
printf("Type \'" fat "save" white "\'      to save a graph\n");

printf("Type \'" fat "min_path" white "\'  to get a minimum lenghth path from one vertex to another\n");
printf("Type \'" fat "min_ver" white "\'   to get a minimum vertex's path from one vertex to another\n");

printf("Type \'" fat "res_net" white "\'   to find a redual network\n");

printf("Type \'" fat "help" white "\'      to list options\n");
printf("Type \'" fat "exit" white "\'      to finish\n");
}

int main(){
 char ***vars = (char ***)calloc(4, sizeof(char **));
 char *opt = NULL, *vname = NULL, *first = NULL, *second = NULL, *filename, *ans;
 int n = 4, e, t, suc = 0, length =0;
 float x, y, diff, w, max;
 vertex **min_p = NULL, **path;
 vars[0] = &opt;
 vars[1] = &vname;
 vars[2] = &first;
 vars[3] = &second;
 grph g, g0;
 FILE *fp;

 fprintf(stdout,blue"DO YOU WANNA DOWNLOAD GRAPH OR GEN RANDOM?(1/2)\n"white);
 ans = getStr(&e);
 if(strcmp(ans, "1")!=0 && strcmp(ans, "2")!=0){
   fprintf(stderr,red"YOU MAKE ME SAD\n"white);
   free(opt);
   exit(1);
 }
 else if(strcmp(ans, "1")==0){
   fprintf(stdout, "insert filename: ");
   filename = getStr(&e);
   if(e < 0){
     exit(1);
   }
   e = getFile(filename, &fp, 2);
   if(!e){
     if(!filename){
       free(filename);
     }
     exit(1);
   }
   init_graph(&g, fp);
 }
 else{
   fprintf(stdout,blue"How many vers do you want?\n"white);
   if(!getInt(&e)){
     fprintf(stderr, red"WRONG\n"white);
     free(opt);
     exit(1);
   }
   fp = fopen("lol", "rb");
   g = make(fp, e);
 }



 options();
 while(1){
   free_all(vars, n);
   printf("\nWhat shall i do?\n->");
   opt = getStr(&e);
   if(e < 0){
     break;
   }

   if(strcmp(opt, "add_v") == 0){
      fprintf(stdout, "Input new vertex's name: ");
      vname = getStr(&e);
      if(e == 0){
        fprintf(stdout, blue "Wrong input. Continue\n" white);
        continue;
      }else if(e < 0){
        break;
      }
      fprintf(stdout, "Input x coord: ");
      if(!getFloat(&x)){
        break;
      }
      fprintf(stdout, "Input y coord: ");
      if(!getFloat(&y)){
        break;
      }

      t = clock();
      add_ver(&g, vname, x, y, &suc);
      diff = (float)(clock() - t) / CLOCKS_PER_SEC;
      if(suc == -1){
        fprintf(stderr, red "Seems that there's already a vertex with this name or coords\n" white);
      }
      else if(suc == 1){
        fprintf(stdout, green "Successfully added vertex %s with coords (%f, %f)\n", vname, x, y);
      }
      else if(suc == 0){
        fprintf(stderr, red "The table is full ha\n" white);
      }
      else if(suc == -2){
        fprintf(stderr, blue "Extreme collision, please choose another name\n" white);
      }
      timer(diff);
   }
   else if(strcmp(opt, "add_e") == 0){
     fprintf(stdout, "Input beginning vertex: ");
     first = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue\n" white);
       continue;
     }else if(e < 0){
       break;
     }
     fprintf(stdout, "Input ending vertex: ");
     second = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue" white);
       continue;
     }else if(e < 0){
       break;
     }

     fprintf(stdout, "Input weight: ");
     if(!getFloat(&w)){
       break;
     }

     t = clock();
     add_edg(&g, first, second, w, &suc);
     diff = (float)(clock() - t) / CLOCKS_PER_SEC;
     if(suc == -1){
       fprintf(stderr, red "Seems that there's no such a vertex %s or %s\n" white, first, second);
     }
     else if(suc == 0){
       fprintf(stderr, red "Seems that there's already an edge between %s and %s\n" white, first, second);
     }
     else{
       fprintf(stdout, green "Successfully added new edge between %s and %s\n" white, first, second);
     }
     timer(diff);
   }
   else if(strcmp(opt, "del_v") == 0){
     fprintf(stdout, "Input vertex: ");
     first = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue\n" white);
       continue;
     }else if(e < 0){
       break;
     }

     t = clock();
     del_ver(&g,first, &suc);
     diff = (float)(clock() - t) / CLOCKS_PER_SEC;
     if(!suc){
       fprintf(stderr, red "Seems that there's no vertex with this name\n" white);
     }
     else{
       fprintf(stdout, green "Successfully deleted vertex %s\n" white, first);
     }
     timer(diff);
   }
   else if(strcmp(opt, "del_e") == 0){
     fprintf(stdout, "Input beginning vertex: ");
     first = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue\n" white);
       continue;
     }else if(e < 0){
       break;
     }
     fprintf(stdout, "Input ending vertex: ");
     second = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue" white);
       continue;
     }else if(e < 0){
       break;
     }

     t = clock();
     del_edg(&g, first,second , &suc);
     diff = (float)(clock() - t) / CLOCKS_PER_SEC;
     if(suc == 0){
       fprintf(stderr, red "Seems that there's no such an edge\n" white);
     }
     else{
       fprintf(stdout, green "Successfully deleted edge between %s and %s\n" white, first, second);
     }
     timer(diff);
   }
   else if(strcmp(opt, "show")==0){
     if(!g.count){
       fprintf(stderr, blue "You got empty graph\n" white);
     }
     else{
       show_graph(g);
     }
   }
   else if(strcmp(opt, "save") == 0){
     save_1(g, 0, min_p, 0);
     save(g);
   }
   else if(strcmp(opt, "search") == 0){
     fprintf(stdout, "Input vertex to search: ");
     first = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue\n" white);
       continue;
     }else if(e < 0){
       break;
     }
     fprintf(stdout, "Input vertex to start with: ");
     second = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue" white);
       continue;
     }else if(e < 0){
       break;
     }

     t = clock();
     path = bfs_path(g, second,first , &suc);
     diff = (float)(clock() - t) / CLOCKS_PER_SEC;
     if(suc == 0){
       fprintf(stderr, red "Seems that there's no such vertex %s or %s\n" white, first, second);
     }
     else if(suc == -1){
       fprintf(stderr, red "Seems that there's no path between %s and %s\n" white, first, second);
     }
     else{
       length = path[0]->dist + 1;
       fprintf(stdout, blue "Here's your path of length %d\n" white, length-1);
       fprintf(stdout, pink "%s: (%f,%f)\n", path[length-1]->name,path[length-1]->x, path[length-1]->y);
       fprintf(stdout,      "         |          %f\n" white, -path[length-1]->dist + path[length-2]->dist);
       for(int i = length - 2; i > 0; i--){
         fprintf(stdout, blue "%s :(%f,%f)\n", path[i]->name,path[i]->x, path[i]->y);
         fprintf(stdout,    "         |          %f\n" white, -path[i]->dist + path[i-1]->dist);
       }
       fprintf(stdout, pink "%s: (%f,%f)"white, path[0]->name,path[0]->x, path[0]->y);
       save_1(g, 1, path, length);
       free(path);
     }
     timer(diff);
   }
   else if(strcmp(opt, "min_path") == 0){
     fprintf(stdout, "Input beginning vertex: ");
     first = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue\n" white);
       continue;
     }else if(e < 0){
       break;
     }
     fprintf(stdout, "Input ending vertex: ");
     second = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue" white);
       continue;
     }else if(e < 0){
       break;
     }

     t = clock();
     min_p = min_path(g, first, second, &suc, &length, 1);
     diff = (float)(clock() - t) / CLOCKS_PER_SEC;
     if(suc == 0){
       fprintf(stderr, red "Seems that there's no such a vertex %s or %s\n" white, first, second);
     }
     else if(suc == -2){
       fprintf(stderr, red "There is no path between %s and %s\n" white, first, second);
     }
     else if(suc == -3){
       fprintf(stderr, red "There are negative cycles between %s and %s\n" white, first, second);
     }
     else{
       fprintf(stdout, blue "Here's your path of length %f\n" white, min_p[0]->dist);
       fprintf(stdout, pink "%s: (%f,%f)\n", min_p[length-1]->name,min_p[length-1]->x, min_p[length-1]->y);
       fprintf(stdout,      "         |          %f\n" white, -min_p[length-1]->dist + min_p[length-2]->dist);
       for(int i = length - 2; i > 0; i--){
         fprintf(stdout, blue "%s :(%f,%f)\n", min_p[i]->name,min_p[i]->x, min_p[i]->y);
         fprintf(stdout,    "         |          %f\n" white, -min_p[i]->dist + min_p[i-1]->dist);
       }
       fprintf(stdout, pink "%s: (%f,%f)\n"white, min_p[0]->name,min_p[0]->x, min_p[0]->y);
       save_1(g, 1, min_p, length);
       free(min_p);
     }
     timer(diff);
   }
   else if(strcmp(opt, "min_ver") == 0){
     fprintf(stdout, "Input beginning vertex: ");
     first = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue\n" white);
       continue;
     }else if(e < 0){
       break;
     }
     fprintf(stdout, "Input ending vertex: ");
     second = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue" white);
       continue;
     }else if(e < 0){
       break;
     }

     t = clock();
     min_p = min_path(g, first, second, &suc, &length, 0);
     diff = (float)(clock() - t) / CLOCKS_PER_SEC;
     if(suc == 0){
       fprintf(stderr, red "Seems that there's no such a vertex %s or %s\n" white, first, second);
     }
     else if(suc == -2){
       fprintf(stderr, red "There is no path between %s and %s\n" white, first, second);
     }
     else if(suc == -3){
       fprintf(stderr, red "There are negative cycles between %s and %s\n" white, first, second);
     }
     else{
       fprintf(stdout, blue "Here's your path of length %f\n" white, min_p[0]->dist);
       fprintf(stdout, pink "%s: (%f,%f)\n", min_p[length-1]->name,min_p[length-1]->x, min_p[length-1]->y);
       fprintf(stdout,      "         | \n" white);
       for(int i = length - 2; i > 0; i--){
         fprintf(stdout, blue "%s :(%f,%f)\n", min_p[i]->name,min_p[i]->x, min_p[i]->y);
         fprintf(stdout,    "         |\n" white);
       }
       fprintf(stdout, pink "%s: (%f,%f)\n"white, min_p[0]->name,min_p[0]->x, min_p[0]->y);
       save_1(g, 1, min_p, length);
       free(min_p);
     }
     timer(diff);
   }
   else if(strcmp(opt, "res_net") == 0){
     fprintf(stdout, "Input source vertex: ");
     first = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue\n" white);
       continue;
     }else if(e < 0){
       break;
     }
     fprintf(stdout, "Input sink vertex: ");
     second = getStr(&e);
     if(e == 0){
       fprintf(stdout, blue "Wrong input. Continue" white);
       continue;
     }else if(e < 0){
       break;
     }
     t = clock();
     g0 = res_net(g, first, second, &max, &suc);
     diff = (float)(clock() - t) / CLOCKS_PER_SEC;
     if(suc == -1){
       fprintf(stderr, red "THere is no path from %s to %s\n"white, first, second);
     }
     else if(suc == 0){
       fprintf(stderr, red "THere is no vertex %s or %s\n"white, first, second);
     }
     else{
       fprintf(stdout, pink "\n                      MAX FLOW: %f\n\n" white, max);
     }
     //show_graph(g0);
     free_graph(g0);
     timer(diff);

   }
   else if(strcmp(opt, "help") == 0){
     options();
   }
   else if(strcmp(opt, "exit") == 0){
     fprintf(stdout, "Goodbye, see ya.\n");
     break;
   }
   else if(strcmp(opt, "extra") == 0){
    printf("input first coord x: ");
    getFloat(&x);
    printf("input first coord y: ");
    getFloat(&y);
    first = get_by_coords(g, x, y, &suc);
    if(!suc){
      fprintf(stderr, red "Wrong coords. Continue.\n"white);
      continue;
    }
    printf("Name: %s\n", first);
    printf("input second coord x: ");
    getFloat(&x);
    printf("input second coord y: ");
    getFloat(&y);
    second = get_by_coords(g, x, y, &suc);
    if(!suc){
      fprintf(stderr, red "Wrong coords. Continue.\n"white);
      continue;
    }
    printf("Name: %s\n", second);

    t = clock();
    min_p = min_path(g, first, second, &suc, &length, 1);
    diff = (float)(clock() - t) / CLOCKS_PER_SEC;
    if(suc == 0){
      fprintf(stderr, red "Seems that there's no such a vertex %s or %s\n" white, first, second);
    }
    else if(suc == -2){
      fprintf(stderr, red "There is no path between %s and %s\n" white, first, second);
    }
    else if(suc == -3){
      fprintf(stderr, red "There are negative cycles between %s and %s\n" white, first, second);
    }
    else{
      fprintf(stdout, blue "Here's your path of length %f\n" white, min_p[0]->dist);
      fprintf(stdout, pink "%s: (%f,%f)\n", min_p[length-1]->name,min_p[length-1]->x, min_p[length-1]->y);
      fprintf(stdout,      "         |          %f\n" white, -min_p[length-1]->dist + min_p[length-2]->dist);
      for(int i = length - 2; i > 0; i--){
        fprintf(stdout, blue "%s :(%f,%f)\n", min_p[i]->name,min_p[i]->x, min_p[i]->y);
        fprintf(stdout,    "         |          %f\n" white, -min_p[i]->dist + min_p[i-1]->dist);
      }
      fprintf(stdout, pink "%s: (%f,%f)\n"white, min_p[0]->name,min_p[0]->x, min_p[0]->y);
      save_1(g, 1, min_p, length);
      free(min_p);
    }
    timer(diff);

   }
   else{
     fprintf(stderr, blue "Sorry, i do not understand you\n Repeat, please, or type \'help\'\n" white);
   }
 }
free_all(vars, n);
save(g);
free_graph(g);
if(strcmp(ans, "1")==0)
free(filename);
free(ans);
free(vars);
return 0;
}
