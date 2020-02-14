#include <stdio.h>
#include <stdlib.h>

typedef struct DOUBLELINKEDLIST {
  int data;
  struct DOUBLELINKEDLIST* prev;
  struct DOUBLELINKEDLIST* next;
} node;

node* createNode(int data);
void addAt(node** head, int data, int index);
void deleteFrom(node** head, int index);
void reverse(node** head);
void traverse(node* head);
void error(char* msg, char* at);
int size(node* head);
void getData(char* data, int* variable);

int main() {
  int choice, data, index;
  node* head = NULL;
  do {
    printf("\n--------------------DOUBLY LINKED LIST--------------------\n");
    printf("1. Insert a node at a specified position\n");
    printf("2. Delete a node from a specified position\n");
    printf("3. Count the number of nodes in the linked list\n");
    printf("4. Reverse the linked list\n");
    printf("5. Traverse & print list.\n");
    printf("6. Exit\n");
    printf("Choice (1-6): ");
    scanf("%d", &choice);

    switch(choice) {
      case 1: getData("data", &data);
              getData("index", &index);
              addAt(&head, data, index);
              printf("Data inserted.\n");
              break;
      case 2: getData("index", &index);
              deleteFrom(&head, index);
              printf("Data deleted.\n");
              break;
      case 3: printf("Size: %d\n", size(head));
              break;
      case 4: reverse(&head);
              printf("Reversed.\n");
              break;
      case 5: traverse(head);
              break;
      case 6: printf("Thanks for stopping by! :)\n");
              break;
      default: printf("You had one job! :p\n");
    }
  } while (choice != 6);

  return 0;
}

void getData(char* data, int* var) {
  printf("Enter %s: ", data);
  scanf("%d", var);
}

void error(char* msg, char* at) {
  printf("ERROR: %s at %s.\n", msg, at);
  free(msg);
  free(at);
  exit(1);
}

node* createNode(int data) {
  node* new_node = (node*) malloc(sizeof(node));
  if (new_node == NULL) {
    error("Memory not allocated", "createNode");
  }
  new_node -> data = data;
  new_node -> next = NULL;
  new_node -> prev = NULL;
  return new_node;
}

int size(node* head) {
  node* traversal_node = head;
  int count = 0;
  while(traversal_node != NULL) {
    traversal_node = traversal_node -> next;
    ++count;
  }
  return count;
}

void addAt(node** head, int data, int index) {
  if (index < 0 || index > size(*head))
    error("Index out of bounds", "addAt");
  
  node* new_node = createNode(data);
  if (index == 0) {
    if (*head == NULL) {
      *head = new_node;
      return;
    }
    new_node -> next = *head;
    (*head) -> prev = new_node;
    *head = new_node;
    return; 
  }

  node* traversal_node = *head;
  int i;
  for (i=0;i<index-1;i++) {
    traversal_node = traversal_node -> next;
  }
  node* temp = traversal_node -> next;
  traversal_node -> next = new_node;
  new_node -> prev = traversal_node;
  new_node -> next = temp;
  if (temp != NULL)
    temp -> prev = new_node;
}

void deleteFrom(node** head, int index) {
  if (index < 0 || index >= size(*head)) {
    error("Index out of bounds", "deleteFrom");
  }

  if (index == 0) {
    node* to_be_deleted = *head;
    *head = (*head) -> next;
    (*head) -> prev = NULL;
    free(to_be_deleted);
    return;
  }

  int i=0;
  node* traversal_node = *head;
  for(;i<index;i++) {
    traversal_node = traversal_node -> next;
  }
  node* to_be_deleted = traversal_node;
  (traversal_node -> prev) -> next = traversal_node -> next;
  if (traversal_node -> next != NULL)
    (traversal_node -> next) -> prev = traversal_node -> prev;
  free(to_be_deleted);
}

void reverse(node** head) {
  if (*head == NULL)
    return ;
  
  node* last = *head;
  node* current = *head;
  while (current != NULL) {
    if (current -> next != NULL)
      last = current -> next;

    node* temp = current -> next;
    current -> next = current -> prev;
    current -> prev = temp;
    current = temp;
  }
  *head = last;
}

void traverse(node* head) {
  if (head == NULL) {
    printf("NULL\n");
    return;
  }
  node* traversal_node = head;
  while (traversal_node != NULL) {
    printf("%d  ", traversal_node -> data);
    traversal_node = traversal_node -> next;
  }
  printf("\n");
}