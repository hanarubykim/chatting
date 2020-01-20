#include "networking.h"
#include <time.h>

int check;
char clientName[256];
char * coloring[7];
char chatLine[BUFFER_SIZE];
char message[BUFFER_SIZE];
char fullLine[256];

//FOR CLIENTS: [4, FOR TEXT: [1
char * chosenClientColor;



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

//helper function for choosingColor
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
  strcpy(chosenClientColor, coloring[chosen - 1]);


  char * coloredName = calloc(256, sizeof(char));
  strcpy(coloredName, "\033[4");
  strcat(coloredName, chosenClientColor);
  strcat(coloredName, clientName);
  strcat(coloredName, "\033[;37m");
  strcpy(clientName, coloredName);

}

int booting(){
  //NOT TH
  printf("\e[1;1H\e[2J");
  printf("***************************************\n");
  printf("WELCOME TO CHAT ROOM, [%s]\n", clientName);
  printf("***************************************\n");

  printf("WOULD YOU LIKE TO CHOOSE A COLOR FOR YOUR USERNAME? [yes] or [no]\n");
  char decide[256];
  fgets(decide, 256, stdin);
  decide[strlen(decide) - 1] = '\0';

  if(strstr(decide, "yes")){
    choosingColor();
  }
  else{
    printf("Alrighty then! That's fine too. :) \n");
  }

  return 1;
}

char * timeStamp(){
  time_t now = time(NULL);
  char * timey = ctime(&now);
  timey[strcspn(timey, "\n")] = '\0';

  char * paren1 = calloc(100, sizeof(char));
  strcpy(paren1, " (");
  char * paren2 = calloc(100, sizeof(char));
  strcpy(paren2, ")");

  timey = strcat(paren1, timey);
  timey = strcat(timey, paren2);

  return timey;
}

void channel(char * ip, char * p){
  int f;
  int server_socket;
  fd_set read_fds;

  server_socket = client_setup(ip, p);

  printf("\e[1;1H\e[2J");

  while (1){
    if(check == 1){
      fflush(stdout);
      FD_ZERO(&read_fds);
      FD_SET(STDIN_FILENO, &read_fds);
      FD_SET(server_socket, &read_fds);
      select(server_socket + 1, &read_fds, NULL, NULL, NULL);

      if(FD_ISSET(STDIN_FILENO, &read_fds)){
        char * timing = timeStamp();
        strcpy(fullLine, clientName);
        strcat(fullLine, " ");
        strcat(fullLine, timing);
        strcat(fullLine, ": ");
        printf("%s", fullLine);


        char message[BUFFER_SIZE];
        fgets(message, sizeof(message), stdin);
        message[strlen(message) - 1] = '\0';
        //* strchr(message, '\n') = '\0';

        if(strstr(message, "*JOIN")){

          char ** parsed = parse_args(message, " ");
          char * newPort = parsed[1];
          printf("%s", newPort);
          f = fork();
          if(f != 0){
            channel(ip, newPort);
          }
          else{
            exit(0);
          }
        }
        char * updatedTime = timeStamp();
        strcpy(chatLine, fullLine);
        strcat(chatLine, message);

        write(server_socket, chatLine, sizeof(chatLine));
        read(server_socket, message, sizeof(message));

      }
    }else{
      check = booting();
    }

    //this would allow for broadcast messages
    //between clients
    if (FD_ISSET(server_socket, &read_fds)) {
      read(server_socket, message, sizeof(message));
      printf("\r%s\n%s", message, fullLine);
      fflush(stdout);
    }//end socket select

  }
}

int main(int argc, char ** argv){
  printf("\e[1;1H\e[2J");
  printf("************************\n");
  printf("Setting up chatroom...\n");
  printf("************************\n");
  printf("Enter your name: ");
  fgets(clientName, 256, stdin);
  clientName[strlen(clientName) - 1] = '\0';

  if(argc == 2){
    channel(argv[1], PORT);
  }
  else{
    channel(TEST_IP, PORT);
  }
  return 0;
}
