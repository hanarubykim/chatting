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


  chosenClientColor = calloc(256, sizeof(char));
  strcpy(chosenClientColor, coloring[chosen]);


  char * coloredName = calloc(256, sizeof(char));
  strcpy(coloredName, "\033[4");
  strcat(coloredName, chosenClientColor);
  strcat(coloredName, clientName);
  strcat(coloredName, "\033[;37m");
  strcpy(clientName, coloredName);

}

int booting(){
  // printf("\e[1;1H\e[2J");
  // printf("Enter your name: ");
  // fgets(clientName, 256, stdin);
  // clientName[strlen(clientName) - 1] = '\0';
  printf("\e[1;1H\e[2J");
  printf("****************************\n");
  printf("WELCOME TO CHAT ROOM, [%s]\n", clientName);
  printf("****************************\n");
  // printf("Welcome, [%s]\n", clientName);
  // printf("You can now enter messages!\n");

  printf("WOULD YOU LIKE TO CHOOSE A COLOR FOR YOUR USERNAME? [yes] or [no]\n");
  char decide[256];
  fgets(decide, 256, stdin);
  decide[strlen(decide) - 1] = '\0';
  if(strstr(decide, "yes")){
    choosingColor();
    //printf("GETS UP TO HERE\n");
    //printf("%s", clientName); //for testing purposes
  }
  else{
    printf("Alrighty then! That's fine too. :) \n");
  }

  return 1;
}

char * timeStamp(){
  char * fullLine = calloc(256, sizeof(char));
  char * adjusted = calloc(256, sizeof(char));

  time(NULL);
  time_t now;
  char * timey = ctime(&now);
  timey[strcspn(timey, "\n")] = '\0';
  strncpy(adjusted, timey, 19);

  char * paren1 = calloc(100, sizeof(char));
  strcpy(paren1, " (");
  char * paren2 = calloc(100, sizeof(char));
  strcpy(paren2, "): ");
  timey = strcat(paren1, adjusted);
  timey = strcat(timey, paren2);
  char * space = " ";
  fullLine = strcat(clientName, space);
  fullLine = strcat(fullLine, timey);

  return fullLine;
}

void printingLine(int server_socket, char * message){
  char * timey = timeStamp();
  char * chatLine = calloc(256, sizeof(char));

  //THIS IS DONE BY CHRISTY.
  // strcpy(chatLine, clientName);//name
  // strcat(chatLine, timey);//followed by time
  // strcat(chatLine, message);// followed by message
  // strcat(chatLine, "\n");

  //THIS WAS DONE BY HANA
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
  printf("\e[1;1H\e[2J");
  //check = 1;

  while (1){
    //printf("CALLS THIS FUNC\n"); // should print out everytime
    if(check == 1){
      //printf("AND IT REACHES HERE? OR NAH\n");
      fflush(stdout);
      FD_ZERO(&read_fds);
      FD_SET(STDIN_FILENO, &read_fds);
      FD_SET(server_socket, &read_fds);
      select(server_socket + 1, &read_fds, NULL, NULL, NULL);

      if(FD_ISSET(STDIN_FILENO, &read_fds)){

        char * beginning = timeStamp();
        // printf("\e[1;1H\e[2J");
        // printf("**************************\n");
        // printf("WELCOME TO CHAT ROOM :)\n");
        // printf("**************************\n");
        //printf("I THINK IT BREAKS RIGHT HERE??\n");
        //printf("\e[1;1H\e[2J");

        printf("\e[1;1H\e[2J");
        printf("%s", beginning); // prints out name (time):
        fgets(message, sizeof(message), stdin);
        * strchr(message, '\n') = 0;

        //char * timey = timeStamp();
        beginning = timeStamp();

        char chatLine[BUFFER_SIZE];
        strcpy(chatLine, beginning);
        strcat(chatLine, message);

        write(server_socket, chatLine, sizeof(chatLine));
        read(server_socket, message, sizeof(message));
      }
    }else{
      check = booting();
    }
  }
}


int main(int argc, char ** argv){
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
