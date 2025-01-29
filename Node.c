#include "Node.h"

void initialize_node(struct Node *node) {
    node->val = 0;
    node->InNeighbours = NULL;
    node->type = 0;
    node->cell1 = -1;
    node->cell2 = -1;
    node->op_val = 0;
}