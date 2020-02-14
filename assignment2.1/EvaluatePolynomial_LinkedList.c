#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct LinkedList {
  float coeff;
  float exponent;
  struct LinkedList *next;
} term;

term* createTerm(float coeff, float exponent);
void addTerm(term** expression_head, float coeff, float exponent);
float evaluate(term* expression, float x);

int main() {
  term* expression = NULL;

  /*
   * f(x) = x^4 + 4x^2 - 7
   */
  addTerm(&expression, 1, 4);
  addTerm(&expression, 4, 2);
  addTerm(&expression, -7, 0);
  float x = 2.5;
  float result = evaluate(expression, x);

  printf("f(x=2.5) = x^4 + 4x^2 - 7 = %f\n", result);
  
  return 0;
}

term* createTerm(float coeff, float exponent) {
  term* new_term = (term*) malloc(sizeof(term));
  if (new_term == NULL) {
    printf("Memory not allocated :(\n");
    exit(1);
  }

  new_term -> coeff = coeff;
  new_term -> exponent = exponent;
  new_term -> next = NULL;

  return new_term;
}

void addTerm(term** expression_head, float coeff, float exponent) {
  term* t = createTerm(coeff, exponent);
  if (*expression_head == NULL) {
    *expression_head = t;
  } else {
    term* current = *expression_head;
    while (current -> next != NULL) {
      current = current -> next;
    }
    current -> next = t;
  }
}

float evaluate(term* expression_head, float x) {
  float result = 0.0;

  term* curr = expression_head;
  while(curr != NULL) {
    result += (curr -> coeff) * pow(x, curr -> exponent);
    curr = curr -> next;
  }
  return result;
}