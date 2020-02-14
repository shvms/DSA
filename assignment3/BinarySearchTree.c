#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct BST {
  int val;
  struct BST* left;
  struct BST* right;
} TreeNode;

TreeNode* createTree(int val);
TreeNode* insert(TreeNode* root, int val);
void inorder(TreeNode* root);
TreeNode* max(TreeNode* root);
TreeNode* min(TreeNode* root);
void delete_node(TreeNode* root, int key);

int main() {
  /**
   *          5
   *        /   \
   *       2     9
   *      / \     \
   *     1   4    13
   */

  int choice, value;
  TreeNode *root = NULL, *temp;

  do {
    printf("------------------------ BINARY SEARCH TREE ------------------------\n");
    printf("1. Insert a new node.\n2. Delete a node.\n3. Find minimum.\n4. Find maximum.\n5. Print inorder traversal of the bst.\n6. Exit\n");
    printf("Enter choice (1-5): ");
    scanf("%d", &choice);

    switch(choice) {
      case 1: printf("Enter value: ");
              scanf("%d", &value);
              root = insert(root, value);
              printf("Inserted successfully.\n");
              break;
      case 2: printf("Enter value: ");
              scanf("%d", &value);
              delete_node(root, value);
              printf("Deleted successfully.\n");
              break;
      case 3: temp = min(root);
              if (temp == NULL)
                printf("Empty BST.\n");
              else
                printf("Minimum: %d\n", temp -> val);
              break;
      case 4: temp = max(root);
              if (temp == NULL)
                printf("Empty BST.\n");
              else
                printf("Maximum: %d\n", temp -> val);
              break;
      case 5: printf("Inorder: ");
              inorder(root);
              printf("\n");
              break;
      case 6: printf("Thanks for stopping by!\n");
              break;
      default: printf("You had one job...\n");
    }
  } while(choice != 6);

  return 0;
}

void inorder(TreeNode* root) {
  if (root != NULL) {
    inorder(root -> left);
    printf("%d ", root -> val);
    inorder(root -> right);
  }
}

TreeNode* createTree(int val) {
  TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
  node -> left = NULL;
  node -> right = NULL;
  node -> val = val;
  return node;
}

/*
 * Sets parent and child node when the child node is being searched for.
 * Both parent = NULL AND child = NULL when BST is empty.
 * parent = NULL AND child != NULL when searched item is root.
 * parent != NULL AND child != NULL when child NOT found.
 * NOTE: Initialise parent and child with NULL.
 */
void search(TreeNode* root, int key, TreeNode** parent, TreeNode** child) {
  if (root == NULL)
    return;
  
  while (root != NULL) {
    if (root -> val == key) {
      *child = root;
      return;
    } else if (root -> val > key) {
      *parent = root;
      root = root -> left;
    } else {
      *parent = root;
      root = root -> right;
    }
  }
}

TreeNode* insert(TreeNode* root, int val) {
  if (root == NULL)
    root = createTree(val);
  else if (val > root -> val)
    root -> right =  insert(root -> right, val);
  else
    root -> left = insert(root -> left, val);
  return root;
}

TreeNode* max(TreeNode* root) {
  if (root == NULL) return NULL;
  while (root -> right != NULL)
    root = root -> right;
  return root;
}

TreeNode* min(TreeNode* root) {
  if (root == NULL) return NULL;
  while (root -> left != NULL)
    root = root -> left;
  return root;
}

void delete_node(TreeNode* root, int key) {
  TreeNode *parent = NULL, *to_be_deleted = NULL;
  search(root, key, &parent, &to_be_deleted);
  
  /* deleting leaf node */
  if (to_be_deleted -> left == NULL && to_be_deleted -> right == NULL) {
    // if root to be deleted
    if (root == to_be_deleted) {
      free(root);
      return;
    }

    if (to_be_deleted == parent -> left) {
      parent -> left = NULL;
    } else {
      parent -> right = NULL;
    }
    free(to_be_deleted);
  }
  /* one subtree exists */
  else if (to_be_deleted -> left == NULL || to_be_deleted -> right == NULL) {
    if (to_be_deleted -> left == NULL) {            // right to be deleted
    //   if root
      if (to_be_deleted == root) {
        root = root -> right;
        free(to_be_deleted);
        return;
      }

      if (parent -> left == to_be_deleted) {
        parent -> left = to_be_deleted -> right;
      } else {
        parent -> right = to_be_deleted -> right;
      }
      free(to_be_deleted);
    } else {                                        // left to be deleted
      // if root
      if (to_be_deleted == root) {
        root = root -> left;
        free(to_be_deleted);
        return;
      }

      if (parent -> left == to_be_deleted) {
        parent -> left = to_be_deleted -> left;
      } else {
        parent -> right = to_be_deleted -> left;
      }
      free(to_be_deleted);
    }
  }
  /* both subtree exists */
  else {
    TreeNode* successor = min(to_be_deleted -> right);
    TreeNode* successor_parent = NULL;
    search(root, successor->val, &successor_parent, &successor);

    // if successor -> left == NULL
    if (successor == to_be_deleted -> right) {
      to_be_deleted -> val = successor -> val;
      successor_parent -> right = successor -> right;
      free(successor);
      return;
    }

    to_be_deleted -> val = successor -> val;
    successor_parent -> left = successor -> right;
    free(successor);
  }
}