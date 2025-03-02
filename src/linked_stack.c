#include "linked_stack.h"

// Initialize the stack
void LinkedStackInit(LinkedStack* stack) {
    stack->top = NULL;
}

// Push an element onto the stack
void push_linked(LinkedStack* stack, LinkedList* value) {
    LinkedStackNode* newNode = (LinkedStackNode*)malloc(sizeof(LinkedStackNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    newNode->node = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop an element from the stack
LinkedList* pop_linked(LinkedStack* stack) {
    if (isempty_linked(stack)) {
        fprintf(stderr, "Stack underflow\n");
        return NULL; // Return an error value
    }
    LinkedStackNode* temp = stack->top;
    LinkedList* poppedValue = temp->node;
    stack->top = temp->next;
    free(temp);
    return poppedValue;
}

// Check if the stack is empty
int isempty_linked(LinkedStack* stack) {
    return (stack->top == NULL);
}

// Peek at the top element of the stack without popping it
LinkedList* linked_peek(LinkedStack* stack) {
    if (isempty_linked(stack)) {
        fprintf(stderr, "Stack is empty\n");
        return NULL;
    }
    return stack->top->node;
}