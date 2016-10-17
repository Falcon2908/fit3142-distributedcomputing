#include <sys/types.h>
#include <sys/times.h>
#include <stdio.h>

int main(int argc, char * argv[]){
  struct tms before, after;

  times(&before);

  int i;
  for(i = 0; i < 30000; i++){
    printf("%d\n", i);
  }

  times(&after);

  // User time is the time spent by the CPU executing in user mode. E.g. adding numbers, comparing, running user-level routines
  printf("User time: %ld seconds\n", after.tms_utime - before.tms_utime);

  // The time spent by the CPU executing in kernel mode. E.g. doing system calls
  printf("System time: %ld seconds\n", after.tms_stime - before.tms_stime);

  return 0;
}
