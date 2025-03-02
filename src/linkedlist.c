#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

#define POOL_SIZE 1024

typedef struct MemoryPool {
    LinkedList* nodes;
    int index;
    struct MemoryPool* next;
} MemoryPool;

MemoryPool* pool = NULL;
LinkedList* free_list_head = NULL;

// Allocates a new memory pool for linked list nodes
void allocate_pool() {
    MemoryPool* new_pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (!new_pool) {
        printf("Memory pool allocation failed!\n");
        return;
    }
    new_pool->nodes = (LinkedList*)malloc(POOL_SIZE*sizeof(LinkedList));
    if (!new_pool->nodes) {
        printf("Node block allocation failed!\n");
        free(new_pool);
        return;
    }
    new_pool->index = 0;
    new_pool->next = pool;
    pool = new_pool;
}

// Retrieves a node from the memory pool
LinkedList* get_node_from_pool() {
    if (free_list_head) {
        LinkedList* node = free_list_head;
        free_list_head = free_list_head->next;
        return node;
    }
    if (!pool || pool->index >= POOL_SIZE) {
        allocate_pool();
        if (!pool) return NULL;
    }
    return &pool->nodes[pool->index++];
}

// Adds a node to the linked list
void add_node(LinkedList** head, int* hash) {
    LinkedList* new_node = get_node_from_pool();
    if (!new_node) {
        printf("Memory allocation failed!\n");
        return;
    }
    new_node->data = *hash;
    new_node->next = *head;
    *head = new_node;
}

// Deletes a node from the linked list
void delete_node(LinkedList** head_ref, int* key) {
    if (*head_ref == NULL) return;
    LinkedList** curr = head_ref;
    while (*curr != NULL) {
        if ((*curr)->data == *key) {
            LinkedList* temp = *curr;
            *curr = (*curr)->next;
            temp->next = free_list_head;
            free_list_head = temp;
            return;
        }
        curr = &((*curr)->next);
    }
}

// Frees the entire linked list
void free_list(LinkedList** head) {
    while (*head != NULL) {
        LinkedList* temp = *head;
        *head = (*head)->next;
        temp->next = free_list_head;
        free_list_head = temp;
    }
    *head = NULL;
}

// Finds a node in the linked list
int find_node(LinkedList* head, int hash) {
    LinkedList* temp = head;
    while (temp != NULL) {
        if (temp->data == hash) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// Frees all memory pools
void free_memory_pools() {
    while (pool) {
        MemoryPool* temp = pool;
        pool = pool->next;
        free(temp->nodes);
        free(temp);
    }
    free_list_head = NULL;
}
