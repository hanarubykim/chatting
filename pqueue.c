#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
  char* data;
  struct node * next;
} Node;

//function to create a new node
Node * newNode(char * d){
  Node* temp = (Node *)malloc(sizeof(Node));
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
  //free(temp);
}

//function to push according to priority
void push(Node ** head, char * d){
  Node* start = (*head);
  //create new node
  Node* temp = newNode(d);
  temp->next = *head;
  (*head) = temp;
}

//function to check is list is empty
int isEmpty(Node** head){
  return (*head) == NULL;
}

Node ** copy(Node ** head){
  Node ** current = malloc(sizeof(Node));
  current = head;
  Node ** newHead = NULL;
  Node ** tail = NULL;
  while(current != NULL){
    if(newHead == NULL){
      newHead = malloc(sizeof(Node));
      (*newHead)->data = (*current)->data;
      (*newHead)->next = NULL;
      //(*tail) = (*newHead);
    }
    else
    {
      (*tail)->next = (Node *)malloc(sizeof(Node));
      (*tail) = (*tail)->next;
      (*tail)->data = (*current)->data;
      (*tail)->next = NULL;
    }
    (*current) = (*current)->next;
    return newHead;
  }

  // Node ** newHead = malloc(sizeof(Node));
  // *newHead = (*head);
  // Node ** prev = malloc(sizeof(Node));
  // *prev = *head;
  // (*head) = (*head)->next;
  // while(!isEmpty(head)){
  //   *prev = (*prev)->next;
  //   //(*prev)->data = (*head)->data;
  //   *head = (*head)->next;
  // }
  // (*prev)->next = NULL;
  // return newHead;
}


// //function to create a new node
// Node * newNode(char * d){
//   Node* temp = malloc(sizeof(Node));
//   temp->data = d;
//   temp->next = NULL;
//   return temp;
// }
//
// //return the value at head
// char* peek(Node** head){
//   return (*head)->data;
// }
//
// char * print(Node *current){
//   if(current == NULL){
//     return NULL;
//   }
//   char * temp = current->data;
//   return temp;
// }
//
// //return the value at head
// // char * peek (Node * head){
// //   return head->data;
// // }
//
// //removes the element with the highest priority from the list
// void pop(Node** head){
//   Node* temp = *head;
//   (*head) = (*head)->next;
//   free(temp);
// }
//
// // void pop(Node * head){
// //   Node * temp = head;
// //   head = head->next;
// //   free(temp);
// // }
//
// //function to check is list is empty
// int isEmpty(Node** head){
//   return (*head) == NULL;
// }
//
// // int isEmpty(Node * head){
// //   return head == NULL;
// // }
//
// //function to push
// void push(Node** head, char* d){
//   if(isEmpty(head)){
//     head = malloc(sizeof(Node));
//   }
//   //create new node
//   Node* temp = newNode(d);
//   temp->next = (*head);
//   (*head) = temp;
// }
//
// // void push(Node * head, char * d){
// //   Node * start = malloc(sizeof


//ws(Node));
// //   start = head;
// //   Node * temp = newNode(d);
// //   temp->next = head;
// //   head = temp;
// // }
//
//
// // Node * copy(Node * head){
// //   Node * prev = head;
// //   Node * finalHead = prev;push
// //   head = head->next;


//ws
// //   while(!isEmpty(head)){
// //     prev = malloc(sizeof(Node));
// //     prev = prev->next;
// //     strcpy(prev->data, head->data);
// //     head = head->next;
// //   }
// //   prev->next = NULL;
// //   return finalHead;
// // }
//
// Node ** copy(Node ** head){
//   Node ** finalHead = malloc(sizeof(Node));
//   *finalHead = (*head);
//   Node * prev = (*head);
//
//   while(!isEmpty(head)){
//     *head = (*head)->next;
//     prev->next = malloc(sizeof(Node));
//     prev = prev->next;
//     strcpy(prev->data, (*head)->data);
//   }
//   return finalHead;
// }
