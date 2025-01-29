#include "Queue.h"

void QueueInit( Queue* queue ){

    queue->head = NULL;
    queue->tail = NULL;

}

int isEmpty( Queue* queue ){

    if( queue->head == NULL ){
        return 1;
    }
    
    return 0; 

}
void QueueNodeInit( QueueNode* qNode ){

    qNode->node = NULL;
    qNode->next = NULL;

}

void QueuePush( QueueNode* node, Queue* queue){

    if( isEmpty( queue ) == 1 ){
        
        queue->head = node;
        queue->tail = node;

        return;

    }

    queue->tail->next = node;
    queue->tail = node;

}

QueueNode* QueuePop( Queue* queue ){
    
    if( isEmpty( queue ) == 1 ){
        return NULL;
    }
    QueueNode* temp = queue->head;
    queue->head = temp->next;
    
    return temp;

}