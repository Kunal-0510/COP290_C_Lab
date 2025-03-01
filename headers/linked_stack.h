#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
// Structure for a stack nod
typedef struct LinkedStackNode {
    LinkedList* node;
    struct LinkedStackNode* next;
} LinkedStackNode;
// Structure for the stack
typedef struct LinkedStack {
    LinkedStackNode* top;
} LinkedStack;

// Function declarations
void LinkedStackInit(LinkedStack* stack);
void push_linked(LinkedStack* stack, LinkedList* value);
LinkedList* pop_linked(LinkedStack* stack);
int isempty_linked(LinkedStack* stack);
LinkedList* linked_peek(LinkedStack* stack);

#endif