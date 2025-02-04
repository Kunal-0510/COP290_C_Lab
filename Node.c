#include "Node.h"

void initialize_node(struct Node *node, int id) {
    node->val = 0;
    node->InNeighbours = NULL;
    node->id= id;
    node->in_size=0;
    node->OutNeighbours=NULL;
    node->type = 0;
    node->cell1 = -1;
    node->cell2 = -1;
    node->op_val = 0;
    node->operator='\0';
}