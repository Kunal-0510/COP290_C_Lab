#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns the minimum of two integers
int min(int a, int b) {
    return (a > b) ? b : a;
}

// Returns the maximum of two integers
int max(int a, int b) {
    return (a < b) ? b : a;
}

// Maps a column number to its corresponding Excel column string (e.g., 0 -> "A", 27 -> "AB")
char* mapping(int col) { // Args: Column number
    char* result = (char*)malloc(4 * sizeof(char));
    if (col < 26) {
        result[0] = 'A' + col;
        result[1] = '\0';
    }
    else if (col < ((26 * 26) + 26)) {
        int mod = col % 26; 
        int div = col / 26;
        result[1] = 'A' + mod;
        result[0] = 'A' + div - 1;
        result[2] = '\0';
    }
    else {
        int mod1 = col % 26;
        col = col / 26;
        col--;
        int mod2 = col % 26;
        col = col / 26;
        col--;
        int div = col % 26;
        result[2] = 'A' + mod1;
        result[1] = 'A' + mod2;
        result[0] = 'A' + div;
        result[3] = '\0';
    }
    return result;
}

// Clears the screen and moves the cursor to the top-left corner
void clearScreen() {
    printf("\033[2J\033[H");  // Clear screen and reposition to home (top-left)
    fflush(stdout);
}

// Displays the sheet in a 10x10 grid format
void display_sheet(struct Sheet* sheet) { // args: The sheet itself
    if (sheet->display == 1) {
        // Clear the screen before drawing the grid
        clearScreen();
        // Print column headers
        printf("   ");
        int colt = sheet->coltop;
        int rowt = sheet->rowtop;
        int numcols = sheet->cols;
        int numrows = sheet->rows;
        for (int j = colt; j < min(colt + 10, numcols); j++) {
            char* colStr = mapping(j);
            printf("%12s", colStr);
            free(colStr);
        }
        printf("\n");
        // Print each row of the grid
        for (int i = rowt; i < min(rowt + 10, numrows); i++) {
            printf("%3d", i + 1);
            for (int j = colt; j < min(colt + 10, numcols); j++) {
                Node* node = sheet->matrix + i * numcols + j;
                // Check if this cell is the active cell
                if (i == sheet->activeRow && j == sheet->activeCol) {
                    // Highlight the active cell using reverse video
                    printf("\033[7m");
                    if (node->isValid == 1)
                        printf("%12d", node->val);
                    else
                        printf("         ERR");
                    printf("\033[0m");
                } else {
                    if (node->isValid == 1)
                        printf("%12d", node->val);
                    else
                        printf("         ERR");
                }
            }
            printf("\n");
        }
    }
}

// Scrolls the sheet view up by 10 rows
void scroll_up(Sheet* sheet) {
    sheet->rowtop = max(sheet->rowtop - 10, 0);
}
    
// Scrolls the sheet view down by 10 rows
void scroll_down(Sheet* sheet) {
    sheet->rowtop = min(sheet->rowtop + 10, max(sheet->rows - 10, 0));   
}

// Scrolls the sheet view right by 10 columns
void scroll_right(Sheet* sheet) {
    sheet->coltop = min(sheet->coltop + 10, max(sheet->cols - 10, 0));
}

// Scrolls the sheet view left by 10 columns
void scroll_left(Sheet* sheet) {
    sheet->coltop = max(sheet->coltop - 10, 0);
}

// Disables the display of the sheet
void disable_display(Sheet* sheet) {
    sheet->display = 0;
}

// Enables the display of the sheet
void enable_display(Sheet* sheet) {
    sheet->display = 1;
}

// Scrolls the sheet view to a specific cell (e.g., "A1", "B2")
void scroll_to(char* cell, Sheet* sheet) {
    char letters[4];
    char numbers[4];
    separate_cell(cell, letters, numbers);
    int row = atoi(numbers) - 1;
    int col = get_column(letters) - 1;

    sheet->rowtop = row;
    sheet->coltop = col;
}
