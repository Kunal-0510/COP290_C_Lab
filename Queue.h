#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <stdio.h>

typedef struct QueueNode{

    Node* node;
    Node* next;

};

typedef struct Queue{

    QueueNode* head;
    QueueNode* tail;

}Queue;

void QueuePush( Node* node , Queue* queue );
void QueuePop( Queue* queue ); 

#endif
