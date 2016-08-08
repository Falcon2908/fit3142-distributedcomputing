#include <stdio.h>
#include <string.h>

// This is also fine
// int n_char(char string[]);

int n_char(char* string);

int main(int argc, char* argv[]){
  char string[50];

  strcpy(string, "Hello, World!");

  int string_length = n_char(string);
  printf("length of string: %d\n", string_length);

  return 0;
}

int n_char(char* string){
  int length = strlen(string);
  if(length > 50){
    printf("String is longer than 50 chars\n");
  }
  return length;
}
