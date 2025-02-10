#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "linkedlist.h"

typedef struct Node{

    int isValid;
    int val ;
    int id;
    LinkedList *InNeighbours;
    LinkedList *OutNeighbours;
    int type;
    int cell1;
    int cell2;
    int op_val;
    char operator;
    
}Node;



void initialize_node(struct Node *node, int index);

#endif

