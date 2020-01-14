#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "node.c"
#include <time.h>

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

void addMessage(Node * head, char * message){
  push(head, message);
}

int main(){
  //******************************************************************************
  //ACTUAL CODE OF THE CHAT ROOM
  //asks for name, message
  //right now, focus on having just one user
  //each time a user enters a message, create a node

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

  while(1){
    char *tempName = name;
    char message[256];
    fgets(message, 256, stdin);
    message[strlen(message) - 1] = '\n';
    message[strlen(message)] = '\0';
    char * timey = timeStamp();
    //Combining UserName (Time): Message || Stores entire line in one string
    char * chatLine = calloc(256, sizeof(char));
    chatLine = strcat(tempName, timey);
    chatLine = strcat(chatLine, message);

    //Node contains string "Hana Kim (12:02:35): hello world"
    addMessage(msg, chatLine);

    printf("\e[1;1H\e[2J");
    printf("**************************\n");
    printf("WELCOME TO CHAT ROOM\n");
    printf("**************************\n");

  }


  return 0;
}
