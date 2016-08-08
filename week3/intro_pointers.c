#include <stdio.h>

int main(int argc, char* argv[]){
  int AValue, *BValue;

  AValue = 0;
  printf("Address of AValue %p AValue = %d\n", &AValue, AValue);

  AValue = 101;
  BValue = &AValue;

  // This is because BValue and &AValue points to the same memory address
  // Thus getting the same exact value
  printf("Address of BValue %p BValue = %d\n", BValue, *BValue);

  // This is a pointer to a pointer
  int** CValue;
  CValue = &BValue;

  printf("Address of CValue %p CValue = %d\n", *CValue, **CValue);

  return 0;
}
