#include "networking.h"

int main(int argc, char **argv) {
  if (argc == 2)
    server_socket = channel( argv[1], PORT);
  else
    server_socket = channel( TEST_IP, PORT );
  }

void channel(char * ip, char * portNum){
  int server_socket;
  char buffer[BUFFER_SIZE];
  int f;

  fd_set read_fds;

  server_socket = client_setup( ip, portNum);

  printf("\e[1;1H\e[2J");

  while (1) {

    // printf("enter data: ");
    //the above printf does not have \n
    //flush the buffer to immediately print
    fflush(stdout);

    //select() modifies read_fds
    //we must reset it at each iteration
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
    FD_SET(server_socket, &read_fds); //add socket to fd set

    //select will block until either fd is ready
    select(server_socket + 1, &read_fds, NULL, NULL, NULL);

    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      char msg[BUFFER_SIZE];

      // printf("\e[1m\e[92m%s: \e[21m\e[39m", clientName); *******NEED TO ACCESS THE NAME******* do this later


      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;

      // ***NEED TO FIX LATER. WILL GET NAME OF USER AND TIME OF MESSAGE SENT********
      // char * chatLine = calloc(256, sizeof(char));
      // chatLine = strcat(name, timey);
      // chatLine = strcat(chatLine, message);


      write(server_socket, msg, sizeof(chatLine));
      read(server_socket, buffer, sizeof(buffer));


      //currently the server is not set up to
      //send messages to all the clients, but
      //this would allow for broadcast messages
      if (FD_ISSET(server_socket, &read_fds)) {
        read(server_socket, buffer, sizeof(buffer));
        // printf("[SERVER BROADCAST] [%s]\n", buffer); //*****FIX LATER TO ALLOW FOR USER NAME TO BE DISPLAYED****
        // printf("enter data: ");
        //the above printf does not have \n
        //flush the buffer to immediately print
        fflush(stdout);
      }//end socket select


}



// int main(int argc, char **argv) {
//
//   int server_socket;
//   char buffer[BUFFER_SIZE];
//
//   fd_set read_fds;
//
//   if (argc == 2)
//     server_socket = client_setup( argv[1]);
//   else
//     server_socket = client_setup( TEST_IP );
//
//   while (1) {
//
//     printf("enter data: ");
//     //the above printf does not have \n
//     //flush the buffer to immediately print
//     fflush(stdout);
//
//     //select() modifies read_fds
//     //we must reset it at each iteration
//     FD_ZERO(&read_fds);
//     FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
//     FD_SET(server_socket, &read_fds); //add socket to fd set
//
//     //select will block until either fd is ready
//     select(server_socket + 1, &read_fds, NULL, NULL, NULL);
//
//     if (FD_ISSET(STDIN_FILENO, &read_fds)) {
//       fgets(buffer, sizeof(buffer), stdin);
//       *strchr(buffer, '\n') = 0;
//       write(server_socket, buffer, sizeof(buffer));
//       read(server_socket, buffer, sizeof(buffer));
//       printf("received: [%s]\n", buffer);
//     }//end stdin select
//
//     //currently the server is not set up to
//     //send messages to all the clients, but
//     //this would allow for broadcast messages
//     if (FD_ISSET(server_socket, &read_fds)) {
//       read(server_socket, buffer, sizeof(buffer));
//       printf("[SERVER BROADCAST] [%s]\n", buffer);
//       printf("enter data: ");
//       //the above printf does not have \n
//       //flush the buffer to immediately print
//       fflush(stdout);
//     }//end socket select
//
//   }//end loop
// }
