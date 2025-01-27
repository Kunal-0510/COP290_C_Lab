#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Node.h"
#include "display.h"

struct Node* create_node_matrix(int R, int C) {

    struct Node* matrix = (struct Node*)malloc(R * C * sizeof(struct Node));
    if (!matrix) {
        fprintf(stderr, "Memory allocation failed for matrix.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize each Node in the matrix.
    for (int i = 0; i < R * C; i++) {
        node(&matrix[i]); 
    }

    return matrix;
}

int main() {
    int R;
    int C;
    scanf("%d", &R);
    scanf("%d", &C);

    struct Node* matrix= create_node_matrix(R,C);

    display_sheet(matrix, 0, 0, R, C);

    return 0;
}
