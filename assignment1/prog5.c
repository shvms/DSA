#include<stdio.h>
#include<stdlib.h>

typedef struct LinkedList {
  int data;
  struct LinkedList *next;
} node;

// helper functions
void getValue(int*, const char*);

// linked list functions
node* createNode(int);
node* addAtBeginning(node*, int);
node* addAtEnd(node*, int);
node* addAt(node*, int, int);
node* deleteFrom(node*, int);
int size(node*);
node* reverse(node*);
void print(node*);


int main() {
  int choice, data, index, length;
  const char* DATA = "data";
  const char* INDEX = "index";
  const char THANKS[5] = {0xF0, 0x9F, 0x98, 0x84, '\0'};
  const char CURSED[5] = {0xF0, 0x9F, 0x98, 0xA1, '\0'};
  node* head = NULL;

  do {
    printf("\n--------------------------- Linked List ---------------------------\n");
    printf("1. Insert node at beginning\n");
    printf("2. Insert node at end\n");
    printf("3. Insert node at ith index\n");
    printf("4. Delete node from ith index\n");
    printf("5. Count the number of nodes in the list\n");
    printf("6. Display reversed linked list\n");
    printf("7. Display linked list\n");
    printf("8. Exit\n");
    printf("Choice (1-8): ");
    scanf("%d", &choice);

    switch(choice) {
      case 1: getValue(&data, DATA);
              head = addAtBeginning(head, data);
              printf("Data inserted.\n");
              break;
      case 2: getValue(&data, DATA);
              head = addAtEnd(head, data);
              printf("Data inserted.\n");
              break;
      case 3: getValue(&data, DATA);
              getValue(&index, INDEX);
              head = addAt(head, data, index);
              printf("Data inserted.\n");
              break;
      case 4: getValue(&index, INDEX);
              head = deleteFrom(head, index);
              printf("Data deleted.\n");
              break;
      case 5: length = size(head);
              printf("Size of the linked list: %d\n", length);
              break;
      case 6: head = reverse(head);
              print(head);
              printf("\n");
              break;
      case 7: print(head);
              printf("\n");
              break;
      case 8: printf("Thanks for stopping by %s\n", THANKS);
              break;
      default: printf("What did you just bring upon this cursed land? %s\n", CURSED);
    }
  } while (choice != 8);

  return 0;
}

void getValue(int * data, const char * requirement) {
  printf("Enter %s: ", requirement);
  scanf("%d", data);
}

node* createNode(int data) {
  node* new_node;
  new_node = (node*) malloc(sizeof(node));
  new_node -> next = NULL;
  new_node -> data = data;
  return new_node;
}

int size(node* head) {
  int counter = 0;
  node* traversal_node = head;

  while(traversal_node != NULL) {
    traversal_node = traversal_node -> next;
    counter++;
  }
  
  return counter;
}

node* addAtBeginning(node* head, int data) {
  node* new_node = createNode(data);

  if (head == NULL) {
    head = new_node;
  } else {
    new_node -> next = head;
    head = new_node;
  }

  return head;
}

node* addAtEnd(node* head, int data) {
  node* new_node = createNode(data);

  if (head == NULL) {
    head = new_node;
  } else {
    node* traversal_node = head;
    while(traversal_node -> next != NULL) {
      traversal_node = traversal_node -> next;
    }
    traversal_node -> next = new_node;
  }

  return head;
}

node* addAt(node* head, int data, int index) {
  int length = size(head);
  if (index < 0 || index > length) {
    printf("Error: Index out of bounds.\n");
    exit(-1);
  }

  if (index == 0)
    return addAtBeginning(head, data);
    
  int counter = 0;
  node* new_node = createNode(data);
  node* traversal_node = head;
  while(counter < index-1) {
    traversal_node = traversal_node -> next;
    counter++;
  }
  node* temp = traversal_node -> next;
  traversal_node -> next = new_node;
  new_node -> next = temp;

  return head;
}

node* deleteFrom(node* head, int index) {
  int length = size(head);
  if (index < 0 || index >= length) {
    printf("Error: Index out of bounds.\n");
    exit(-1);
  }

  if (index == 0) {
    node* to_be_deleted = head;
    head = head -> next;
    free(to_be_deleted);
    return head;
  }
  
  int counter = 0;
  node* traversal_node = head;
  while (counter < index-1) {
    traversal_node = traversal_node -> next;
    counter++;
  }
  node* to_be_deleted = traversal_node -> next;
  traversal_node -> next = (traversal_node -> next) -> next;
  free(to_be_deleted);
  return head;
}

node* reverse(node* head) {
  node* current = head;
  node* nxt = NULL;
  node* prev = NULL;
  while(current != NULL){
    // storing current next
    nxt = current -> next;
    current -> next = prev;
    
    // update
    prev = current;
    current = nxt;
  }
  head = prev;

  return head;
}

// void printReverse(node* head) {
//   if (head == NULL) {
//     printf("NULL");
//   } else {
//     printReverse(head -> next);
//     printf(" ----> %d", head -> data);
//   }
// }

void print(node* head) {
  printf("HEAD ----> ");
  node* traversal_node = head;
  while(traversal_node != NULL) {
    printf("%d ----> ", traversal_node -> data);
    traversal_node = traversal_node -> next;
  }
  printf("NULL\n");
}