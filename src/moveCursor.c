// moveCursor.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include "Sheet.h"
#include "display.h"
#include "parsing.h"  // Ensure parseInput is declared here

// Global variable to store original terminal settings
static struct termios orig_termios;

// Disable raw mode and restore terminal settings
void disableRawMode() {
    printf("\033[?25h");  // Show the cursor before exiting raw mode
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// Enable raw mode (disable canonical mode and echo)
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// Edit the active cell: get a formula from the user and update the cell
void editActiveCell(Sheet* sheet) {
    // Temporarily leave raw mode to use standard input editing
    disableRawMode();
    
    // Clear the screen so that previous interactive output is removed
    clearScreen();
    
    // Position the prompt well below the spreadsheet grid (adjust as needed)
    printf("\033[15;1H");
    
    // Get active cell's column string (for example, "A")
    char* colStr = mapping(sheet->activeCol);
    printf("Enter formula for cell %s%d: ", colStr, sheet->activeRow + 1);
    free(colStr);
    fflush(stdout);
    
    char input[100];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        
        // Build a full expression in the form "A1=<input>"
        char cellName[10];
        colStr = mapping(sheet->activeCol);
        snprintf(cellName, sizeof(cellName), "%s%d", colStr, sheet->activeRow + 1);
        free(colStr);
        
        char fullExpr[150];
        snprintf(fullExpr, sizeof(fullExpr), "%s=%s", cellName, input);
        
        // Pass the full expression to the parser to update the cell
        int result = parseInput(fullExpr, sheet);
        if (result != 1) {
            printf("\nError parsing expression: %s\n", fullExpr);
            fflush(stdout);
            sleep(2);  // Pause to let the user see the error
        }
    }
    
    // Re-enable raw mode for interactive navigation
    enableRawMode();
}

// Interactive mode: use arrow keys to move the active cell and Enter to edit it
void interactive_mode(Sheet* sheet) {
    // Clear the screen when entering interactive mode
    clearScreen();
    
    // Initialize active cell and view if needed
    sheet->activeRow = 0;
    sheet->activeCol = 0;
    sheet->rowtop = 0;
    sheet->coltop = 0;
    
    enableRawMode();
    char c;
    while (1) {
        // Redraw the spreadsheet; display_sheet() calls clearScreen()
        display_sheet(sheet);
        
        // Display the interactive mode prompt below the grid (adjust line number as needed)
        printf("\033[14;1H");
        printf("Interactive mode: Use arrow keys to move, Enter to edit, q to quit.");
        fflush(stdout);
        
        if (read(STDIN_FILENO, &c, 1) != 1)
            break;
        
        if (c == 'q') {
            break;
        }
        else if (c == '\033') {
            // Read the next two characters for an escape sequence
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) != 1)
                continue;
            if (read(STDIN_FILENO, &seq[1], 1) != 1)
                continue;
            if (seq[0] == '[') {
                switch (seq[1]) {
                    case 'A': // Up arrow
                        if (sheet->activeRow > 0)
                            sheet->activeRow--;
                        break;
                    case 'B': // Down arrow
                        if (sheet->activeRow < sheet->rows - 1)
                            sheet->activeRow++;
                        break;
                    case 'C': // Right arrow
                        if (sheet->activeCol < sheet->cols - 1)
                            sheet->activeCol++;
                        break;
                    case 'D': // Left arrow
                        if (sheet->activeCol > 0)
                            sheet->activeCol--;
                        break;
                }
            }
            // Adjust the view if the active cell moves outside the current 10x10 window
            if (sheet->activeRow < sheet->rowtop)
                sheet->rowtop = sheet->activeRow;
            else if (sheet->activeRow >= sheet->rowtop + 10)
                sheet->rowtop = sheet->activeRow - 9;
            if (sheet->activeCol < sheet->coltop)
                sheet->coltop = sheet->activeCol;
            else if (sheet->activeCol >= sheet->coltop + 10)
                sheet->coltop = sheet->activeCol - 9;
        }
        else if (c == '\n') {
            // Enter key pressed: edit the active cell
            editActiveCell(sheet);
        }
    }
    disableRawMode();
    // Clear screen on exit to remove interactive prompt remnants
    clearScreen();
}
