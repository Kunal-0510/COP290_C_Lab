#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedList {
    int data;
    struct LinkedList* next;
}LinkedList;

LinkedList* add_node(LinkedList* head, int hash);
LinkedList* delete_node(LinkedList* head, int hash);

#endif