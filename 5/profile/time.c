#include "../src/lib.h"
#define ITERS 5
grph make_1(FILE *fp,char ***lol,int  n){
  grph g;
  init_graph(&g, fp);
  int suc, k, cnt = 20000, i, gcount, vcount, a,b;
  float x, y, w;
  char **key, *le;
   srand(time(NULL));
     vcount = cnt*(10-n);
     fprintf(stdout, green "Started ADDING\n" white);
     key = calloc(vcount, sizeof(char *));
     for(i = 0; i < vcount;){
       k = rand() * rand();
       suc = 0;
       le = calloc(100, sizeof(char));
       sprintf(le,"%d", k);
       if(rand() > 0)
         x = 0.001*(rand() % 10000);
       else
         x = -0.001*(rand() % 10000);
       if(rand() > 0)
         y = 0.001*(rand() % 10000);
       else
         y = -0.001*(rand() % 10000);
       add_ver(&g, le, x, y, &suc);
       if(suc == 1){
          key[i++] = le;
          if(i>1){
            if(rand() > 0)
              add_edg(&g, key[i-1], key[i-2], 0.001*(rand() % 10000), &suc);
            else
              add_edg(&g, key[i-1], key[i-2], -0.001*(rand() % 10000), &suc);
          if(rand() > rand())
             add_edg(&g, key[i-2], key[i-1], 0.001*(rand() % 10000), &suc);
          }
       }
       else{
         free(le);
       }
     }

     gcount = vcount * (vcount - 1) / 40000;
     for(i = 0; i<gcount; ){
       a = abs((rand() * rand())) % vcount;
       b = abs((rand() * rand())) % vcount;
       w = rand()/rand();
       add_edg(&g, key[a], key[b], w, &suc);
       if(suc == 1){
         i++;
       }
    }
  *lol = key;
  return g;
 }

void time_bfs(FILE *fp){
  fprintf(stdout, green "             BFS PROFILING\n"white);

  int n = 9,suc, k, cnt = 20000,m;
  char **key;
  grph g;
  clock_t f, l;
  srand(time(NULL));
  int vcount;
  while(n-- > 0){
    m=0;
  //  printf("started adding\n");
    g = make_1(fp, &key, n);
    vcount = cnt*(10 - n);
    //printf("added all, start doing bfs\n");
    f = clock();
    for(int i = 0; i < ITERS; i++){
      k = rand() % vcount;
      bfs(&g, key[k], &suc);
      if(suc == 1){
        m++;
      }
    }

  l = clock();
  printf("Done %d bfs's\n", m);
  fprintf(stdout, blue "Test %d, num of vers: %d, num of edges; %d, time: %ld %f\n"white, 10 - n, vcount,3*(vcount-1)/2+(vcount / 40000)*(vcount-1), (l-f)/ITERS, (float)(l - f)/(CLOCKS_PER_SEC*ITERS));
  free_graph(g);
  for(int i = 0; i < 20000*(10-n); i++){
    free(key[i]);
  }
  free(key);
  }
}

void time_min_path(FILE *fp){
  fprintf(stdout, green "             MIN_PATH PROFILING\n"white);
  int n = 9,suc, k, k1, cnt = 20000, len, m;
  char **key;
  grph g;
  clock_t f, l;
  vertex **v;
  srand(time(NULL));
  int vcount;
  while(n-- > 0){
    m = 0;
  //  printf("started adding\n");
    g = make_1(fp, &key, n);
    vcount = cnt*(10 - n);
  //  printf("added all, start searching paths\n");
    f = clock();
    for(int i = 0; i < ITERS; i++){
      k = rand() % vcount;
      k1 = rand() %vcount;
      v = min_path(g, key[k], key[k1],  &suc,&len, 1);
      if(suc == 1){
        m++;
      }
      fprintf(stdout, green"%d done\n"white, i);

      free(v);
    }

  l = clock();
  printf("Found %d paths\n", m);
  fprintf(stdout, blue "Test %d, num of vers: %d, num of edges; %d, time: %ld %f\n"white, 10 - n, vcount,3*(vcount-1)/2+(vcount / 40000)*(vcount-1), (l-f)/ITERS, (float)(l - f)/(CLOCKS_PER_SEC*ITERS));
  free_graph(g);
  for(int i = 0; i < 20000*(10-n); i++){
    free(key[i]);
  }
  free(key);
  }
}

void time_min_path_v(FILE *fp){
  fprintf(stdout, green "      MIN_PATH for vers PROFILING\n"white);
  int n = 9,suc, k, k1, cnt = 20000, len, m;
  char **key;
  grph g;
  clock_t f, l;
  vertex **v;
  srand(time(NULL));
  int vcount;
  while(n-- > 0){
    m = 0;
    //printf("started adding\n");
    g = make_1(fp, &key, n);
    vcount = cnt*(10 - n);
    //printf("added all, start searching paths\n");
    f = clock();
    for(int i = 0; i < ITERS; i++){
      k = rand() % vcount;
      k1 = rand() %vcount;
      v = min_path(g, key[k], key[k1],  &suc,&len, 0);
      if(suc == 1){
        m++;
      }
      fprintf(stdout, green"%d done\n"white, i);
      free(v);
    }

  l = clock();
  printf("Found %d paths\n", m);
  fprintf(stdout, blue "Test %d, num of vers: %d, num of edges; %d, time: %ld %f\n"white, 10 - n, vcount,3*(vcount-1)/2+(vcount / 40000)*(vcount-1), (l-f)/ITERS, (float)(l - f)/(CLOCKS_PER_SEC*ITERS));
  free_graph(g);
  for(int i = 0; i < 20000*(10-n); i++){
    free(key[i]);
  }
  free(key);
  }
}


void time_res_net(FILE *fp){
  fprintf(stdout, green "        RES_NET PROFILING\n"white);
  int n = 9,suc, k, k1, cnt = 20000, m=0;
  char **key;
  grph g, g0;
  float len;
  clock_t f, l;
  srand(time(NULL));
  int vcount;
  while(n-- > 0){
    m = 0;
  //  printf("started adding\n");
    g = make_1(fp, &key, n);
    vcount = cnt*(10 - n);
  //  printf("added all, start searching paths\n");
    f = clock();
    for(int i = 0; i < ITERS; i++){
      k = rand() % vcount;
      k1 = rand() %vcount;
      g0 = res_net(g, key[k], key[k1], &len, &suc);
      if(suc ==1){
        m++;
      }
      fprintf(stdout, green"%d done\n"white, i);
      free_graph(g0);
    }

  l = clock();
  printf("Found %d flows\n", m);
  fprintf(stdout, blue "Test %d, num of vers: %d, num of edges; %d, time: %ld %f\n"white, 10 - n, vcount,3*(vcount-1)/2+(vcount / 40000)*(vcount-1), (l-f)/ITERS, (float)(l - f)/(CLOCKS_PER_SEC*ITERS));
  free_graph(g);
  for(int i = 0; i < 20000*(10-n); i++){
    free(key[i]);
  }
  free(key);
  }
}

int main(){
  FILE *fp = fopen("lol", "rb");

  time_bfs(fp);
  //time_min_path(fp);
  //time_min_path_v(fp);
  time_res_net(fp);
}
