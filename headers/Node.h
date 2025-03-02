#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "linkedlist.h"

/*
Node Module

This module defines the Node structure, which stores the basic information about each cell of the spreadsheet. 
The Node structure includes fields for storing the cell's value, validity, dependencies, and other properties.

Node Structure

The core data structure used in the spreadsheet for representing cells and dependencies is the Node structure.

The fields of the structure are described below:

- isValid: Indicates whether the Node will be displayed as ERR or not. A node is shown as ERR iff it has a division by zero error or depends on a node with division by zero error.
- val: Stores the numerical value of the Node.
- id: Unique identifier for the node. For a node in the ith row and jth column, this identifier is defined as i * (number of columns) + j.
- OutNeighbours: Pointer to a linked list storing nodes that depend on the Node.
- type: Represents the type of the Node (e.g., constant, formula, etc.). Each function is assigned to a unique type. By default, the type is initialized to 0 which represents constant assignment.
- cell1, cell2: Store references to other cells if the Node represents a formula or an arithmetic expression. They are set to -1 by default.
- op_val: Stores the numeric value in case of commands like cell=value+cell.
- operator: Stores the mathematical operator used in the case of an arithmetic expression.
*/

typedef struct Node {
    int isValid;
    int val;
    int id;
    LinkedList *OutNeighbours;
    int type;
    int cell1;
    int cell2;
    int op_val;
    char operator;
} Node;

void initialize_node(struct Node *node, int index);

#endif

