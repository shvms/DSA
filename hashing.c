#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NODE {
    int val;
    struct NODE* next;
} node;

typedef struct htable {
    int size;
    node** table;
} hashtable;

int hash(hashtable* ht, int key);
node* createNode(int key);
hashtable* createHashTable(int size);
hashtable* insert(hashtable* ht, int key);
int search(hashtable* ht, int key);
hashtable* delete(hashtable* ht, int key);

/* assuming distinct values */
/* closed addressing */
int main() {
    hashtable* ht = createHashTable(10);
    int i;

    int values[5] = {8, 4, 3, 28, 98};

    for(i=0;i<5;++i)
        ht = insert(ht, values[i]);
    
    for(i=0;i<5;++i) {
        printf("hashtable[%d] = %d\n", search(ht, values[i]), values[i]);
    }

    printf("Value 21 at %d\n", search(ht, 21));
    printf("Value 78 at %d\n", search(ht, 78));

    delete(ht, 28);
    delete(ht, 98);
    delete(ht, 8);
    printf("After deleting 8, 98 & 28: key 98 is at %d\n", search(ht, 98));

    return 0;
}


int hash(hashtable* ht, int key) {
    return key % (ht -> size);
}

node* createNode(int key) {
    node* n = (node*) malloc(sizeof(node));
    n -> next = NULL;
    n -> val = key;
    return n;
}

hashtable* createHashTable(int size) {
    hashtable* h = (hashtable*) malloc(sizeof(hashtable));
    h -> size = size;
    h -> table = (node**) malloc(sizeof(node*) * size);
    int i;

    for(i=0;i<size;++i) {
        (h -> table)[i] = NULL;
    }

    return h;
}

hashtable* insert(hashtable* ht, int key) {
    int h = hash(ht, key);
    
    node* item = createNode(key);

    if ((ht -> table)[h] == NULL) {
        (ht -> table)[h] = item;
    } else {
        item -> next = (ht -> table)[h] -> next;
        (ht -> table)[h] -> next = item;
    }
    return ht;
}

int search(hashtable* ht, int key) {
    int h = hash(ht, key);
    
    node* curr = (ht -> table)[h];
    while (curr != NULL) {
        if (curr -> val == key)
            return h;
        curr = curr -> next;
    }
    return -1;
}

hashtable* delete(hashtable* ht, int key) {
    int h = hash(ht, key);
    node* to_be_deleted = NULL;
    
    node* curr = (ht -> table)[h];
    if (curr == NULL) return ht;
    
    if (curr -> val == key) {
        to_be_deleted = curr;
        (ht -> table)[h] = curr -> next;
        free(to_be_deleted);
        return ht;
    }

    while (curr -> next != NULL) {
        if ((curr -> next) -> val == key) {
            to_be_deleted = curr -> next;
            curr -> next = (curr -> next) -> next;
            free(to_be_deleted);
            return ht;
        }
        curr = curr -> next;
    }
    return ht;
}