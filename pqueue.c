#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
  char* data;
  struct node* next;

} Node;

//function to create a new node
Node* newNode(char* d){
  Node* temp = (Node*)malloc(sizeof(Node));
  temp->data = d;
  temp->next = NULL;
  return temp;
}

//return the value at head
char* peek(Node** head){
  return (*head)->data;
}

//removes the element with the highest priority from the list
void pop(Node** head){
  Node* temp = *head;
  (*head) = (*head)->next;
  free(temp);
}

//function to push according to priority
void push(Node** head, char* d){
  Node* start = (*head);

  //create new node
  Node* temp = newNode(d);

  //insert node with higher priority. Insert new node before head node and change head node
  temp->next = *head;
  (*head) = temp;

  //either at the ends of the list or at required position
  //temp->next = start->next;
  //start->next = temp;
}

//function to check is list is empty
int isEmpty(Node** head){
  return (*head) == NULL;
}
