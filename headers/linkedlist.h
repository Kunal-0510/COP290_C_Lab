#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedList {
    int data;
    struct LinkedList* next;
}LinkedList;

LinkedList* add_node(LinkedList* head, int hash);
LinkedList* delete_node(LinkedList* head, int hash);
void free_list(LinkedList** head);
int find_node(LinkedList* head, int hash);
void print_list(LinkedList* head);

#endif