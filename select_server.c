#include "networking.h"

//*WORKK ON THIS *****************************
void process(char *s);
void subserver(int from_client);
void channel(char * portNum);

int main(){
  channel(PORT);
}

void channel(char * portNum){
  signal(SIGINT, sighandler);

  int listen_socket;
  int client_socket;
  //   int f;
  int subserver_count = 0;
  char buffer[BUFFER_SIZE];

  int max_clients = 10; // max num of clients allowed
  int clientsConnected[max_clients]; // client sockets stored in an array
  int fd_max; // largest fd


  // set of file descriptors to read from
  fd_set read_fds;

  // initialize the array of clients
  for (int i = 0; i < max_clients; i++) {
      clientsConnected[i] = 0;
  }

  listen_socket = server_setup(portNum);
  fd_max = listen_socket;

  while (1) {

      //select() modifies read_fds
      //we must reset it at each iteration
      FD_ZERO(&read_fds); //0 out fd set
      FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
      FD_SET(listen_socket, &read_fds); //add socket to fd set

      for(int i = 0; i < max_clients; i++){
        if(clientsConnected[i] > 0){
          FD_SET(clientsConnected[i], &read_fds);
        }

        if(clientsConnected[i] > fd_max){//to make sure fd_max is always the largest fd
          fd_max = clientsConnected[i];
        }
      }

      //select will block until either fd is ready
      select(fd_max + 1, &read_fds, NULL, NULL, NULL);

      //if listen_socket triggered select
      if (FD_ISSET(clientsConnected[i], &read_fds)) {
        //need to create ability to ...
        //create a chatroom
        //join a different chatroom
        if(read(clientsConnected[i], &read_fds)){
          //read in the line that could contain the prompt to create/change chatrooms


          //NOT DONE YET



          //create a chatroom
          if(strstr(buffer, "!CREATE ")){
            char * newPort; //need to parse the line to find the new chatroom name
            strcat(buffer, newPort);
            f = fork();
            if(f == 0){
              channel(newPort);
            }
          }

          //join a different chatroom
          //need to do this later
        }




       // client_socket = server_connect(listen_socket);
       //
       // f = fork();
       // if (f == 0)
       //   subserver(client_socket);
       // else {
       //   subserver_count++;
       //   close(client_socket);
       // }
      }//end listen_socket select

      //if stdin triggered select
      if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        //if you don't read from stdin, it will continue to trigger select()
        fgets(buffer, sizeof(buffer), stdin);
        printf("[server] subserver count: %d\n", subserver_count);
      }//end stdin select
    }
  }



}



// int main() {
//
//   int listen_socket;
//   int client_socket;
//   int f;
//   int subserver_count = 0;
//   char buffer[BUFFER_SIZE];
//
//   //set of file descriptors to read from
//   fd_set read_fds;
//
//   listen_socket = server_setup();
//
//   while (1) {
//
//     //select() modifies read_fds
//     //we must reset it at each iteration
//     FD_ZERO(&read_fds); //0 out fd set
//     FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
//     FD_SET(listen_socket, &read_fds); //add socket to fd set
//
//     //select will block until either fd is ready
//     select(listen_socket + 1, &read_fds, NULL, NULL, NULL);
//
//     //if listen_socket triggered select
//     if (FD_ISSET(listen_socket, &read_fds)) {
//      client_socket = server_connect(listen_socket);
//
//      f = fork();
//      if (f == 0)
//        subserver(client_socket);
//      else {
//        subserver_count++;
//        close(client_socket);
//      }
//     }//end listen_socket select
//
//     //if stdin triggered select
//     if (FD_ISSET(STDIN_FILENO, &read_fds)) {
//       //if you don't read from stdin, it will continue to trigger select()
//       fgets(buffer, sizeof(buffer), stdin);
//       printf("[server] subserver count: %d\n", subserver_count);
//     }//end stdin select
//   }
// }
//
// void subserver(int client_socket) {
//   char buffer[BUFFER_SIZE];
//
//   //for testing client select statement
//   strncpy(buffer, "hello client", sizeof(buffer));
//   write(client_socket, buffer, sizeof(buffer));
//
//   while (read(client_socket, buffer, sizeof(buffer))) {
//
//     printf("[subserver %d] received: [%s]\n", getpid(), buffer);
//     process(buffer);
//     write(client_socket, buffer, sizeof(buffer));
//   }//end read loop
//   close(client_socket);
//   exit(0);
// }
//
// void process(char * s) {
//   while (*s) {
//     if (*s >= 'a' && *s <= 'z')
//       *s = ((*s - 'a') + 13) % 26 + 'a';
//     else  if (*s >= 'A' && *s <= 'Z')
//       *s = ((*s - 'a') + 13) % 26 + 'a';
//     s++;
//   }
// }
