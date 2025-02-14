#include "linkedlist.h"

// Memory pool for LinkedList nodes
static LinkedList nodePool[MAX_NODES];
static LinkedList* freeList = NULL;  // Head of the free node list


void init_memory_pool() {
    for (int i = 0; i < MAX_NODES - 1; i++) {
        nodePool[i].next = &nodePool[i + 1];  
    }
    nodePool[MAX_NODES - 1].next = NULL;
    freeList = nodePool;  
}

LinkedList* get_new_node(int hash) {
    if (freeList == NULL) {
        printf("Memory limit reached!\n");
        return NULL;
    }
    LinkedList* new_node = freeList;
    freeList = freeList->next;  
    new_node->data = hash;
    new_node->next = NULL;
    return new_node;
}

// Return a node to the memory pool
void free_node(LinkedList* node) {
    if (node == NULL) return;
    node->next = freeList;
    freeList = node;
}

// Add a node to the linked list (Using Memory Pool)
void add_node(LinkedList** head, int hash) {
    LinkedList* new_node = get_new_node(hash);
    if (!new_node) return;  // Memory exhausted
    new_node->next = *head;
    *head = new_node;
}

// Delete a node from the linked list
void delete_node(LinkedList** head, int hash) {
    LinkedList* temp = *head, *prev = NULL;

    while (temp != NULL && temp->data != hash) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;  // Not found

    if (prev != NULL) prev->next = temp->next;
    else *head = temp->next;

    free_node(temp);
}

// Free entire linked list
void free_list(LinkedList** head) {
    LinkedList* temp = *head;
    while (temp != NULL) {
        LinkedList* next = temp->next;
        free_node(temp);
        temp = next;
    }
    *head = NULL;
}

void print_list(LinkedList* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    LinkedList* current = head;
    printf("List contents: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}