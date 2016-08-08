#include <stdio.h>
#include "addition.h"
int main(){
  printf("Hello World!\n");
  int* integer_pointer;
  int i = 0;
  integer_pointer = &i;
  printf("memory location %p, value: %d\n", integer_pointer, *integer_pointer);
  int result = add_two_numbers(2,3);
  printf("result of addition: %d\n", result);
  return 0;
}
