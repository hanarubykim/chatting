#include "networking.h"
#include <time.h>

int check;
char clientName[256];
char * coloring[7];

//FOR CLIENTS: [4
//FOR TEXT: [1

char * chosenClientColor;
void colors(){
  char * red = ";31m";
  char * green = ";32m";
  char * yellow = ";33m";
  char * blue = ";34m";
  char * magenta = ";35m";
  char * cyan = ";36m";
  char * reset = ";37m";

  coloring[0] = red;
  coloring[1] = green;
  coloring[2] = yellow;
  coloring[3] = blue;
  coloring[4] = magenta;
  coloring[5] = cyan;
  coloring[6] = reset;

}

void choosingColor(){
  colors(); //sets up the array of colors
  printf("CHOOSING USERNAME COLOR... HERE ARE YOUR OPTIONS\n");
  printf("(1) RED\n(2) GREEN\n(3) YELLOW\n(4) BLUE\n(5) MAGENTA\n(6) CYAN\n(7) WHITE\n\n");
  printf("PLEASE ENTER THE NUMBER OF YOUR DESIRED USERNAME COLOR: ");

  char colorNum[256];
  fgets(colorNum, 256, stdin);
  colorNum[strlen(colorNum) - 1] = '\0';

  int chosen = atoi(colorNum);

  // chosenClientColor = coloring[chosen];
  // char * coloredName = calloc(256, sizeof(char));
  // coloredName = strcat("\033[4", chosenClientColor);
  // coloredName = strcat(coloredName, clientName);
  // coloredName = strcat(coloredName, "\033[1");
  // coloredName = strcat(coloredName, coloring[6]);


  chosenClientColor = calloc(256, sizeof(char));
  strcpy(chosenClientColor, coloring[chosen]);


  char * coloredName = calloc(256, sizeof(char));
  strcpy(coloredName, "\033[4");

  strcat(coloredName, chosenClientColor);

  strcat(coloredName, "\033[1");

  //clientName = coloredName;
  strcpy(clientName, coloredName);
  printf("%s", clientName);
  //return clientColoring[chosen];
  //printf("\033%sHELLO\033%s\n", clientColoring[chosen], clientColoring[7]);
}

int booting(){
  // printf("\e[1;1H\e[2J");
  // printf("Enter your name: ");
  // fgets(clientName, 256, stdin);
  // clientName[strlen(clientName) - 1] = '\0';
  printf("\e[1;1H\e[2J");
  printf("**************************\n");
  printf("WELCOME TO CHAT ROOM, [%s]\n", clientName);
  printf("**************************\n");
  // printf("Welcome, [%s]\n", clientName);
  // printf("You can now enter messages!\n");

  printf("WOULD YOU LIKE TO CHOOSE A COLOR FOR YOUR USERNAME? [yes] or [no]\n");
  char decide[256];
  fgets(decide, 256, stdin);
  decide[strlen(decide) - 1] = '\0';
  if(strstr(decide, "yes")){
    choosingColor();
    printf("GETS UP TO HERE\n");
  }
  else{
    printf("Alrighty then! That's fine too. :) \n");
  }

  return 1;
}


char * timeStamp(){
  char * fullLine = calloc(256, sizeof(char));
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
  char * space = " ";
  fullLine = strcat(clientName, space);
  fullLine = strcat(fullLine, timey);

  return fullLine;
}

void printingLine(int server_socket, char * message){
  char * timey = timeStamp();
  char * chatLine = calloc(256, sizeof(char));
  chatLine = strcat(clientName, timey);
  chatLine = strcat(chatLine, message);
  chatLine = strcat(chatLine, "\n");

  write(server_socket, message, sizeof(message));
  read(server_socket, message, sizeof(message));
}

void channel(char * ip, char * portNum){
  int server_socket;
  char message[BUFFER_SIZE];
  int f;

  fd_set read_fds;

  server_socket = client_setup(ip, portNum);

  //check = 1;


  while (1){
    if(check == 1){
      fflush(stdout);
      FD_ZERO(&read_fds);
      FD_SET(STDIN_FILENO, &read_fds);
      FD_SET(server_socket, &read_fds);

      //select will block until either fd is ready
      select(server_socket + 1, &read_fds, NULL, NULL, NULL);

      if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        printf("\e[1;1H\e[2J");
        printf("**************************\n");
        printf("WELCOME TO CHAT ROOM :)\n");
        printf("**************************\n");
        char message[BUFFER_SIZE];
        fgets(message, sizeof(message), stdin);
        *strchr(message, '\n') = 0;

        //printf("%s: ", username);
        // if(strstr(buffer, "#in")){
        //   char temp[BU        printf("%s: ", username);FFER_SIZE];
        //   temp = buffer;
        // }

        // char * timey = timeStamp();
        // char * chatLine = calloc(256, sizeof(char));
        // chatLine = strcat(clientName, timey);
        // chatLine = strcat(chatLine, message);
        // chatLine = strcat(chatLine, "\n");

        printingLine(server_socket, message);
        //TEST OUT WHAT WRITE VS WHAT READ DOES TOMORROW
        // write(server_socket, message, sizeof(message));
        // read(server_socket, message, sizeof(message));

      }
    } else{
      check = booting();
    }
  }

}// printf("CHOOSING USERNAME COLOR... HERE ARE YOUR OPTIONS\n");
  // printf("(1) RED\n(2) GREEN\n(3) YELLOW\n(4) BLUE\n(5) MAGENTA\n(6) CYAN\n(7) WHITE\n\n");
  // printf("PLEASE ENTER THE NUMBER OF YOUR DESIRED USERNAME COLOR: ");
  //
  // char colorNum[256];
  // fgets(colorNum, 256, stdin);
  // colorNum[strlen(colorNum) - 1] = '\0';
  //
  // int chosen = atoi(colorNum);
  //
  // chosenClientColor = coloring[chosen];
  // char * coloredName = calloc(256, sizeof(char));
  // coloredName = strcat("\033[4", chosenClientColor);
  // coloredName = strcat(coloredName, clientName);
  // coloredName = strcat(coloredName, "\033[1");
  // coloredName = strcat(coloredName, coloring[7]);
  //
  // //clientName = coloredName;
  // strcpy(clientName, coloredName);
  // printf("%s", clientName);
  // //return clientColoring[chosen];
  // //printf("\033%sHELLO\033%s\n", clientColoring[chosen], clientColoring[7]);

int main(int argc, char **argv){
  // colors();
  // char * testing = calloc(256, sizeof(char));
  // char * chosenColor = calloc(256, sizeof(char));
  // strcpy(chosenColor, coloring[1]); //RED
  // printf("WORKING");
  // char * changeText = calloc(256, sizeof(char));
  // strcpy(changeText, "\033[4");
  // strcat(changeText, chosenColor);

  printf("Enter your name: ");
  fgets(clientName, 256, stdin);
  clientName[strlen(clientName) - 1] = '\0';


  // printf("%shiya", changeText); //THIS IS PART OF THE BLOCK OF CODE ABOVE. FOR TESTING
  if(argc == 2){
    channel(argv[1], PORT);
  }
  else{
    channel(TEST_IP, PORT);
  }

  //int check = booting();

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
