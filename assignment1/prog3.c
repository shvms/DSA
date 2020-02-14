#include <stdio.h>
#include <stdlib.h>

typedef struct ARRAY {
  int* arr;
  int size;
} array;

array* createArray(array*, int);
void insert(array*, int, int);
void del(array*, int);
void print(array*);

int main(void) {
  array* A; int i;
  A = createArray(A, 10);
  for(i=0;i<A->size;i++) {
    A -> arr[i] = rand() % 50;
  }
  printf("CURRENT ARRAY: ");
  print(A);
  insert(A, 100, 6);
  printf("AFTER INSERTING 100 AT 6: ");
  print(A);
  del(A, 6);
  printf("AFTER DELETING 100 FROM 6: ");
  print(A);

  return 0;
}

array* createArray(array* A, int size) {
  A = (array*) malloc(sizeof(array));
  A -> size = size;
  A -> arr = (int*) malloc(sizeof(int) * size);
  return A;
}

void insert(array* A, int data, int index) {
  int i;
  A -> size++;
  int* temp = (int*) malloc(sizeof(int) * A -> size);
  for(i=0;i<index;i++) {
    temp[i] = A -> arr[i];
  }
  temp[index] = data;
  for(i=index+1;i<A->size;i++) {
    temp[i] = A -> arr[i-1];
  }
  free(A -> arr);
  A -> arr = temp;
}

void del(array* A, int index) {
  int i;
  A -> size--;
  int* temp = (int*) malloc(sizeof(int) * A -> size);
  for(i=0;i<index;i++) {
    temp[i] = A -> arr[i];
  }
  for(i=index+1;i<=A->size;i++) {
    temp[i-1] = A -> arr[i];
  }
  free(A -> arr);
  A -> arr = temp;
}

void print(array* A) {
  int i;
  for(i=0;i<A->size;i++) {
    printf("%d ", A -> arr[i]);
  }
  printf("\n");
}