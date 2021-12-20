#include "lib.h"
int hash(char *key){
  int hash = 7;
  for (int i = 0; i < (int)strlen(key); i++){
    hash = (hash*STEP + (int)key[i]) % H_SIZE;
  }
  (hash < 0) ? (hash = -hash) : hash;
  return hash;
}

htab h_init(){
  htab t;
  t.space = (vertex *)calloc(H_SIZE, sizeof(vertex));
  t.size = 0;
  t.full = H_SIZE;
  return t;
}

int h_find(char *key, htab t){
  int k = hash(key);
  int k0 = k;
  while(1){
    if(!t.space[k].name){
      return -1;
    }
    else if(strcmp(key, t.space[k].name) != 0){
      k = (k+SKIP) % H_SIZE;
      if(k == k0){
        return -1;
      }
    }
    else{
      break;
    }
  }
  return k;
}

que init_que(int n){
   que q;
   q.frnt = 0;
   q.rear = -1;
   q.pos = (int *)calloc(n, sizeof(int));
   return q;
}

void insert_q(que *q, int x){
  q->rear++;
  q->pos[q->rear] = x;
}

int isempty(que q){
  if(q.rear < q.frnt){
     return 1;
  }
  return 0;
}

int pop_q(que *q){
  int h, x;
  if(isempty(*q)){
    return -1;
  }
  x = q->pos[q->frnt];
  for(h = q->frnt; h < q->rear; h++){
    q->pos[h] = q->pos[h+1];
  }
  q->rear--;
  return x;
}

void init_graph(grph *g, FILE *fp){
  int n, len, e, pos;
  list *tmp;
  e = fread(&n, 1, sizeof(int), fp);

  if(!e){
    g->vers = h_init();
    g->count = 0;
    return;
  }

  g->vers.full = n;
  fread(&n, 1, sizeof(int), fp);
  g->count = n;
  g->vers.size = n;
  vertex *v = (vertex *)calloc(g->vers.full, sizeof(vertex));
  list **l = (list **)calloc(g->vers.full, sizeof(list *));
  for(int i = 0; i < n; i++){
    fread(&pos, 1, sizeof(int), fp);
    fread(&len, 1, sizeof(int), fp);
    v[pos].name = (char *)calloc(len+1, sizeof(char));
    fread(v[pos].name, len, sizeof(char), fp);
    fread(&(v[pos].x), 1, sizeof(float), fp);
    fread(&(v[pos].y), 1, sizeof(float), fp);
    v[pos].next = NULL;
    g->vers.size = g->vers.size + 1;
  }
  while(fread(&n, 1, sizeof(int), fp)){
    tmp = (list *)calloc(1, sizeof(list));
    fread(&tmp->me, 1, sizeof(int), fp);
    fread(&tmp->w, 1, sizeof(float), fp);
    if(!l[n]){
      v[n].next = tmp;
      l[n] = tmp;
      l[n]->next = NULL;
    }
    else{
      l[n]->next = tmp;
      l[n] = l[n]->next;
      l[n]->next = NULL;
    }
  }
  g->vers.space = v;
  free(l);
  fclose(fp);
}

void add_ver(grph *g, char *name, float x, float y, int *suc){
  htab t = g->vers;

  if(t.size == t.full){
    *suc = 0;
    return;
  }

  int k = hash(name);
  int k0 = k;
  while(t.space[k].name){
    if(strcmp(name, t.space[k].name) == 0 || (t.space[k].x == x && t.space[k].y == y)){
      *suc = -1;
      return;
    }
    else if(t.space[k].name)
      k = (k+SKIP) % H_SIZE;

    if(k == k0){
      *suc = -2;
      return;
    }
  }

  t.space[k].name = (char *)calloc(strlen(name)+1, sizeof(char));
  strcat(t.space[k].name, name);

  t.space[k].x = x;
  t.space[k].y = y;
  t.space[k].next = NULL;
  t.size ++;
  g->count = g->count + 1;
  *suc = 1;
} // O(1)

void add_edg(grph *g, char *first, char *second, float w, int *suc){
  *suc = 0;
  int h1 = h_find(first, g->vers);
  int h2 = h_find(second, g->vers);

  if(h1 < 0 || h2 < 0){
    *suc = -1;
    return;
  }

  list *tmp = g->vers.space[h1].next;

  while(tmp){
    if(strcmp(second, g->vers.space[tmp->me].name) == 0){
      *suc = 0;
      return;
    }
    tmp = tmp->next;
  }
  *suc = 1;
  tmp = (list *)calloc(1, sizeof(list));
  tmp->next = g->vers.space[h1].next;
  tmp->w = w;
  tmp->me = h2;
  g->vers.space[h1].next = tmp;
} // O(|E|)

void del_ver(grph *g, char *name, int *suc){
  list *tmp, *p;
  int h1 = h_find(name, g->vers);
  if(h1 < 0){
    *suc = 0;
    return;
  }
  tmp = g->vers.space[h1].next;
  g->vers.space[h1].next = NULL;
  while(tmp){
    p = tmp;
    tmp = tmp->next;
    free(p);
  }
  for(int i = 0; i < H_SIZE; i++){
    if(!g->vers.space[i].name || !g->vers.space[i].next){
      continue;
    }
    tmp = g->vers.space[i].next;
    if(tmp->me == h1){
      g->vers.space[i].next = tmp->next;
      free(tmp);
    }
    else{
      while(tmp->next){
        if(tmp->next->me == h1){
          p = tmp->next;
          tmp->next = p->next;
          free(p);
          break;
        }
        tmp = tmp->next;
      }
    }

  }

  *suc = 1;
  free(g->vers.space[h1].name);
  g->vers.space[h1].x = 0;
  g->vers.space[h1].y = 0;
  g->vers.space[h1].next = NULL;
  g->vers.space[h1].name = NULL;
  g->count = g->count - 1;
  g->vers.size --;

} // O(|V|+|E|)

void del_edg(grph *g, char *first, char *second, int *suc){
    list *tmp, *p;

    int h1 = h_find(first, g->vers);
    int h2 = h_find(second, g->vers);

    if(h1 < 0 || h2 < 0){
      *suc = 0;
      return;
    }

    tmp = g->vers.space[h1].next;
    if(strcmp(g->vers.space[tmp->me].name, second) == 0){
      g->vers.space[h1].next = tmp->next;
      free(tmp);
      *suc = 1;
      return;
    }

    while(tmp->next){
      if(strcmp(g->vers.space[tmp->next->me].name, second) == 0){
         p = tmp->next;
         tmp->next = p->next;
         free(p);
         *suc = 1;
         return;
      }
      tmp = tmp->next;
    }

  *suc = 0;
  return;

} // O(|E|)

void bfs(grph *g, char *first , int *suc){
  int h1 = h_find(first, g->vers);
  int x;
  list *tmp;

  if(h1 < 0){
    *suc = 0;
    return;
  }
  for(int i = 0; i < H_SIZE; i++){
    if(g->vers.space[i].name){
      g->vers.space[i].disc = 0;
      g->vers.space[i].dist = INF;
      g->vers.space[i].pred = -1;
    }
  }
  g->vers.space[h1].disc = 1;
  g->vers.space[h1].dist = 0;
  g->vers.space[h1].pred = -2;

  que q = init_que(g->count);
  insert_q(&q, h1);

  while(!isempty(q)){
    x = pop_q(&q);
    tmp = g->vers.space[x].next;
    while(tmp){
      if(g->vers.space[tmp->me].disc == 0 && (tmp->w - tmp->flow) != 0.0){     // IMPOrtant
        g->vers.space[tmp->me].disc = 1;
        g->vers.space[tmp->me].dist = g->vers.space[x].dist + 1;
        g->vers.space[tmp->me].pred = x;
        insert_q(&q, tmp->me);
      }
      tmp = tmp->next;
    }
    g->vers.space[x].disc = 2;
  }
  free(q.pos);
  *suc = 1;
} //O(2*|V|+|E|)

vertex ** bfs_path(grph g, char *first ,char *second, int *suc){
  int tab = h_find(second, g.vers);
  int my;
  bfs(&g, first, &my);
  if(tab < 0 || !my){
    *suc = 0;
    return NULL;
  }
  vertex **ans = (vertex **)calloc(g.count, sizeof(vertex *));

  if(strcmp(first, second) == 0){
    ans[0] = &g.vers.space[tab];
    ans[1] = &g.vers.space[tab];
    g.vers.space[tab].pred = tab;
    *suc =1;
    g.vers.space[tab].dist = 1;
    return ans;

  }

  my = 0;
  while(strcmp(first, g.vers.space[tab].name) != 0){
    ans[my++] = &(g.vers.space[tab]);
    tab = g.vers.space[tab].pred;
    if(tab == -1 || g.vers.space[tab].dist == INF){
      *suc = -1;
      free(ans);
      return NULL;
    }
  }
  ans[my++] = &(g.vers.space[tab]);
  *suc = 1;
  return ans;
}//O(2|V|+|E|)

vertex ** min_path(grph g, char *first,char *  second, int *suc, int *len, int c){
  int h1 = h_find(first, g.vers), h2 = h_find(second, g.vers),w, k = 0, end = 0;
  list *tmp;
  if(h1 < 0 || h2 < 0){
    *suc = 0;
    return NULL;
  }
  *suc = 1;

  vertex **distance = (vertex **)calloc(g.count, sizeof(vertex *));

  if(strcmp(first, second) == 0){
    distance[0] = &g.vers.space[h1];
    distance[1] = &g.vers.space[h1];
    g.vers.space[h1].pred = h1;
    *len = 2;
    *suc = 1;
    g.vers.space[h1].dist = 0;
    return distance;

  }

  for(int i = 0; i < g.vers.full; i++){  //inits
    if(g.vers.space[i].name){
      g.vers.space[i].dist = INF;
      distance[k++] = &(g.vers.space[i]);
      g.vers.space[i].pred = -1;
    }
  }
  g.vers.space[h1].dist = 0;
  g.vers.space[h1].pred = -2;
  for(int i = 0; i < g.count; i++){ //main
    for(int j = 0; j < g.count; j++){
        tmp = distance[j]->next;
        while(tmp){
          (c == 0) ? (w = 1) : (w = tmp->w);
          if(distance[j]->dist + w < g.vers.space[tmp->me].dist){
            g.vers.space[tmp->me].dist = distance[j]->dist + w;
            end = h_find(distance[j]->name, g.vers);
            g.vers.space[tmp->me].pred = end;
            end = 1;
          }
          tmp = tmp->next;
        }
    }
    if(!end){
      end = i;
      break;
    }
    (i == g.count - 1) ? (end = i) : (end = 0);  // neg cycles
  }

  if(end == g.count - 1){ // neg cycles
    *suc = -3;
    free(distance);
    return NULL;
  }

  k = 0;
  vertex *v = &(g.vers.space[h2]);
  while(v->dist != INF && v->pred != -1){ //rebuilding path
    if(strcmp(v->name, first) == 0){
      distance[k++] = v;
      *len = k;
      *suc = 1;
      return distance;
    }

    distance[k++] = v;
    v = &(g.vers.space[v->pred]);
  }

  free(distance); //nope
  *suc = -2;
  return NULL;
} //O(|V| * |E| + |V|**2)

grph cpy_graph(grph g){
  grph g0;
  list *tmp, *tmp0, *p;
  g0.count = g.count;
  g0.vers = h_init();
  g0.vers.size = g.count;
  g0.vers.full = g.vers.full;
  for(int i = 0; i < g.vers.full; i++){
    if(g.vers.space[i].name){
      g0.vers.space[i].name = (char *)calloc(strlen(g.vers.space[i].name)+1, sizeof(char));
      sprintf(g0.vers.space[i].name, "%s", g.vers.space[i].name);
      g0.vers.space[i].next = NULL;
      g0.vers.space[i].x = g.vers.space[i].x;
      g0.vers.space[i].y = g.vers.space[i].y;
      tmp = g.vers.space[i].next;
      if(tmp){
        tmp0 = (list *)calloc(1, sizeof(list));
        (tmp->w < 0) ? (tmp0->w = -tmp->w) : (tmp0->w = tmp->w);
        tmp0->me = tmp->me;
        tmp0->next = NULL;
        tmp->flow = 0;
        g0.vers.space[i].next = tmp0;
        tmp = tmp->next;
        p = tmp0;
      }
      while(tmp){
        tmp0 = (list *)calloc(1, sizeof(list));
        (tmp->w < 0) ? (tmp0->w = -tmp->w) : (tmp0->w = tmp->w);
        tmp0->me = tmp->me;
        tmp->flow = 0;
        tmp0->next = NULL;
        tmp = tmp->next;
        p->next = tmp0;
        p = tmp0;
      }
    }
  }
  return g0;
}

float min_cf(grph g, vertex **path){
  int n = path[0]->dist + 1;
  list *tmp = path[n-1]->next;
  char *cur = path[n-2]->name;
  while(tmp){
    if(strcmp(cur, g.vers.space[tmp->me].name) == 0){
      break;
    }
    tmp = tmp->next;
  }
  float min = tmp->w - tmp->flow, k;
  for(int i = n-2; i>0; i--){
    tmp = path[i]->next;
    cur = path[i-1]->name;
    while(tmp){
      if(strcmp(cur, g.vers.space[tmp->me].name) == 0){
        break;
      }
      tmp = tmp->next;
    }
    k = tmp->w - tmp->flow;
    if(k < min){
      min = k;
    }
  }
  return min;
}//O(|E|+|V|)

void add_or_rewrite_edg(grph *g,float cf, vertex **path){
  int n = path[0]->dist+1, suc;
  list *tmp;
  float flo, w;
  for(int i = n-1; i > 0; i--){
    tmp = path[i]->next;
    while(tmp){
      if(strcmp(path[i-1]->name, g->vers.space[tmp->me].name)==0){
        break;
      }
      tmp = tmp->next;
    }
    tmp->flow = tmp->flow + cf;
    flo = tmp->flow;
    w = tmp->w;
    tmp = path[i-1]->next;
    suc = 0;
    while(tmp){
      if(strcmp(path[i]->name, g->vers.space[tmp->me].name)==0){
        suc = 1;
        break;
      }
      tmp = tmp->next;
    }

    if(!suc){
      tmp = (list *)calloc(1, sizeof(list));
      tmp->next = path[i-1]->next;
      path[i-1]->next = tmp;
      tmp->w = w;
      tmp->res_n = 1;
      tmp->me = h_find(path[i]->name, g->vers);
    }

    tmp->flow = tmp->w - flo;
  }
}  //O(|V|+2|E|)

grph res_net(grph g, char *first, char *second, float *max, int *suc){
  *max = 0;
  grph g0 = cpy_graph(g); //O(|V|+|E|)
  int s, r=0;
  float cmin;
  vertex **path = bfs_path(g0, first, second, &s); //maybe should be done by min_path
  if(s == 0 || s == -1){
    *suc =s;
    free(path);
    return g0;
  }

  while(s == 1){
    cmin = min_cf(g0, path);
    add_or_rewrite_edg(&g0, cmin, path);
    save_1(g0, r++, path, path[0]->dist+1); ///////////////////////////////////////////////////
    free(path);
    path = bfs_path(g0, first, second, &s);
  }

  list *tmp, *p;
  for(int i = 0; i < H_SIZE; i++){
    if(g0.vers.space[i].name){
      tmp = g0.vers.space[i].next;
      if(tmp){
        if(tmp->res_n == 1){
          g0.vers.space[i].next = tmp->next;
          free(tmp);
        }
        else{
          while(tmp->next){
            if(tmp->next->res_n == 1){
              p = tmp->next;
              tmp->next = p->next;
              free(p);
              break;
            }
          tmp = tmp->next;
          }
        }
      }
    }
  }

int h1 = h_find(first, g0.vers);
tmp = g0.vers.space[h1].next;
while(tmp){
  *max = *max + tmp->flow;
  tmp = tmp->next;
}
*suc = 1;
return g0;
}//O(|V|*|E|+|V|**2)

void show_graph(grph g){
  list *tmp;
  fprintf(stdout, un "CURRENT GRAPH SIZE: " white  fat "%d" white, g.count);
  printf("\n");
  for(int i = 0; i < H_SIZE; i++){
    if(!g.vers.space[i].name){
      continue;
    }
    tmp = g.vers.space[i].next;
    fprintf(stdout, pink "%s value: (%f, %f)" white, g.vers.space[i].name, g.vers.space[i].x, g.vers.space[i].y);
    while(tmp){
       fprintf(stdout, blue " --- %s weight: %f" white, g.vers.space[tmp->me].name, tmp->w);
       tmp = tmp->next;
    }
    printf("\n");
  }
}  // O(|V|+|E|)

void free_graph(grph g){
  vertex *v = g.vers.space;
  int n = g.vers.full;
  list *tmp, *p;
  for(int i = 0; i < n; i++){
    tmp = v[i].next;
    while(tmp){
      p = tmp;
      tmp = tmp->next;
      free(p);
    }
    if(v[i].name){
      free(v[i].name);
    }
  }
  free(g.vers.space);
}  // O(|V|+|E|)

void save(grph g){
  int n = H_SIZE, len;

  vertex *v = g.vers.space;
  char *name;
  list *tmp;
  float a, b;
  name = (char *)calloc(100, sizeof(char));
  sprintf(name, "%d_graph", g.count);
  FILE *fp;
  getFile(name, &fp, 0);

  fwrite(&n, 1, sizeof(int), fp);
  fwrite(&(g.count), 1, sizeof(int), fp);
  for(int i = 0; i < n; i++){
    if(!v[i].name){
      continue;
    }
    len = strlen(v[i].name);
    fwrite(&i, 1, sizeof(int), fp);
    fwrite(&len, 1, sizeof(int), fp);
    fwrite(v[i].name, len, sizeof(char), fp);
    a =  v[i].x;
    b= v[i].y;
    fwrite(&a, 1, sizeof(float), fp);
    fwrite(&b, 1, sizeof(float), fp);
  }

  for(int i = 0; i < n; i++){
    if(!v[i].name){
      continue;
    }
    tmp = v[i].next;
    while(tmp){
      fwrite(&i, 1, sizeof(int), fp);
      fwrite(&tmp->me, 1, sizeof(int), fp);
      fwrite(&tmp->w, 1, sizeof(float), fp);
      tmp = tmp->next;
    }
  }
  fclose(fp);
  free(name);
}

void save_1(grph g, int o, vertex **path, int rel){
  vertex *v = g.vers.space;
  int n = H_SIZE;
  float minx = 60000, miny = 60000, maxx = -60000, maxy = -60000;
  char *name;
  list *tmp;
  name = (char *)calloc(100, sizeof(char));
  sprintf(name, "%d_%d_graph_txt", g.count, o);
  FILE *fp;
  getFile(name, &fp, 1);

  fprintf(fp, "[%d, ", g.count);
  for(int i = 0; i < n; i++){
    if(v[i].name == NULL){
      continue;
    }

    if(v[i].x > maxx){
      maxx = v[i].x;
    }
    if(v[i].y > maxy){
      maxy = v[i].y;
    }
    if(v[i].x < minx){
      minx = v[i].x;
    }
    if(v[i].y < miny){
      miny = v[i].y;
    }
    fprintf(fp,"[\"%s\", %f, %f, %d],", v[i].name, v[i].x, v[i].y, i);
  }

  for(int i = 0; i < n; i++){
    if(v[i].name == NULL){
      continue;
    }
    tmp = v[i].next;
    while(tmp){
      fprintf(fp, "[%d, %d, %f, %f], ",i, tmp->me, tmp->flow, tmp->w);
      //fprintf(fp, "[%d, %d, %f], ",i, tmp->me, tmp->w);
      tmp = tmp->next;
    }

  }
  fprintf(fp, "[%f, %f, %f, %f, 0]", minx,miny,maxx,maxy);
  if(rel){
    fprintf(fp, ",[[%d, %d],", h_find(path[rel-1]->name, g.vers), h_find(path[rel-2]->name, g.vers));
    for(int i = rel - 2; i>1; i--){
      fprintf(fp, "[%d, %d],", h_find(path[i]->name, g.vers), h_find(path[i-1]->name, g.vers));
    }
    fprintf(fp, "[%d, %d]], 1", h_find(path[1]->name, g.vers), h_find(path[0]->name, g.vers));
  }
  else{
    fprintf(fp, ",0");
  }
  fprintf(fp, "]");

  fclose(fp);
  free(name);
}

char * get_by_coords(grph g,float x,float y,int *suc){
  float a,b, ax, by, ap = 100, bp = 100;
  int s = 0, k;
  for(int i = 0; i < g.vers.full; i++){
    if(g.vers.space[i].name){
      a = g.vers.space[i].x - x;
      b = g.vers.space[i].y - y;
      (a < 0) ? (a = -a) : a;
      (b < 0) ? (b = -b) : b;

      if(a < 100  && b < 100  && a < ap && b < bp){
        ap = a;
        bp = b;
        ax = g.vers.space[i].x;
        by = g.vers.space[i].y;
        s = 1;
        k = i;
      }
      if(a == 0 && b == 0){
        s = 1;
        k = i;
        break;
      }
    }
  }
  *suc = s;
  if(s){
    char *lol = (char *)calloc(strlen(g.vers.space[k].name)+1, sizeof(char));
    strcat(lol, g.vers.space[k].name);
    return lol;
  }
  return NULL;
}


grph make(FILE *fp, int  n){
  grph g;
  init_graph(&g, fp);
  int suc, k,i, gcount, vcount, a,b;
  float x, y, w;
  char **key, *le;
   srand(time(NULL));
     vcount = n;
     key = calloc(n, sizeof(char*));
     fprintf(stdout, green "Started ADDING\n" white);
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

     gcount = vcount * (vcount - 1) / 10;
     for(i = 0; i<gcount; ){
       a = abs((rand() * rand())) % vcount;
       b = abs((rand() * rand())) % vcount;
       w = rand()/rand();
       add_edg(&g, key[a], key[b], w, &suc);
       if(suc == 1){
         i++;
       }
    }

for(int i = 0; i<n;i++){
  free(key[i]);
}
free(key);
return g;
 }
