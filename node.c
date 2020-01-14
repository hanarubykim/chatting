#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
  char* data;
  struct node * next;
} Node;

Node * newNode(char * d){
  Node * temp = malloc(sizeof(Node));
  temp->data = d;
  temp->next = NULL;
  return temp;
}

char * peek(Node * head){
  return head->data;
}

char * print(Node * current){
  if(current == NULL){
    return NULL;
  }
  char * temp = current->data;
  return temp;
}

void pop(Node * head){
  head->data = NULL;
  head->next = NULL;
  free(head);
}

void push(Node * head, char * d){
  Node * newHead = newNode(d);
  newHead->next = head;
  head = newHead;
}

int isEmpty(Node * head){
  return head == NULL;
}

Node * copy(Node * head){
  if(isEmpty(head)){
    return NULL;
  }

  Node * newHead = (Node *) malloc(sizeof(Node));
  newHead->data = head->data;

  Node * temp = newHead;
  head = head->next;
  while(!isEmpty(head)){
    printf("AT WHAT POINT DOES THIS BREAK?\n");
    temp->next = malloc(sizeof(Node));
    temp = temp->next;
    strcpy(temp->data, head->data);
    head = head->next;
  }
  temp->next = NULL;
  return newHead;
}








//ws
