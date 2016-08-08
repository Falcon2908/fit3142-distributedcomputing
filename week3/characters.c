#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

  char my_string[] = "My name is Arvin.";
  printf("%s\n", my_string);
  my_string[2] = 'z';
  printf("%s\n", my_string);

  char* other_string = (char*)malloc(100 * sizeof(char));
  char third_string[30] = "I live in Melbourne";
  strcpy(other_string, third_string);
  other_string[3] = '|';
  printf("%s\n", other_string);
  printf("%s\n", third_string);
  free(other_string);
  printf("After getting freed: %s\n", other_string);
  
  return 0;
}
