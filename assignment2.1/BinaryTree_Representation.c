#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
  int data;
  struct NODE* left;
  struct NODE* right;
} node;

node* createNode(int);
node* insert(node*, int);
int count(node*, int);

int main() {
/**
 *          5
 *        /   \
 *       3     7
 *      / \   / \
 *     1   4 6  13
 */
  int c = 0;
  node* root = NULL;
  root = insert(root, 5);
  root = insert(root, 3);
  root = insert(root, 7);
  root = insert(root, 1);
  root = insert(root, 4);
  root = insert(root, 6);
  root = insert(root, 13);
  c = count(root, c);
  printf("%d leaves.\n", c);
  
  return 0;
}

node* createNode(int elem) {
  node* new_node = (node*) malloc(sizeof(node));
  if (new_node == NULL) {
      printf("Memory couldn't be allocated.\n");
      exit(1);
  }
  new_node -> left = NULL;
  new_node -> right = NULL;
  new_node -> data = elem;
  return new_node;
}

node* insert(node* root, int elem) {
  if (root == NULL)
      return createNode(elem);
  if (elem < (root -> data))
      root -> left = insert(root -> left, elem);
  else
      root -> right = insert(root -> right, elem);
  return root;
}

int count(node* root, int value) {
  if (root != NULL) {
    if (root -> left == NULL && root -> right == NULL) { return 1; }

    int left_leaf = count(root -> left, value);
    int right_leaf = count(root -> right, value);

    return left_leaf + right_leaf;
  }
  return value;
}
