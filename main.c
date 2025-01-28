#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Node.h"
#include "display.h"


int main() {
    int R, C;
    scanf("%d %d", &R, &C);

    struct Sheet* sheet = (struct Sheet*)malloc(sizeof(struct Sheet));
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