#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <stdio.h>

typedef struct QueueNode{

    Node* node;
    Node* next;

}QueueNode;

typedef struct Queue{

    QueueNode* head;
    QueueNode* tail;

}Queue;

void QueuePush( QueueNode* node , Queue* queue );
QueueNode* QueuePop( Queue* queue ); 
void QueueInit( Queue* queue );
void QueueNodeInit( QueueNode* node );

#endif
