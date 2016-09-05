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
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
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
  struct sockaddr_storage client_address;
  socklen_t addr_size = sizeof(client_address);
  // accept() makes server wait until a client is attached
  int new_fd = accept(socketfd, (struct sockaddr *) &client_address, &addr_size);

  if(new_fd == -1){
    perror("error: accept()");
    exit(1);
  }

  char s[INET6_ADDRSTRLEN];
  inet_ntop(client_address.ss_family, get_in_addr((struct sockaddr *) &client_address), s, sizeof(s));
  fprintf(stdout, "server: got connection from %s\n", s);

  char buffer[BUFFSIZE] = "";
  while(recv(new_fd, buffer, BUFFSIZE, 0)){
    fprintf(stdout, "%s", buffer);
    memset(buffer,0,strlen(buffer));
  }
  close(new_fd);
  close(socketfd);

  fprintf(stdout, "connection is closed!\n");
  return 0;
}
