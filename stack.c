#include "stack.h"

// Initialize the stack
void StackInit(Stack* stack) {
    stack->top = NULL;
}

// Push an element onto the stack
void push(Stack* stack, int value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack underflow\n");
        return -1; // Return an error value
    }
    StackNode* temp = stack->top;
    int poppedValue = temp->data;
    stack->top = temp->next;
    free(temp);
    return poppedValue;
}

// Check if the stack is empty
int isEmpty(Stack* stack) {
    return (stack->top == NULL);
}

// Peek at the top element of the stack without popping it
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        return -1;
    }
    return stack->top->data;
}