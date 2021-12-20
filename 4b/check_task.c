#include <stdio.h>

int main(){

FILE *fp = fopen("Task", "r+b"), *fk = fopen("Task_text", "w+t");
unsigned a;

while(fread(&a, sizeof(unsigned), 1, fp)){
fprintf(fk, "%d\n", a);
}

fclose(fp);
fclose(fk);

return 0;
}
