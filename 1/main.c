#include <stdio.h>
#include <stdlib.h>

typedef struct part{
  double *array;
  int length;
}part;


void getInt(int *a);
void getDouble(double *a);

void init(part *a, int n);

void print_matrix(part *a, int n);
void print_vec(double *a, int n);

void vec(part *a, int n, double *new);

void getInt(int *a){
  int n;
  do{
    n = scanf("%d", a);

    /* if (n < 0)
      return 0;
     */

    if (n == 0){
      printf("I need number\n");
      scanf("%*[^\n]");
    }

    if (*a < 0){
      printf("I need a natural!\n");
      scanf("%*[^\n]");
      n = 0;
    }

  } while (n == 0);
}

void getDouble(double *a){
  int n;
  do{
    n = scanf("%lf", a);

    /* if (n < 0)
      return 0;
    */

    if (n == 0){
      printf("I need number\n");
      scanf("%*[^\n]");
    }
  } while (n == 0);
}


void print_vec(double *a, int n){
  printf("Outcoming vector:\n\n");
  for(int i = 0; i < n - 1; i++){
    printf("%f ", a[i]);
  }
  printf("%f\n\n", a[n-1]);
}


void print_matrix(part *a, int n){
  printf("Original Matrix:\n\n");
  for(int i = 0; i < n; i++){
    for(int j = 0; j < a[i].length; j++){
      printf("%f ", a[i].array[j]);
    } printf("\n\n");
  }
}


void vec(part *a, int n, double *new){
  int min, sum;

  min = (a[0].length >= a[n-1].length)? a[n-1].length : a[0].length;
  sum = 0;

  for(int i = 0; i < min; i++){
    if (a[0].array[i] !=0)
        sum = (a[0].array[i] > a[n-1].array[i]) ? sum + a[0].array[i] : sum;
  }

  new[0] = sum;

  for(int i = 1; i < n; i++){
    min = (a[i].length >= a[i-1].length)? a[i-1].length : a[i].length;

    sum = 0;

    for(int j = 0; j < min; j++)
        if (a[i].array[j] !=0)
           sum = (a[i].array[j] > a[i-1].array[j]) ? sum + a[i].array[j] : sum;

    new[i] = sum;
  }

}


void init(part *a, int n){

  double temp;
  int m;

  for (int i = 0; i < n; i++){
    printf("How much elements in string %d?\n", i);

    getInt(&m);

    a[i].length = m;
    a[i].array = malloc(m * sizeof(double));

    if(m !=0)
        printf("Insert elements\n");

    for(int j = 0; j < m; j++){
      getDouble(&temp);
      a[i].array[j] = temp;
    }
  }
}

int main(){

  int n;

  printf("Insert Amount of strings: ");
  getInt(&n);
  printf("\n");

  part a[n];
  double sum_up[n];

  init(a, n);

  vec(a, n, sum_up);

  print_matrix(a, n);

  print_vec(sum_up, n);

  for (int i = 0; i < n; i++){
    free(a[i].array);
  }

  return 0;
}
