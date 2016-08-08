#include <stdio.h>

int main(){
  printf("Hello World!\n");
  int* integer_pointer;
  int i = 0;
  integer_pointer = &i;
  printf("memory location %p, value: %d\n", integer_pointer, *integer_pointer);
  return 0;
}
