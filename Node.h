#include <stdio.h>
#include "linkedlist.h"

struct Node{

    int val = 0;
    LinkedList *InNeighbours = NULL;
    int type = 1;
    int *cell1 = NULL;
    int *cell2 = NULL;
    int *op_val = NULL;

};