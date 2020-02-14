#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

typedef struct LinkedList {
    int data;
    struct LinkedList *next;
} node; 

/*
 * Creates & returns a new node
 */
node* createNode(int data) {
    node* new_node;
    new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL)
        perror("Memory not allocated.\n");
    new_node -> next = NULL;
    new_node -> data = data;
    return new_node;
}

/*
 * Returns size of the given linked list
 */
int size(node* head) {
    int counter = 0;
    node* traversal_node = head;

    while(traversal_node != NULL) {
        traversal_node = traversal_node -> next;
        counter++;
    }
    
    return counter;
}

/**
 * Recursively computes and returns size of the linked list
 */
int size_recursive(node* head) {
    if (head == NULL)
        return 0;
    return 1 + size_recursive(head -> next);
}

/* add nodes */
node* addAtEnd(node* head, int data) {
    node* new_node = createNode(data);

    if (head == NULL) {
        head = new_node;
    } else {
        node* traversal_node = head;
        while(traversal_node -> next != NULL) {
            traversal_node = traversal_node -> next;
        }
        traversal_node -> next = new_node;
    }
    
    return head;
}

/* add at the beginning */
node* addAtBeginning(node* head, int data) {
    node* new_node = createNode(data);

    if (head == NULL) {
        head = new_node;
    } else {
        new_node -> next = head;
        head = new_node;
    }

    return head;
}

/* add at a specified index */
node* addAt(node* head, int data, int index) {
    int length = size(head);
    if (index < 0 || index > length) {
        perror("Error: Index out of bounds.\n");
    }

    if (index == 0)
        return addAtBeginning(head, data);
    
    int counter = 0;
    node* new_node = createNode(data);
    node* traversal_node = head;
    while(counter < index-1) {
        traversal_node = traversal_node -> next;
        counter++;
    }
    node* temp = traversal_node -> next;
    traversal_node -> next = new_node;
    new_node -> next = temp;

    return head;
}

/**
 * Adds a chain of linked list at a specified index
 */
node* addChainAt(node* head, node* chain, int index) {
    int length = size(head);
    if (index < 0 || index > length) {
        perror("Error: Index out of bounds.\n");
    }

    int counter = 0;
    node* traversal_node = head;
    while(counter < index-1) {
        traversal_node = traversal_node -> next;
        counter++;
    }
    node* other_half = traversal_node -> next;
    traversal_node -> next = chain;

    node* last_node_chain = chain;
    while(last_node_chain -> next != NULL) {
        last_node_chain = last_node_chain -> next;
    }
    last_node_chain -> next = other_half;

    return head;
}

/*
 * Assumes the list is empty and builds it.
 * Example comparator:
 * function (int a, int b) {
 *   return a < b;
 * }
 */
node* add_sort(node* head, int data, bool (*cmp)(int a, int b)) {
    int counter = 0;
    node* new_node = createNode(data);
    node* traversal_node = head;
    node* prev = traversal_node;

    // if head is empty
    if (head == NULL) {
        return new_node;
    }

    while(traversal_node != NULL) {
        if (cmp(data, traversal_node -> data)) {
            if (traversal_node == head) {
                new_node -> next = head;
                return new_node;
            }
            new_node -> next = traversal_node;
            prev -> next = new_node;
            return head;
        }
        prev = traversal_node;
        traversal_node = traversal_node -> next;
    }

    prev -> next = new_node;
    return head;
}


/* delete nodes */
node* deleteFromEnd(node* head) {
    if (head == NULL) {
        perror("Error: Empty list.\n");
    }

    if (head -> next == NULL) {
        head = NULL;
        return head;
    } else {
        node* traversal_node = head;
        while((traversal_node -> next) -> next != NULL) {
            traversal_node = traversal_node -> next;
        }
        node* to_be_deleted = traversal_node -> next;
        traversal_node -> next = NULL;
        free(to_be_deleted);
        return head;
    }
}

/* deletes from beginning */
node* deleteFromBeginning(node* head) {
    if (head == NULL) {
        perror("Error: Empty list.\n");
    }

    node* to_be_deleted = head;
    head = head -> next;
    free(to_be_deleted);
    return head;
}

/* deletes from a specified index */
node* deleteFrom(node* head, int index) {
    int length = size(head);
    if (index < 0 || index >= length) {
        perror("Error: Index out of bounds.\n");
    }

    if (index == 0)
        return deleteFromBeginning(head);
    
    int counter = 0;
    node* traversal_node = head;
    while (counter < index-1) {
        traversal_node = traversal_node -> next;
        counter++;
    }
    node* to_be_deleted = traversal_node -> next;
    traversal_node -> next = (traversal_node -> next) -> next;
    free(to_be_deleted);
    return head;
}

/* prints reverse */
void printReverse(node* head) {
    if (head == NULL) {
        printf("NULL");
    } else {
        printReverse(head -> next);
        printf(" ----> %d", head -> data);
    }
}

/* prints the linked list */
void printLinkedList(node* head) {
    printf("HEAD ----> ");
    node* traversal_node = head;
    while(traversal_node != NULL) {
        printf("%d ----> ", traversal_node -> data);
        traversal_node = traversal_node -> next;
    }
    printf("NULL\n");
}

node* copy(node* head) {
    node* head2 = NULL;
    node* current = head;
    node* tail = NULL;

    while (current != NULL) {
        if (head2 == NULL) {
            head2 = createNode(current -> data);
            tail = head2;
        } else {
            tail -> next = createNode(current -> data);
            tail = tail -> next;
        }
        current = current -> next;
    }
    return head2;
}

/* dummy comparator function */
bool comparator(int a, int b) {
    return a < b;
}

int main() {
    printf("-----LINKEDLIST-----\n");
    node* head = NULL;

    // head = add_sort(head, 5, comparator);
    // head = add_sort(head, 420, comparator);
    // head = add_sort(head, -34, comparator);
    // head = add_sort(head, 69, comparator);

    head = addAtEnd(head, 25);
    head = addAtEnd(head, 45);
    head = addAtEnd(head, 69);
    head = addAtEnd(head, 420);
    head = addAtBeginning(head, 619);
    head = addAt(head, 1, 3);
    node* head2 = copy(head);
    head2 = addAtEnd(head2, 200);
    
    // node* chain = NULL;
    // chain = addAtEnd(chain, 23);
    // chain = addAtEnd(chain, 3);
    // chain = addAtEnd(chain, 12);
    
    printLinkedList(head);
    printLinkedList(head2);
    // printf("%d size\n", size_recursive(head));
    // printReverse(head);
    // printf("\n");
    // printLinkedList(chain);
    // head = addChainAt(head, chain, 3);
    // printLinkedList(head);

    return 0;
}