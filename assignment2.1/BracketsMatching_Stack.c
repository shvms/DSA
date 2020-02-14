#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LINKEDLIST {
  char data;
  struct LINKEDLIST* next;
} node;

typedef struct STACK {
  int curr_size;
  node* top;
} stack;

stack* initialiseStack(stack* st);
node* createNode(char data);
void push(stack* st, char data);
char pop(stack* st);
bool isEmpty(stack* st);
void error(const char*, const char*);

int main() {
  stack* st; int i, data;
  st = initialiseStack(st);
  
  int n;
  printf("Enter size: ");
  scanf("%d ", &n);
  char* paran = (char*) malloc(sizeof(char) * n);
  for(int i=0;i<n;++i)
    scanf("%c", paran+i);

  for (int i=0;i<n;++i) {
    char elem = paran[i];
    if (elem == ')') {
      if (st -> top == NULL || (st -> top) -> data == ')')
        push(st, elem);
      else
        pop(st);
    } else {
      push(st, elem);
    }
  }

  if (st -> curr_size == 0)
    printf("Well formed.\n");
  else
    printf("Not well formed.\n");

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

node* createNode(char data) {
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

void push(stack* st, char data) {
  node* new_node = createNode(data);
  new_node -> next = st -> top;
  st -> top = new_node;
  st -> curr_size++;
}

char pop(stack* st) {
  if (isEmpty(st)) {
    error("Stack underflow", "pop");
  }
  int data = (st -> top) -> data;
  st -> top = (st -> top) -> next;
  st -> curr_size--;
  return data;
}