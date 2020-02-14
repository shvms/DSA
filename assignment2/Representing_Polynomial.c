#include <stdio.h>
#include <stdlib.h>

typedef struct LINKEDLIST {
  int data;
  struct LINKEDLIST* next;
} node;

node* createNode(int data);
void push(node** head, int data);
void sum(node* head1, node* head2, int h);

int main() {
  int high_degree, i, coeff;
  node *head1=NULL, *head2=NULL;
  
  printf("Highest degree of polynomial: ");
  scanf("%d", &high_degree);

  printf("Enter coefficients for 1st polynomial.\n");
  for(i=0;i<=high_degree;i++) {
    printf("Coefficient of x^%d: ", i);
    scanf("%d", &coeff);
    push(&head1, coeff);
  }

  printf("Enter coefficients for 2nd polynomial.\n");
  for(i=0;i<=high_degree;i++) {
    printf("Coefficient of x^%d: ", i);
    scanf("%d", &coeff);
    push(&head2, coeff);
  }

  sum(head1, head2, high_degree);
}

node* createNode(int data) {
  node* new_node = (node*) malloc(sizeof(node));
  if (new_node == NULL) {
    printf("Memory not allocated.\n");
    exit(1);
  }

  new_node -> next = NULL;
  new_node -> data = data;
  return new_node;
}

void push(node** head, int data) {
  node* new_node = createNode(data);
  new_node -> next = *head;
  *head = new_node;
}

void sum(node* head1, node* head2, int h) {
  node* curr1 = head1;
  node* curr2 = head2;
  int s;
  while (curr1 != NULL) {
    s = (curr1 -> data) + (curr2 -> data);
    if (s != 0)
      printf("+ %dx^%d ", s, h);
    --h;
    curr1 = curr1 -> next;
    curr2 = curr2 -> next;
  }
}