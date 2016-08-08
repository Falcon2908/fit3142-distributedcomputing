#include <stdio.h>

int main(){

  FILE *fp;
  fp = fopen("foo.txt", "a");

  fprintf(fp, "// Sample code\n");

  char code_string[100];

  for(int i=0; i < 10; i++){
    printf("Enter code: ");
    scanf("%s", code_string);
    fprintf(fp, "%s\n", code_string);
  }
  fclose(fp);
  return 0;
}
