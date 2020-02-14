#include <stdio.h>
#include <stdlib.h>

typedef struct LINKEDLIST {
  int data;
  struct LINKEDLIST* next;
} node;

node* createNode(int data);
void push_sorted(node** head, int data);
node* SortedMerge(node* a, node* b);
void printLinkedList(node* head);

int main() {
  int len = 5, i, num;
  node *head1 = NULL, *head2 = NULL;

  for(i=0;i<len;i++) {
    num = rand() % 50;
    
    push_sorted(&head1, num);
    printf("%d inserted.\n", num);
  }
  printLinkedList(head1);
  printf("--------------------------------------------\n");
  for(i=0;i<len;i++) {
    num = rand() % 50;
    push_sorted(&head2, num);
    printf("%d inserted.\n", num);
  }
  printLinkedList(head2);
  printf("--------------------------------------------\n");
  node* merged = SortedMerge(head1, head2);
  printf("Merged list: ");
  printLinkedList(merged);
}

node* createNode(int data) {
  node* new_node = (node*) malloc(sizeof(node));
  if (new_node == NULL) {
    printf("Memory can't be allocated.\n");
    exit(1);
  }
  new_node -> next = NULL;
  new_node -> data = data;
  return new_node;
}

void push_sorted(node** head, int data) {
  node* new_node = createNode(data);
  if (*head == NULL) {
    *head = new_node;
    return;
  }

  if (data < (*head) -> data) {
    new_node -> next = *head;
    *head = new_node;
    return;
  }

  node* current = *head;
  while(current -> next != NULL) {
    if (data < (current -> next) -> data) {
      new_node -> next = current -> next;
      current -> next = new_node;
      return;
    }
    current = current -> next;
  }

  current -> next = new_node;
}

node* SortedMerge(node* a, node* b) {
  if (a == NULL) {
    return b;
  }
  if(b == NULL) {
    return a;
  }

  node* min = (a -> data) < (b -> data) ? a : b;
  node* merged = min;
  node* current_merged = merged;

  if (min == a)
    a = a -> next;
  else
    b = b -> next;

  while(a != NULL && b != NULL) {
    if ((a -> data) <= (b -> data)) {
      current_merged -> next = a;
      current_merged = current_merged -> next;
      a = a -> next;
    } else {
      current_merged -> next = b;
      current_merged = current_merged -> next;
      b = b -> next;
    }
  }

  if (a == NULL)
    a = b;
  while(a != NULL) {
    current_merged -> next = a;
    current_merged = current_merged -> next;
    a = a -> next;
  }
  return merged;
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