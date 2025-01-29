#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>  

LinkedList* add_node(LinkedList* head, int hash) {
    LinkedList* new_node = (LinkedList*)malloc(sizeof(LinkedList));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        return head;  
    }

    new_node->data = hash;
    new_node->next = head;  
    return new_node; 
} // Always use list= addnode(), not just addnode()


LinkedList* delete_node(LinkedList* head, int hash) {
    LinkedList* temp = head;
    LinkedList* prev = NULL;

    while (temp != NULL && temp->data != hash) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL) { 
        if (prev == NULL) {  
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
    }

    return head;
}