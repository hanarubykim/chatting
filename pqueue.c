#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
  char* data;
  int priority; //lower values indicate higher priority
  struct node* next;

} Node;

//function to create a new node
Node* newNode(char* d, int p){
  Node* temp = (Node*)malloc(sizeof(Node));
  temp->data = d;
  temp->priority = p;
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
void push(Node** head, char* d, int p){
  Node* start = (*head);

  //create new node
  Node* temp = newNode(d, p);

  //insert node with higher priority. Insert new node before head node and change head node
  if ((*head)->priority > p) {
    //insert new node before head
    temp->next = *head;
    (*head) = temp;
  }
  else {
    //traverse the list and find a position to insert new node
    while (start->next != NULL && start->next->priority < p) {
      start = start->next;
    }

    //either at the ends of the list or at required position
    temp->next = start->next;
    start->next = temp;
    }
}

//function to check is list is empty
int isEmpty(Node** head){
  return (*head) == NULL;
}
