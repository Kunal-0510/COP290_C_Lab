#include "stack.h"

// Initialize the stack
void StackInit(Stack* stack) {
    stack->top = NULL;
}

// Push an element onto the stack
void push(Stack* stack, int value) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data = value;
    node->next = stack->top;
    stack->top = node;
}

// Pop an element from the stack
int pop(Stack* stack) {
    if (isempty(stack)) {
        fprintf(stderr, "Stack underflow\n");
        return -1; 
    }
    StackNode* temp = stack->top;
    int val = temp->data;
    stack->top = temp->next;
    free(temp);
    return val;
}

// Check if the stack is empty
int isempty(Stack* stack) {
    return (stack->top == NULL);
}

// Peek at the top element of the stack without popping it
int peek(Stack* stack) {
    if (isempty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        return -1;
    }
    return stack->top->data;
}