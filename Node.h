#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "linkedlist.h"

typedef struct Node {
    int val;                     // Value of the cell.
    struct LinkedList *InNeighbours;    // List of incoming neighbors.
    int type;                    // Type of the node (1 by default).
    int *cell1;                  // Pointer to another cell's value (for formulas).
    int *cell2;                  // Pointer to another cell's value (for formulas).
    int *op_val;                 // Pointer for operation value (e.g., addition result).
}Node;

void node(struct Node *node) {
    node->val = 0;
    node->InNeighbours = NULL;
    node->type = 1;
    node->cell1 = NULL;
    node->cell2 = NULL;
    node->op_val = NULL;
}

#endif
