#include "Node.h"

typedef struct Node{

    int val ;
    LinkedList *InNeighbours;
    int type;
    int *cell1;
    int *cell2;
    int *op_val;

}Node;

Node* initialize_node(){

    Node* cell;
    cell->val = 0;
    cell->InNeighbours = NULL;
    cell->type = 0;
    cell->cell1 = NULL;
    cell->cell2 = NULL;
    cell->op_val = NULL;

    return cell;
    
}