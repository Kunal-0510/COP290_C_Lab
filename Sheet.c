#include "Sheet.h"

// Function to create a matrix of Nodes
Node* create_node_matrix(int R, int C) {
    Node* matrix = (Node*)malloc(R * C * sizeof(struct Node));
    if (!matrix) {
        fprintf(stderr, "Memory allocation failed for matrix.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int index = i * C + j;
            initialize_node(&matrix[index], index); 
        }
    }
    return matrix;
}

// Function to create and initialize a Sheet
void create_sheet(int row, int col, struct Sheet *sheet) {
    sheet->rows = row;
    sheet->cols = col;
    sheet->coltop = 0;
    sheet->rowtop = 0;
    sheet->matrix = create_node_matrix(row, col);
    sheet->display = 1;
}