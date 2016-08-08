#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PASS_MARK 50
int main(int argc, char* argv[]){
  printf("MONASH SCHOOL OF IT\n");
  printf("The pass mark is: %d\n", PASS_MARK);
  int num_students = 100;
  int students[num_students];
  srand ( time(NULL) );
  for(int i = 0; i < num_students; i++){
    students[i] = rand() % 100;
  }

  printf("\n--- IF STATEMENTS ---\n");
  for(int i = 0; i < num_students; i++){
    printf("Student %3d mark is: %2d -->", i+1, students[i]);
    if(students[i] < PASS_MARK){
      printf("NOT PASS\n");
    }
    else{
      printf("PASS\n");
    }
  }

  printf("\n--- SWITCH ---\n");
  for(int i = 0; i < num_students; i++){
    printf("Student %d mark is: %d -->", i+1, students[i]);
    int mark = students[i];
    switch(mark){
      case (50):
        printf("YOU ARE EFFICIENT\n");
        break;
      default:
        printf("I AM NOT SURE\n");
    }
  }
  return 0;
}
