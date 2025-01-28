#include "Node.h"

void node(struct Node *node) {
    node->val = 0;
    node->InNeighbours = NULL;
    node->type = 0;
    node->cell1 = NULL;
    node->cell2 = NULL;
    node->op_val = NULL;
}