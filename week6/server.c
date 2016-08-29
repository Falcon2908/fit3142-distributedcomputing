// FIT3142 - Server with BSD socket
// Author: Arvin Wiyono
// Date: 29 August 2016 - Semester 2
// Based on beej.us tutorial on Network programming

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#define PORT "5000"

int main(int argc, char* argv[]){

  int status;
  struct addrinfo hints, *servinfo;

  // Perform getaddrinfo()
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC; // look for both IPv4 and IPv6 address
  hints.ai_socktype = SOCK_STREAM; // can be either SOCK_STREAM or SOCK_DGRAM
  hints.ai_flags = AI_PASSIVE;

  if((status = getaddrinfo(NULL, PORT, &hints, &servinfo)) == -1){
    fprintf(stderr, "error getaddrinfo(): %s\n", gai_strerror(status));
    exit(1);
  }

  // servinfo now points to a linked list of 1 or more struct addrinfos

  return 0;
}
