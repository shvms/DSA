#include <stdio.h>
#include <stdlib.h>

typedef struct LINKEDLIST {
  int data;
  struct LINKEDLIST* next;
} node;

node* createNode(int data);
void push(node** head, int data);
void FrontBackSplit(node* source, node** frontRef, node** backRef);
void printLinkedList(node* head);

int main(void) {
  node* head = NULL;
  node* front = NULL;
  node* back = NULL;
  int i, data;

  for(int i=0;i<8;i++) {
    data = rand() % 50;
    push(&head, data);
    printf("%d inserted.\n", data);
  }
  printLinkedList(head);
  printf("--------------------------------------------------------\n");
  FrontBackSplit(head, &front, &back);
  printLinkedList(front);
  printLinkedList(back);

  return 0;
}

node* createNode(int data) {
  node* new_node = (node*) malloc(sizeof(node));
  if (new_node == NULL) {
    printf("Memory not allocated.\n");
    exit(1);
  }
  new_node -> next = NULL;
  new_node -> data = data;
  return new_node;
}

void push(node** head, int data) {
  node* new_node = createNode(data);

  if (*head == NULL) {
    *head = new_node;
  } else {
    node* traversal_node = *head;
    while(traversal_node -> next != NULL) {
      traversal_node = traversal_node -> next;
    }
    traversal_node -> next = new_node;
  }
}

void FrontBackSplit(node* source, node** frontRef, node** backRef) {
  node* slow = source;
  node* fast = source;

  while ((fast -> next != NULL) && ((fast -> next) -> next != NULL)) {
    push(frontRef, slow -> data);
    fast = (fast -> next) -> next;
    slow = slow -> next;
  }
  push(frontRef, slow -> data);
  slow = slow -> next;

  while (slow != NULL) {
    push(backRef, slow -> data);
    slow = slow -> next;
  }
}

void printLinkedList(node* head) {
  printf("HEAD ----> ");
  node* traversal_node = head;
  while(traversal_node != NULL) {
      printf("%d ----> ", traversal_node -> data);
      traversal_node = traversal_node -> next;
  }
  printf("NULL\n");
}