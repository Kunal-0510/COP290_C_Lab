#include "Node.h"

//initialize the node
void initialize_node(struct Node *node, int id) {
    node->isValid=1;
    node->val = 0;
    node->id= id;
    node->OutNeighbours=NULL;
    node->type = 0;
    node->cell1 = -1;
    node->cell2 = -1;
    node->op_val = 0;
    node->operator='\0';
}