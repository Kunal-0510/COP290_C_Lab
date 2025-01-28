#include "Queue.h"

void QueueInit( QueueNode* node ){
    QueueNode*
}
void QueuePush( Node* node, Queue* queue){

    queue->tail->next = node;
    queue->tail = node;
}