#include "networking.h"

void nickname(){

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

  //MAYBE NEED TO FORK?
  // int f = fork();
  // if (f == 0){
  //   while(1){
  //     //insert all the code from the while loop below
  //   }
  // }

  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
  }
}
