#include "networking.h"
#include <time.h>

int check;
char name[256];



int booting(){
  char name[256];
  printf("\e[1;1H\e[2J");
  printf("Enter your name: ");
  fgets(name, 256, stdin);
  name[strlen(name) - 1] = '\0';
  printf("\e[1;1H\e[2J");
  printf("**************************\n");
  printf("WELCOME TO CHAT ROOM\n");
  printf("**************************\n");
  printf("Welcome, [%s]\n", name);
  printf("You can now enter messages!\n");

  return 1;
}



char * timeStamp(){
  time(NULL);
  time_t now;
  char * timey = ctime(&now);
  timey[strcspn(timey, "\n")] = '\0';
  char * paren1 = calloc(100, sizeof(char));
  strcpy(paren1, " (");
  char * paren2 = calloc(100, sizeof(char));
  strcpy(paren2, "): ");
  timey = strcat(paren1, timey);
  timey = strcat(timey, paren2);
  return timey;
}

void channel(char * ip, char * portNum){
  int server_socket;
  char buffer[BUFFER_SIZE];name
  int f;

  fd_set read_fds;

  server_socket = client_setup(ip, portNum);
  //printf("\e[1;1H\e[2J");

  check = 1;

  while (1){
    if(check == 1){
      fflush(stdout);name
      FD_ZERO(&read_fds);
      FD_SET(STDIN_FILENO, &read_fds);
      FD_SET(server_socket, &read_fds);

      //select will block until either fd is ready
      select(server_socket + 1, &read_fds, NULL, NULL, NULL);

      if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        printf("\e[1;1H\e[2J");
        printf("**************************\n");
        printf("WELCOME TO CHAT ROOM\n");
        printf("**************************\n");
        char buffer[BUFFER_SIZE];
        //check what this prints out exactly
        //printf("%s: ", username);
        fgets(buffer, sizeof(buffer), stdin);
        *strchr(buffer, '\n') = 0;
        //printf("%s: ", username);
        // if(strstr(buffer, "#in")){
        //   char temp[BU        printf("%s: ", username);FFER_SIZE];
        //   temp = buffer;
        // }
        char * timey = timeStamp();
        char * chatLine = calloc(256, sizeof(char));
        chatLine = strcat(name, timey);
        chatLine = strcat(chatLine, buffer);
        chatLine = strcat(chatLine, "\n");

        write(server_socket, buffer, sizeof(buffer));
        read(server_socket, buffer, sizeof(buffer));

      }
    } else{
      check = booting();
    }
  }

}

// int main(int argc, char **argv) {
//   if (argc == 2)
//     server_socket = channel( argv[1], PORT);
//   else
//     server_socket = channel( TEST_IP, PORT );
// }



int main(int argc, char **argv){
  char name[256];
  printf("Enter your name: ");
  fgets(name, 256, stdin);
  name[strlen(name) - 1] = '\0';
  printf("\e[1;1H\e[2J");
  printf("**************************\n");
  printf("WELCOME TO CHAT ROOM\n");
  printf("**************************\n");
  printf("Welcome, |%s|\n", name);
  printf("You can now enter messages!\n");
  if (argc == 2) {
    channel(argv[1], PORT);
  }
  else {
    channel(TEST_IP, PORT);
  }

  int check = booting();

  return 0;
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
//     //flush the buffer to immediately print# forking: client fserver
//     fflush(stdout);
//
//     //select() modifies read_fds
// //     //we must reset it at each iterationint main(int argc, char **argv) {
//   if (argc == 2)
//     server_socket = channel( argv[1], PORT);
//   else
//     server_socket = channel( TEST_IP, PORT );
//   }
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
