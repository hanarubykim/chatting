#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "pqueue.c"

int main(){

  Node* pq = newNode("m1", 1);
    push(&pq, "m2", 2);
    push(&pq, "m3", 3);
    push(&pq, "m4", 0);

    while (!isEmpty(&pq)) {
      printf("%s \n", peek(&pq));
      pop(&pq);
    }


  // char name[256];
  // printf("WELCOME TO CHAT ROOM\n");
  // printf("Enter your name: ");
  // fgets(name, 256, stdin);
  // name[strlen(name) - 1] = 0;
  //
  // printf("Welcome, %s\n\n", name);
  //
  // char message[256];
  //
  // printf("Please enter a message: ");
  // fgets(message, 256, stdin);
  // message[strlen(message) - 1] = 0;
  // printf("Message you just entered: %s\n", message);




  return 0;
}
