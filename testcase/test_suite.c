/* test_suite.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void test_parser(int tc, int rows, int cols) {
    // Construct the command to run the sheet executable:
    // It feeds input.txt to sheet and writes the output to temp_output.txt.
    char command[256];
    snprintf(command, sizeof(command), "./target/release/spreadsheet %d %d < testcase/input/input%d.txt > testcase/temp_output.txt", rows, cols, tc);
    
    // Run the command.
    if (system(command) != 0) {
        fprintf(stderr, "Error: Failed to execute sheet program.\n");
        return;
    }
    
    // Open the generated output and the expected output.
    char expected_output_file[256];
    snprintf(expected_output_file, sizeof(expected_output_file), "testcase/output/output%d.txt", tc);
    FILE *fout = fopen("testcase/temp_output.txt", "r");
    FILE *fexpected = fopen(expected_output_file, "r");
    if (!fout || !fexpected) {
        fprintf(stderr, "Error: Could not open output files.\n");
        return;
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
        printf("Testcase %d FAILED.\n", tc);
    } else {
        printf("Testcase %d PASSED.\n", tc);
    }
}

int main(void) {
    FILE* fptr = fopen("testcase/size.txt", "r");
    if (!fptr) {
        fprintf(stderr, "Error: Could not open size.txt.\n");
        return 1;
    }

    int rows, cols, tc = 1;
    while (fscanf(fptr, "%d %d", &rows, &cols) == 2) {
        
        test_parser(tc++, rows, cols);
        
    }

    
    


    fclose(fptr);

    return 0;
}
