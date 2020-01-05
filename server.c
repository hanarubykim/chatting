#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
  char name[256];
  printf("WELCOME TO CHAT ROOM\n");
  printf("Enter your name: ");
  fgets(name, 256, stdin);
  name[strlen(name) - 1] = 0;

  printf("Welcome, %s\n", name);

  

  return 0;
}
