#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

/*
Stack Module

This module defines the stack data structure used for various operations within the spreadsheet. 
It includes functions to initialize the stack, push and pop elements, check if the stack is empty, and peek at the top element.
*/

// Structure for a stack node
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

// Structure for the stack
typedef struct Stack {
    StackNode* top;
} Stack;

// Function declarations
void StackInit(Stack* stack);
void push(Stack* stack, int value);
int pop(Stack* stack);
int isempty(Stack* stack);
int peek(Stack* stack);

#endif