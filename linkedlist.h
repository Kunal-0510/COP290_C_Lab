#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedList {
    int data;
    struct LinkedList* next;
}LinkedList;

#endif