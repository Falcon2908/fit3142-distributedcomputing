// FIT3142 - Server with BSD socket
// Author: Arvin Wiyono
// Date: 29 August 2016 - Semester 2
// Based on beej.us tutorial on Network programming

#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
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

  fprintf(stdout, "fit3142 - server application\n");

  // Perform getaddrinfo()
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC; // look for both IPv4 and IPv6 address
  hints.ai_socktype = SOCK_STREAM; // can be either SOCK_STREAM or SOCK_DGRAM
  hints.ai_flags = AI_PASSIVE;

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
      continue;
    }

    // Perform binding
    if(bind(socketfd, p->ai_addr, p->ai_addrlen) == -1){
      close(socketfd);
      perror("error in bind()");
      continue;
    }
    break;
  }
  freeaddrinfo(servinfo); // Done with the structure

  // If there is no socket that can be bound
  if(p == NULL){
    perror("error: server failed to bind\n");
    exit(1);
  }

  // BACKLOG is the number of connections allowed on the incoming queue
  if(listen(socketfd, BACKLOG) == -1){
    perror("error: listen()\n");
    exit(1);
  }
  fprintf(stdout, "server: waiting for connections...\n");

  int fdmax = socketfd;
  fd_set read_set;
  fd_set master_set;
  // Initializing set
  FD_ZERO(&read_set);
  FD_ZERO(&master_set);
  // Add socketfd to read_set
  FD_SET(socketfd, &master_set);
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 0;

  // Initializing SEG_DATA
  SEG_DATA * mydata = (SEG_DATA*) malloc(sizeof(SEG_DATA));
  mydata->mylock = 0;
	mydata->exit = 0;
	mydata->rpm = 3500;
	mydata->crankangle = 0;
	mydata->throttle = 70;
	mydata->fuelflow = 50;
	mydata->temp = 80;
	mydata->fanspeed = 30;
	mydata->oilpres = 70;
  int up = 0;

  char buffer[BUFFSIZE] = "";
  int end_loop = 0;
  while(!end_loop){
    // Copy master to read set
    read_set = master_set;

    if(select(fdmax + 1, &read_set, NULL, NULL, &tv) == -1){
      perror("error: select()");
      exit(1);
    }

    for(int i = 0; i <= fdmax; i++){
      if(FD_ISSET(i, &read_set)){ // Get one that is read to be served
        if(i == socketfd){ // A new client is attached
          struct sockaddr_storage client_address;
          socklen_t addr_size = sizeof(client_address);
          int new_fd = accept(socketfd, (struct sockaddr *) &client_address, &addr_size);

          if(new_fd == -1){
            perror("error: accept()");
            exit(1);
          }
          else{
            FD_SET(new_fd, &master_set);
            if(new_fd > fdmax){
              fdmax = new_fd;
            }
            char s[INET6_ADDRSTRLEN];
            inet_ntop(client_address.ss_family, get_in_addr((struct sockaddr *) &client_address), s, sizeof(s));
            fprintf(stdout, "\nserver: got connection from %s\n", s);
          }
        }
        else{
          int nbytes;
          // Check whether client is detached from socket
          if((nbytes = recv(i, buffer, sizeof(buffer), 0)) == 0){
            fprintf(stdout, "\nserver: client #%d is disconnected\n", i);
            close(i);
            // Remove from master set
            FD_CLR(i, &master_set);
            end_loop = 1; // End the while loop if one of the clients is detached
          }
          else{
            sprintf(buffer, "%d %d %d %d %d %d %d\n", mydata->rpm, mydata->crankangle, mydata->throttle, mydata->fuelflow, mydata->temp, mydata->fanspeed, mydata->oilpres);
            // Client requests SEG_DATA
            send(i, buffer, strlen(buffer), 0);
          }
        }
      } // End of if FD_ISSET
    } // End of loop
    // Update values in SEG_DATA
    if ( up == 1 && mydata->rpm > 6500 ) up = 0;
		if ( up == 0 && mydata->rpm < 500 ) up = 1;
		if ( up == 1 ){
			mydata->rpm += 100;
			mydata->crankangle += 1;
			mydata->crankangle %= 360;
			mydata->throttle += 1;
			mydata->throttle %= 100;
			mydata->fuelflow += 1;
			mydata->fuelflow %= 100;
			mydata->temp += 1;
			mydata->temp %= 100;
			mydata->fanspeed += 1;
			mydata->fanspeed %= 100;
			mydata->oilpres += 1;
			mydata->oilpres %= 100;
		} else {
			mydata->rpm -= 100;
			mydata->crankangle -= 1;
			mydata->crankangle %= 360;
			mydata->throttle -= 1;
			mydata->throttle %= 100;
			mydata->fuelflow -= 1;
			mydata->fuelflow %= 100;
			mydata->temp -= 1;
			mydata->temp %= 100;
			mydata->fanspeed -= 1;
			mydata->fanspeed %= 100;
			mydata->oilpres -= 1;
			mydata->oilpres %= 100;
		}
		sleep(1);
		fprintf(stdout, "\nSTATUS DUMP\n");
		fprintf(stdout, "Lock             = %d\n", mydata->mylock );
		fprintf(stdout, "Present          = %d\n", mydata->present );
		fprintf(stdout, "Exit Status      = %d\n", mydata->exit );
		fprintf(stdout, "UP Status        = %d\n", up );
		fprintf(stdout, "RPM              = %d\n", mydata->rpm );
		fprintf(stdout, "Crank Angle      = %d\n", mydata->crankangle );
		fprintf(stdout, "Throttle Setting = %d\n", mydata->throttle );
		fprintf(stdout, "Fuel Flow        = %d\n", mydata->fuelflow );
		fprintf(stdout, "Engine Temp      = %d\n", mydata->temp );
		fprintf(stdout, "Fan Speed        = %d\n", mydata->fanspeed );
		fprintf(stdout, "Oil Pressure     = %d\n", mydata->oilpres );
  } // End of while loop

  close(socketfd);
  fprintf(stdout, "connection is closed!\n");
  return 0;
}
