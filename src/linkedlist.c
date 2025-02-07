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

void free_list(LinkedList* head) {
    LinkedList* temp;
    while (head != NULL) {
        temp = head;      // Store current node
        head = head->next; // Move to next node
        free(temp);       // Free current node
    }
}

int find_node(LinkedList* head, int hash){
    LinkedList* temp = head;
    int found=0;
    while(temp!=NULL && found==0){
        if(temp->data==hash){
            found=1;
        }
        else{
            temp= temp->next;
        }
    }
    return found;
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