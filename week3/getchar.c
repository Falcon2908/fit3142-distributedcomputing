#include <stdio.h>

int main(){

  int char_counter = 0, line_counter = 0;
  char c;
  while((c = getchar()) != EOF){
    char_counter++;
    if(c == '\n')
      line_counter++;
  }
  printf("%d\n", char_counter);
  printf("%d\n", line_counter);
  return 0;
}
