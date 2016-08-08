#include <stdio.h>

int main(int argc, char* argv[]){
  printf("Use FOR loop\n");
  for(int i = 1; i < argc; i++){
    printf("command argument %d: %s\n", i, argv[i]);
  }

  printf("\nUse WHILE loop\n");
  int counter = 1;
  while(counter < argc){
    printf("command argument %d: %s\n", counter, argv[counter]);
    counter += 1;
  }
  return 0;
}
