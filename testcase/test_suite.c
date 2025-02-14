/* test_suite.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void) {
    // Set up parameters for the sheet program.
    int rows = 5, cols = 5;  // adjust these values as needed

    // Construct the command to run the sheet executable:
    // It feeds input.txt to sheet and writes the output to temp_output.txt.
    char command[256];
    snprintf(command, sizeof(command), "./sheet %d %d < testcase/input.txt > testcase/temp_output.txt", rows, cols);
    
    // Run the command.
    if (system(command) != 0) {
        fprintf(stderr, "Error: Failed to execute sheet program.\n");
        return 1;
    }
    
    // Open the generated output and the expected output.
    FILE *fout = fopen("temp_output.txt", "r");
    FILE *fexpected = fopen("output.txt", "r");
    if (!fout || !fexpected) {
        fprintf(stderr, "Error: Could not open output files.\n");
        return 1;
    }
    
    char lineOut[BUFFER_SIZE];
    char lineExpected[BUFFER_SIZE];
    int lineNum = 1;
    int failed = 0;
    
    // Compare files line by line.
    while (fgets(lineOut, BUFFER_SIZE, fout) && fgets(lineExpected, BUFFER_SIZE, fexpected)) {
        if (strcmp(lineOut, lineExpected) != 0) {
            printf("Mismatch at line %d:\n", lineNum);
            printf("Expected: %s", lineExpected);
            printf("Got     : %s", lineOut);
            failed = 1;
        }
        lineNum++;
    }
    
    // Check if one file has extra lines.
    while (fgets(lineOut, BUFFER_SIZE, fout)) {
        printf("Extra line in output at line %d: %s", lineNum, lineOut);
        failed = 1;
        lineNum++;
    }
    while (fgets(lineExpected, BUFFER_SIZE, fexpected)) {
        printf("Missing line in output (expected at line %d): %s", lineNum, lineExpected);
        failed = 1;
        lineNum++;
    }
    
    fclose(fout);
    fclose(fexpected);
    
    if (failed) {
        printf("Test FAILED.\n");
        return 1;
    } else {
        printf("Test PASSED.\n");
    }
    
    return 0;
}
