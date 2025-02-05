#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Node.h"
#include "display.h"
#include "Sheet.h"
#include "Functions.h"
#include "hash.h"
#include <time.h>
#include "parsing.h"

#define MAX_INPUT_LENGTH 100
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


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: ./sheet <rows> <columns>\n");
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    Sheet* sheet = (Sheet*)malloc(sizeof(Sheet));
    if (!sheet) {
        fprintf(stderr, "Memory allocation failed for Sheet.\n");
        return EXIT_FAILURE;
    }
    clock_t st = clock();
    create_sheet(rows, cols, sheet); // Initialize the sheet
    display_sheet(sheet);      // Display the sheet (assuming this function is defined)
    clock_t en = clock();
    double el = ((double)(en - st)) / CLOCKS_PER_SEC;
    printf("[%0.1f] (ok) > ", el);

    char input[MAX_INPUT_LENGTH];
    while (1) {
        // printf("%d\n", strlen(input));
        if (!fgets(input, MAX_INPUT_LENGTH, stdin)) {
            printf("[0.0] (error reading input) >");
            continue;
        }

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        clock_t start_time = clock(); // Start timing the command

        if (strcmp(input, "q") == 0) {
            break; 
        } else if (strcmp(input, "w") == 0) {
            scroll_up(sheet);
        } else if (strcmp(input, "s") == 0) {
            scroll_down(sheet);
        } else if (strcmp(input, "a") == 0) {
            scroll_left(sheet);
        } else if (strcmp(input, "d") == 0) {
            scroll_right(sheet);
        } else if (strcmp(input, "disable_output") == 0) {
            disable_display(sheet);
        } else if (strcmp(input, "enable_output") == 0) {
            enable_display(sheet);
        } else if (strncmp(input, "scroll_to ", 10) == 0) {
            char* cell = input + 10; // Extract cell argument
            scroll_to(cell, sheet);
        } else {
            // Assume it's a formula or operation
            // printf("%d\n", strlen(input));
            int result = parseInput(input, sheet); // Assuming parse_input is implemented in parser.h
            if (result == 0) {
                printf("[0.0] (error parsing input) >");
                continue;
            }
            else{
                display_sheet(sheet);
            }
        }

        clock_t end_time = clock();
        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        
        printf("[%0.1f] (ok) > ", elapsed_time);
    }
    
    free(sheet); // Free allocated memory
    return 0;
}