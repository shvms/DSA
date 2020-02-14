#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct Node {
  int data;
  struct Node *next;
} node;

node* insertAtEnd(node*, int);
node* traversal(node*);
node* createNode(int);
void print(node*);

int main() {
  node* head = NULL;
  int input, i;

  for(i=0;i<SIZE;i++) {
    input = rand() % 50;
    printf("#%d) Insert At End: %d\n", (i+1), input);
    head = insertAtEnd(head, input);
  }

  printf("LINKED LIST: ");
  print(head);
  printf("\n");

  return  0;
}

node* createNode(int data) {
  node* new_node;
  new_node = (node*) malloc(sizeof(node));
  new_node -> next = NULL;
  new_node -> data = data;

  return new_node;
}

node* traversal(node* head) {
  node* traversal_node = head;

  // head == NULL check done in `insertAtEnd`
  // before invoking `traversal`
  while (traversal_node -> next != NULL) {
    traversal_node = traversal_node -> next;
  }
  return traversal_node;
}

node* insertAtEnd(node* head, int data) {
  node* new_node = createNode(data);

  if (head == NULL) {
    head = new_node;
    return head;
  }

  node* traversal_node = traversal(head);
  traversal_node -> next = new_node;
  return head;
}

void print(node* head) {
  printf("HEAD ----> ");

  node* traversal_node = head;
  while(traversal_node != NULL) {
    printf("%d ----> ", traversal_node -> data);
    traversal_node = traversal_node -> next;
  }
  printf("NULL");
}