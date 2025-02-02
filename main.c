#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Node.h"
#include "display.h"
#include "Sheet.h"

//Input-> parsing-> assign cell properties-> call add_edge -> call recalculate -> display file
//                                                 ^Nimit            ^Gogo
/*
TBD:
- Parsing (Kunal)
- Add_edge (Nimit)
- Recalculate (Gogo)
- Time funtionality in Display.h and final formatting to match display style (Nimit)
- Error Handling: MAJOR (Each of us in our respective files)
- main.c file (Dekh lenge)
- make file (Kunal)
*/


int main() {
    int R, C;
    scanf("%d %d", &R, &C);

    Sheet* sheet = (Sheet*)malloc(sizeof(Sheet));
    if (!sheet) {
        fprintf(stderr, "Memory allocation failed for Sheet.\n");
        return EXIT_FAILURE;
    }

    create_sheet(R, C, sheet); // Initialize the sheet
    display_sheet(sheet);      // Display the sheet (assuming this function is defined)
    scroll_up(sheet);
    disable_display(sheet);
    scroll_right(sheet);
    scroll_right(sheet);
    enable_display(sheet);
    display_sheet(sheet);
    
    free(sheet); // Free allocated memory
    return 0;
}