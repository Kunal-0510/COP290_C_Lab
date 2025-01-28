#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "linkedlist.h"

typedef struct Node{

    int val ;
    LinkedList *InNeighbours;
    int type;
    int *cell1;
    int *cell2;
    int *op_val;

}Node;

struct Node* initialize_node();

#endif

