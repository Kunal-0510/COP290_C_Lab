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

void QueueNodeInit(QueueNode* qNode) {
    if (qNode == NULL) return;  // Prevent segfaults
    qNode->node = NULL;
    qNode->next = NULL;
}

void QueuePush(QueueNode* node, Queue* queue) {

    node->next = NULL;  // Important to prevent undefined behavior
    // printf("I reached here!!11111\n");
    if (isEmpty(queue)==1) {
        queue->head = node;
        queue->tail = node;
    } else {
        // printf("I reached here!!11112\n");
        
        queue->tail->next = node;
        // printf("I reached here!!11113\n");
    }
}

QueueNode* QueuePop(Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }

    QueueNode* temp = queue->head;
    queue->head = temp->next;

    if (queue->head == NULL) {  // If queue becomes empty
        queue->tail = NULL;
    }

    return temp;  // Caller must free the node after use
}