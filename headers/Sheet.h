#ifndef SHEET_H
#define SHEET_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Node.h"
#include "linkedlist.h"

/*
Sheet Module

This module defines the Sheet structure, which stores the information about the spreadsheet. 
The Sheet structure contains a matrix of Node structures that constitute the spreadsheet, 
along with metadata such as the number of rows and columns, and the current view's top-left cell indices.
*/

// Declare the Sheet structure
typedef struct Sheet {
    int rows;                    // Number of rows
    int cols;                    // Number of columns
    int coltop;                  // Top-left cell column index
    int rowtop;                  // Top-left cell row index
    struct Node *matrix;         // Matrix of nodes
    int activeRow;               // Active cell row index
    int activeCol;               // Active cell column index
    int display;                 // Display flag
} Sheet;

// Function declarations
struct Node* create_node_matrix(int R, int C);
void create_sheet(int row, int col, struct Sheet *sheet);

#endif