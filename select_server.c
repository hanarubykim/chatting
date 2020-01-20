#include "networking.h"

int f; //fork pid

char ** parse_args(char * line, char * split);
void process(char *s);
void subserver(int from_client);
void channel(char * portNum);

int main(){
  channel(PORT);
}

//simple parsing
char ** parse_args(char * line, char * split) {
  line = strsep(&line, "\n");
  char ** args = malloc(sizeof(char *) * 10);
  int x = 0;
  while (line) {
    args[x] = strsep( &line, split);
    x += 1;
  }
  args[x] = NULL;
  return args;
}


void channel(char * portNum){
  int listen_socket;
  int client_socket;
  int subserver_count = 0;
  char buffer[BUFFER_SIZE];

  int max_clients = 10; // max num of clients allowed
  int clientsConnected[max_clients]; // client sockets stored in an array
  int fd_max; // largest fd

  // set of file descriptors to read from
  fd_set read_fds;
  int i;

  // initialize the array of clients
  for (i = 0; i < max_clients; i++) {
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

    for(i = 0; i < max_clients; i++){
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
    if (FD_ISSET(listen_socket, &read_fds)) {

      client_socket = server_connect(listen_socket);

      //for testing client select statement
      // strncpy(buffer, "DOES THIS OUTPUT ANYTHING?!\n", sizeof(buffer));
      write(client_socket, buffer, sizeof(buffer));


      // If we still have space for more clients
      //  Add client to the collection of clients
      for (i = 0; i < max_clients; i++) {
        if (!clientsConnected[i]) {
          clientsConnected[i] = client_socket;
          printf("USER %d has connected to port %s\n", client_socket, portNum);
          break;
        }
      }
    }

    for (i = 0; i < max_clients; i++) {
      //if listen_socket triggered select
      if (FD_ISSET(clientsConnected[i], &read_fds)) {
        if (read(clientsConnected[i], buffer, sizeof(buffer))) {
          //read in the line that could contain the prompt to create/join chatrooms

          //create a chatroom
          if(strstr(buffer, "*CREATE")){
            char ** parsed = parse_args(buffer, " ");
            char * newPort = parsed[8];
            // strcat(buffer, newPort);
            f = fork();
            if(f == 0){
              //THIS CAT DOES NOT WORK ****************
              // strcat(buffer, "CREATED PORT");
              // strcat(buffer, newPort);
              channel(newPort);
            }
          }

          //join a different chatroom
          if (strstr(buffer, "*JOIN")){
            close(clientsConnected[i]);
            clientsConnected[i] = 0;
            // Send to all clients
            for (i = 0; i < max_clients; i++){
              if (clientsConnected[i] > 0) {
                write(clientsConnected[i], buffer, sizeof(buffer));
              }
            }
          }

          printf("[subserver %d] received: [%s]\n", getpid(), buffer);

          for (i = 0; i < max_clients; i++) {
            if (clientsConnected[i] > 0) {
              write(clientsConnected[i], buffer, sizeof(buffer));
            }
          }
        } else{
          close(clientsConnected[i]);
          clientsConnected[i] = 0;
        }
      }
    }

    //if stdin triggered select
    if (FD_ISSET(STDIN_FILENO, &read_fds)){
      //if you don't read from stdin, it will continue to trigger select()
      fgets(buffer, sizeof(buffer), stdin);
      printf("[server] subserver count: %d\n", subserver_count);
    }
  }
}
