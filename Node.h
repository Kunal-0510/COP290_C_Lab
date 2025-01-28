#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "linkedlist.h"

typedef struct Node{
<<<<<<< HEAD

    int val ;
    LinkedList *InNeighbours;
    int type;
    int *cell1;
    int *cell2;
    int *op_val;

}Node;
=======
>>>>>>> c00332c06cb6f7cf8f8dd89aed1239dbec2e456b

    int val ;
    LinkedList *InNeighbours;
    int type;
    int *cell1;
    int *cell2;
    int *op_val;

}Node;

void initialize_node(struct Node *node);

#endif

