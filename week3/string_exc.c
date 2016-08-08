#include <stdio.h>
#include <string.h>

int main(){
  char line[100], *sub_text;

  strcpy(line, "Hello, I am a string.");
  printf("Line: %s\n", line);

  strcat(line, " What are you?");
  printf("Line: %s\n", line);

  printf("Length of line: %d\n", (int)strlen(line));

  if( ( sub_text = strchr(line, 'W') ) != NULL){
    printf("String starting with \"W\" --> %s\n", sub_text);
  }

  if( ( sub_text = strchr(line, 'w') ) != NULL ){
    printf("String starting with \"w\" --> %s\n", sub_text);
  }
  else{
    printf("String does not contain \"w\"\n");
  }

  if( ( sub_text = strchr(line, 'u') ) != NULL){
    printf("String starting with \"u\" --> %s\n", sub_text);
    printf("Memory location of \"u\": %p\n", sub_text);
  }

  return 0;
}
