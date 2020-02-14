#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LINKEDLIST {
  int data;
  struct LINKEDLIST* next;
} node;

typedef struct STACK {
  int curr_size;
  node* top;
} stack;

stack* initialiseStack(stack* st);
node* createNode(int data);
void push(stack* st, int data);
int pop(stack* st);
bool isEmpty(stack* st);
void error(const char*, const char*);

int main() {
  stack* st; int i, data;
  st = initialiseStack(st);
  printf("Stack initiliazed.\n");

  for(i=0;i<5;i++) {
    data = rand()%50;
    push(st, data);
    printf("\n%d pushed.\n", data);
  }

  printf("-------------------------------------------------");

  while(true) {
    data = pop(st);
    printf("\n%d popped.\n", data);
  }

  return 0;
}

void error(const char* err, const char* at) {
  printf("ERROR: %s at %s\n", err, at);
  exit(-1);
}

stack* initialiseStack(stack* st) {
  st = (stack*) malloc(sizeof(stack));
  if (st == NULL) {
    error("Not allocated", "initialiseStack");
  }
  st -> top = NULL;
  st -> curr_size = 0;

  return st;
}

node* createNode(int data) {
  node* new_node = (node*) malloc(sizeof(node));
  if (new_node == NULL) {
    error("Not allocated", "createNode");
  }
  new_node -> next = NULL;
  new_node -> data = data;
  return new_node;
}

bool isEmpty(stack* st) {
  return st -> curr_size == 0;
}

void push(stack* st, int data) {
  node* new_node = createNode(data);
  new_node -> next = st -> top;
  st -> top = new_node;
  st -> curr_size++;
}

int pop(stack* st) {
  if (isEmpty(st)) {
    error("Stack underflow", "pop");
  }
  int data = (st -> top) -> data;
  st -> top = (st -> top) -> next;
  st -> curr_size--;
  return data;
}