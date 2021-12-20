#include <stdio.h>

struct tup {
           int number;
           long length;
};
struct tup change_num(int );
void init(int *c, struct tup *d, int n);
void print_mas(int *a,int n);
void print_tup(struct tup *a,int n);
void sortedmas(struct tup *a, int n);
void checkvv(int *a);

void checkvv(int *a){
  int n;
  n = scanf("%d", a);
  while ((n == 0)||(*a < 0)){
     if (n ==0){
       scanf("%*[^\n]");
       printf("I need number\n");
       n = scanf("%d", a);
     }
     if(*a < 0){
       scanf("%*[^\n]");
       printf("I need a natural!\n");
       n = scanf("%d", a);
     }
  }

}

void sortedmas(struct tup *a, int n){
  int i,j;
  struct tup c;
    for (i = 0; i < n - 1; i++){
      for (j = i+1; j < n; j++){
        if (a[i].length > a[j].length){
            c = a[i];
            a[i] = a[j];
            a[j] = c;
        }
      }
    }

}

void print_mas(int *a, int n){
  int i;
  for(i = 0; i < n - 1; i++){
    printf("%d ", a[i]);

  }
  printf("%d\n\n", a[i]);
}

void print_tup(struct tup *a, int n){
  int i;
  for(i = 0; i < n - 1; i++){
    printf("%d ", a[i].number);
  }
  printf("%d ", a[n - 1].number);
  printf("\n");
}

struct tup change_num(int a){
  int a1 = a % 10, i = 1, a2 = a, j = 0;
  struct tup x;

  if (a >=0 && a <=9){
    x.length = 1;
    x.number = a;
    return x;
  }


  while(a2 != 0){
      a2 /= 10;
      i *= 10;
    }

  i /= 10;
  a1 = a1 * i + (a % i / 10) * 10 + (a / i);
  x.number = a1;

  while(a1 !=0){
    j++;
    a1 /= 10;
  }

  x.length = j;

  return x;
}

void init(int *c, struct tup *d, int n){
  int a;
  for (int i = 0; i < n; i++){

    checkvv(&a);

    c[i] = a;
    d[i] = change_num(a);

    }
}

int main(){

  int n;

  printf("Insert amount of numbers: ");
  checkvv(&n);
  printf("\n");
  int c0[n];
  struct tup c1[n];

  printf("Insert a sequence of numbers\n");

  init(c0, c1, n);

  printf("\nOriginal sequence\n");
  print_mas(c0, n);

  sortedmas(c1, n);

  printf("New sequence\n");
  print_tup(c1, n);

  return 0;
}
