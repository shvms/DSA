#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LINKEDLIST {
  int data;
  struct LINKEDLIST* next;
} node;

typedef struct QUEUE {
  node* front;
  node* rear;
  int capacity;
  int curr_size;
} queue;

queue* initialiseQueue(queue*);
void enqueue(queue*, int);
int dequeue(queue*);
bool isEmpty(queue*);
node* createNode(int data);
void error(const char*, const char*);

int main() {
  queue* qu; int data, i;
  qu = initialiseQueue(qu);
  printf("Queue initialised.\n");

  for(i=0;i<5;i++) {
    data = rand() % 50;
    enqueue(qu, data);
    printf("%d enqueued.\n", data);
  }

  printf("---------------------------------------------\n");

  for(int i=0;i<5;++i) {
      printf("%d dequeued.\n", dequeue(qu));
  }

  return 0;
}

void error(const char* err, const char* at) {
  printf("ERROR: %s at %s\n", err, at);
  exit(-1);
}

node* createNode(data) {
  node* new_node = (node*) malloc(sizeof(node));
  if (new_node == NULL) {
    error("Not allocated", "createNode");
  }
  new_node -> next = NULL;
  new_node -> data = data;
  return new_node;
}

bool isEmpty(queue* qu) {
  return qu -> curr_size == 0;
}

queue* initialiseQueue(queue* qu) {
  qu = (queue*) malloc(sizeof(qu));
  if(qu == NULL) {
    error("Not allocated", "initialiseQueue");
  }

  qu -> front = NULL;
  qu -> rear = NULL;
  qu -> curr_size = 0;

  return qu;
}

void enqueue(queue* qu, int data) {
  node* new_node = createNode(data);
  if (qu -> front == NULL) {
    qu -> front = new_node;
    qu -> rear = qu -> front;
  } else {
    (qu -> rear) -> next = new_node;
    qu -> rear = new_node;
  }
  qu -> curr_size++;
}

int dequeue (queue* qu) {
  if (isEmpty(qu)) {
    error("Queue empty", "dequeue");
  }
  int data;
  node* to_be_deleted = qu -> front;
  data = to_be_deleted -> data;
  qu -> front = (qu -> front) -> next;
  qu -> curr_size--;

  if (qu -> front == qu -> rear) {
    qu -> front = NULL;
    qu -> rear = NULL;
  }

  free(to_be_deleted);
  return data;
}