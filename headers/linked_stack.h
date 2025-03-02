#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

/*
LinkedStack Module

This module defines the linked stack data structure used for managing linked lists within the spreadsheet. 
It includes functions to initialize the stack, push and pop elements, check if the stack is empty, and peek at the top element.
*/

// Structure for a stack node
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