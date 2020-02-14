#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct Stack {
    int top;
    int capacity;
    int * arr;
} stack;

stack* initializeStack(stack*);
void push(stack*, int);
int pop(stack*);
bool isEmpty(stack*);
bool isFull(stack*);

int main() {
  stack* st = NULL; int i=0, data;
  st = initializeStack(st);
  printf("Stack initialized\n");
  
  for(;i<5;i++) {
    data = rand() % 100;
    push(st, data);
    printf("%d pushed.\n", data);
  }

  printf("\n-----------------------------------------------\n");

  while(true) {
    data = pop(st);
    printf("%d popped.\n", data);
  }

  return 0;
}

stack* initializeStack(stack* st) {
  st = (stack*) malloc(sizeof(stack));
  st -> top = -1;
  st -> capacity = MAX_SIZE;
  st -> arr = (int*) malloc(sizeof(int) * st -> capacity);
}

bool isEmpty(stack* st) {
  return st -> top == -1;
}

bool isFull(stack* st) {
  return (st -> capacity) - (st -> top) == 1;
}

void push(stack* st, int data) {
  if (isFull(st)) {
    printf("Error: Stack overflow.\n");
    exit(-1);
  }

  (st -> top)++;
  (st -> arr)[st -> top] = data;
}

int pop(stack* st) {
  int data;
  if (isEmpty(st)) {
    printf("Error: Stack underflow.\n");
    exit(-1);
  }
  
  data = (st -> arr)[st -> top];
  (st -> top)--;
  return data;
}
