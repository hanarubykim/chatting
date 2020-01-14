#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "networking.h"

int booting(){
  char name[256];
  printf("Enter your name: ");
  fgets(name, 256, stdin);
  name[strlen(name) - 1] = '\0';
  printf("\e[1;1H\e[2J");
  printf("**************************\n");
  printf("WELCOME TO CHAT ROOM\n");
  printf("**************************\n");
  printf("Welcome, [%s]\n", name);
  printf("You can now enter messages!\n");

  return 0;
}

int main(int argc, char **argv) {
  int server_socket;
  char buffer[BUFFER_SIZE];
  char portNum[BUFFER_SIZE];
  [printf("Enter port# between 49152-65535: ");
  fgets(portNum, sizeof(portNum), stdin);
  *strchr(portNum, '\n') = 0;]

  if (argc == 2)
    server_socket = client_setup( argv[1], portNum);
  else
    server_socket = client_setup( TEST_IP, portNum );

    int go = booting();
	  int f = fork();
	  if (f == 0){
	    while(1){
	      if(go == 1){
          printf("enter data: ");
          fgets(buffer, sizeof(buffer), stdin);
          *strchr(buffer, '\n') = 0;
          write(server_socket, buffer, sizeof(buffer));
          read(server_socket, buffer, sizeof(buffer));
          printf("received: [%s]\n", buffer);
        }
	    }
	  }
    return 0;
  }
