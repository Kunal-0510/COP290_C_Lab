#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

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