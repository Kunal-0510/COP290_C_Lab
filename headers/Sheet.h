#ifndef SHEET_H
#define SHEET_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Node.h"
#include "linkedlist.h"

// Declare the Sheet structure
typedef struct Sheet {
    int rows;                    // Number of rows
    int cols;                    // Number of columns
    int coltop;                  // Top-left cell column index
    int rowtop;                  // Top-left cell row index
    struct Node *matrix;         // Matrix of nodes
    int display;                 // Display flag
} Sheet;

// Function declarations
struct Node* create_node_matrix(int R, int C);
void create_sheet(int row, int col, struct Sheet *sheet);
void free_sheet(Sheet* sheet);

#endif