#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define STDIN 0

void print_numbers(int * numbers){
  for(int i = 0; i< 3; i++){
    printf("%d\n", numbers[i]);
  }
}

int main(void){
  struct timeval tv;
  fd_set readfds;

  tv.tv_sec = 1;
  tv.tv_usec = 500000;

  FD_ZERO(&readfds);
  FD_SET(STDIN, &readfds);

  select(STDIN+1, &readfds, NULL, NULL, NULL);

  if(FD_ISSET(STDIN, &readfds))
    printf("A key was pressed!\n");
  else
    printf("Timed out\n");

  int numbers [] = {1, 54, 23};
  print_numbers(numbers);
  return 0;
}
