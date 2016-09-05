// FIT3142 - Client that connects to a server with BSD socket
// Author: Arvin Wiyono
// Date: 29 August 2016 - Semester 2
// Based on beej.us tutorial on Network programming

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include "segment-lock.h"
#define PORT "5000"
#define BACKLOG 10
#define BUFFSIZE 1024

void *get_in_addr(struct sockaddr *sa){
  if (sa->sa_family == AF_INET){
    return &(((struct sockaddr_in*)sa)->sin_addr);
  }
  return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char* argv[]){
  int status;
  struct addrinfo hints, *servinfo;

  fprintf(stdout, "fit3142 - client application\n");
  if(argc != 2){
    fprintf(stdout, "usage: client hostname\n");
    exit(1);
  }

  // Perform getaddrinfo()
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC; // look for both IPv4 and IPv6 address
  hints.ai_socktype = SOCK_STREAM; // can be either SOCK_STREAM or SOCK_DGRAM

  if((status = getaddrinfo(NULL, PORT, &hints, &servinfo)) == -1){
    perror("error in getaddrinfo()");
    exit(1);
  }

  // servinfo now points to a linked list of 1 or more struct addrinfos
  struct addrinfo *p;
  int socketfd;
  for(p = servinfo; p != NULL; p = p->ai_next){
    // Get socket file descriptor
    if((socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
      perror("error in socket()");
      fprintf(stdout, "continue to the next addrinfo\n");
      continue;
    }
    // Perform connect
    if(connect(socketfd, p->ai_addr, p->ai_addrlen) == -1){
      close(socketfd);
      perror("error in connect()");
      fprintf(stdout, "continue to the next addrinfo\n");
      continue;
    }
    break;
  }

  // If there is no socket that can be bound
  if(p == NULL){
    perror("error: client failed to connect ");
    exit(1);
  }

  char s[INET6_ADDRSTRLEN];
  inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr), s, sizeof(s));
  fprintf(stdout, "client: connecting to %s\n", s);
  freeaddrinfo(servinfo); // Done with the structure

  SEG_DATA * mydata = (SEG_DATA*) malloc(sizeof(SEG_DATA));

  // Start getting input from server
  char buffer[BUFFSIZE];
  // Some value as long as it is not 1
  int myexit = 1000;

  while(!(myexit == 1)){
    myexit = 1000;
    while(!(myexit > -1 && myexit < 2)){
      // Get user input
      printf("\nEnter command (1 to exit, 0 to continue): ");
      scanf("%d", &myexit);
    }
    if(!(myexit == 1)){
      memset(&buffer, 0, sizeof(buffer));
      // Send something for requesting a response
      send(socketfd, "Give me SEG_DATA", 16, 0); 
      for(;;){
        if(recv(socketfd, buffer, BUFFSIZE, 0) > 0)
          break;
      }
      // Parse integers in buffer
      char * token;
      char * temp;
      const char delim[2] = " ";
      token = strtok(buffer, delim);
      mydata->rpm = strtol(token, &temp, 10);
      token = strtok(NULL, delim);
      mydata->crankangle = strtol(token, &temp, 10);
      token = strtok(NULL, delim);
      mydata->throttle = strtol(token, &temp, 10);
      token = strtok(NULL, delim);
      mydata->fuelflow = strtol(token, &temp, 10);
      token = strtok(NULL, delim);
      mydata->temp = strtol(token, &temp, 10);
      token = strtok(NULL, delim);
      mydata->fanspeed = strtol(token, &temp, 10);
      token = strtok(NULL, delim);
      mydata->oilpres = strtol(token, &temp, 10);
      fprintf(stdout, "RPM              = %d\n", mydata->rpm );
      fprintf(stdout, "Crank Angle      = %d\n", mydata->crankangle );
      fprintf(stdout, "Throttle Setting = %d\n", mydata->throttle );
      fprintf(stdout, "Fuel Flow        = %d\n", mydata->fuelflow );
      fprintf(stdout, "Engine Temp      = %d\n", mydata->temp );
      fprintf(stdout, "Fan Speed        = %d\n", mydata->fanspeed );
      fprintf(stdout, "Oil Pressure     = %d\n", mydata->oilpres );
    }
  }

  close(socketfd);

  fprintf(stdout, "connection is closed!\n");
  return 0;
}
