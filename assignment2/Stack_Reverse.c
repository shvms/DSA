#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STR_LEN 20

typedef struct Stack {
    int top;
    int capacity;
    char * arr;
} stack;

stack* initializeStack(stack*, int);
void push(stack*, char);
char pop(stack*);
bool isEmpty(stack*);
bool isFull(stack*);

int main() {
  stack* st = NULL; int i=0, size;
  char str[MAX_STR_LEN], output;

  printf("Enter string to reverse: ");
  fgets(str, MAX_STR_LEN, stdin);

  size = strlen(str);

  st = initializeStack(st, size);
  
  for(;i<size;i++)
    push(st, str[i]);

  printf("Reversed string: ");

  for(i=0;i<size;i++) {
    output = pop(st);
    printf("%c", output);
  }
  printf("\n");

  return 0;
}

stack* initializeStack(stack* st, int length) {
  st = (stack*) malloc(sizeof(stack));
  st -> top = -1;
  st -> capacity = length;
  st -> arr = (char*) malloc(sizeof(char) * st -> capacity);

  return st;
}

bool isEmpty(stack* st) {
  return st -> top == -1;
}

bool isFull(stack* st) {
  return (st -> capacity) - (st -> top) == 1;
}

void push(stack* st, char data) {
  if (isFull(st)) {
    printf("Error: Stack overflow.\n");
    exit(-1);
  }

  (st -> top)++;
  (st -> arr)[st -> top] = data;
}

char pop(stack* st) {
  char data;
  if (isEmpty(st)) {
    printf("Error: Stack underflow.\n");
    exit(-1);
  }
  
  data = (st -> arr)[st -> top];
  (st -> top)--;
  return data;
}
