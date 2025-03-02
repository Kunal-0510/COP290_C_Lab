#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*
LinkedList Module

This module defines the linked list data structure used for managing dependencies between nodes in the spreadsheet. 
It includes functions to add and delete nodes, free the entire list, and find nodes within the list.
*/

typedef struct LinkedList {
    int data;
    struct LinkedList* next;
} LinkedList;

void add_node(LinkedList** head, int* hash);
void delete_node(LinkedList** head_ref, int* key);
void free_list(LinkedList** head);
int find_node(LinkedList* head, int hash);

#endif