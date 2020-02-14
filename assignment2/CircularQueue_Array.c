#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct Queue {
  int front;
  int back;
  int capacity;
  int current_size;
  int * arr;
} queue;

queue* initializeQueue(queue* q, int size);
void enqueue(queue* q, int data);
int dequeue(queue* q);
int length(queue* q);
int peek(queue* q);
bool isEmpty(queue* q);
bool isFull(queue* q);
void printQueue(queue* q);

int main() {
  queue* q = NULL;
  int data, i;

  q = initializeQueue(q, MAX_SIZE);
  printf("Queue initialized.\n");

  for(i=0;i<10;i++) {
    data = rand() % 50;
    enqueue(q, data);
    printQueue(q);
    printf("%d enqueued.\n", data);
  }

  printf("--------------------------------------------------------------------\n");
  i=0;
  while(i <= 2) {
    data = dequeue(q);
    printQueue(q);
    printf("%d dequeued.\n", data);
    i++;
  }
  printf("\n--------------------------------------------------------------------\n");
  enqueue(q, 69);
  printQueue(q);

  printf("\n--------------------------------------------------------------------\n");
  enqueue(q, 420);
  printQueue(q);

  printf("\n--------------------------------------------------------------------\n");
  printf("%d dequeued.", dequeue(q));
  printQueue(q);

  return 0;
}

queue* initializeQueue(queue* q, int size) {
  q = (queue*) malloc(sizeof(queue));
  q -> front = 0;
  q -> back = -1;
  q -> capacity = size;
  q -> arr = (int*) malloc(sizeof(int) * q -> capacity);
  q -> current_size = 0;

  return q;
}

bool isEmpty(queue* q) {
  return q -> current_size == 0;
}

bool isFull(queue* q) {
  return q -> current_size == q -> capacity;
}

void enqueue(queue* q, int data) {
  if (isFull(q)) {
    printf("Queue is full.\n");
    exit(-1);
  }

  q -> back++;
  q -> arr[q -> back % q -> capacity] = data;
  q -> current_size++;
}

int dequeue(queue* q) {
  int data;
  if (isEmpty(q)) {
    printf("Queue empty.\n");
    exit(-1);
  }

  data = (q -> arr)[q -> front % q -> capacity];
  q -> front++;
  q -> current_size--;

  return data;
}

int length(queue* q) {
  return q -> current_size;
}

int peek(queue* q) {
  return q -> arr[q -> back % q -> capacity];
}

void printQueue(queue* q) {
  int i=0, item;
  printf("| ");
  for(;i<q->capacity;i++) {
    if ((item = (q -> arr[i])))
      printf("%d | ", item);
    else
      printf("  | ");
  }
  printf("\n");
}