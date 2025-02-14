#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 60000000  // Adjust based on expected usage

typedef struct LinkedList {
    int data;
    struct LinkedList* next;
} LinkedList;


void init_memory_pool();
LinkedList* get_new_node(int hash);
void free_node(LinkedList* node);
void add_node(LinkedList** head, int hash);
void delete_node(LinkedList** head, int hash);
void free_list(LinkedList** head);

#endif // LINKEDLIST_H