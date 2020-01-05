#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "pqueue.c"

int main(){

  //TESTING CODE FOR PRIORITY QUEUE

  //each node is data, followed by it's priority
  //LOWER PRIORITY VALUE == HIGHER PRIORITY so m4 has the highest priority, will be popped off first

  Node* pq = newNode("m1", 1);
  push(&pq, "m2", 2);
  push(&pq, "m3", 3);
  push(&pq, "m4", 0);

  while (!isEmpty(&pq)) {
    printf("%s \n", peek(&pq));
    pop(&pq);
  }

  //will output m4 m1 m2 m3


  //******************************************************************************

  //ACTUAL CODE OF THE CHAT ROOM
  //asks for name
  //asks for message

  //right now, focus on having just one user

  //need to implement priority queue in order to store message
  //each time a user enters a message, create a node
  //highest priority nodes will be most recent message
  //lowest priority nodes will have older messages

  //thinking of having a variable called priority = 1000 (max messages the chatroom can hold )
  //each time a message is sent, decrease priority by 1
  //that way, the older messages (with priority 1000) are stored further along the pqueue. newer messages (with priority 999, 998, etc) are stored near the front of the list



  char name[256];
  printf("WELCOME TO CHAT ROOM\n");
  printf("Enter your name: ");
  fgets(name, 256, stdin);
  name[strlen(name) - 1] = 0;

  printf("Welcome, %s\n\n", name);

  char message[256];

  printf("Please enter a message: ");
  fgets(message, 256, stdin);
  message[strlen(message) - 1] = 0;
  printf("Message you just entered: %s\n", message);




  return 0;
}
