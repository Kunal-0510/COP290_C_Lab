#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedList {
    int data;
    struct LinkedList* next;
}LinkedList;

void add_node(LinkedList** head, int* hash);
void delete_node( LinkedList** head_ref, int* key);
void free_list(LinkedList** head);
int find_node(LinkedList* head, int hash);


#endif