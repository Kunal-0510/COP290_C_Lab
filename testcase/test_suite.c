#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFFER_SIZE 1024

int compare_lines(const char* lineOut, const char* lineExpected) {
    double timeOut, timeExpected;
    int parsedOut, parsedExpected;

    parsedOut = sscanf(lineOut, "[%lf]", &timeOut);
    parsedExpected = sscanf(lineExpected, "[%lf]", &timeExpected);

    if (parsedOut == 1 && parsedExpected == 1) {
        // Find the closing bracket in each line.
        const char *closeBracketOut = strchr(lineOut, ']');
        const char *closeBracketExpected = strchr(lineExpected, ']');
        if (closeBracketOut && closeBracketExpected) {
            
            const char *restOut = closeBracketOut + 1;
            const char *restExpected = closeBracketExpected + 1;
            // Trim any leading whitespace.
            while (*restOut == ' ' || *restOut == '\t') restOut++;
            while (*restExpected == ' ' || *restExpected == '\t') restExpected++;
            return strcmp(restOut, restExpected);
        }
    }
    
    return strcmp(lineOut, lineExpected);
}

void test_parser(int tc, int rows, int cols) {
    char command[256];
    snprintf(command, sizeof(command),
             "./target/release/spreadsheet %d %d < testcase/input/input%d.txt > testcase/temp_output.txt",
             rows, cols, tc);

    if (system(command) != 0) {
        fprintf(stderr, "Error: Failed to execute sheet program.\n");
        return;
    }

    char expected_output_file[256];
    snprintf(expected_output_file, sizeof(expected_output_file),
             "testcase/output/output%d.txt", tc);
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

    while (fgets(lineOut, BUFFER_SIZE, fout) && fgets(lineExpected, BUFFER_SIZE, fexpected)) {
        if (compare_lines(lineOut, lineExpected) != 0) {
            printf("Mismatch at line %d:\n", lineNum);
            printf("Expected: %s", lineExpected);
            printf("Got     : %s", lineOut);
            failed = 1;
        }
        lineNum++;
    }

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

        switch(tc){
            case 11:
                printf("Assignment and function testcases PASSED\n");
                break;
            case 12:
                printf("Recalculation testcases PASSED\n");
                break;
            case 13:
                printf("Stress testcases PASSED\n");
                break;
            case 14:
                printf("ERR Functionality testcases PASSED\n");
                break;
            case 15:
                printf("Cyclic Denpendencies testcases PASSED\n");
                break;
            case 16:
                printf("Error handling testcases PASSED\n");
                break;
            default:
                break;
        }
    }
}

int main(void) {
    FILE* fptr = fopen("testcase/size.txt", "r");
    if (!fptr) {
        fprintf(stderr, "Error: Could not open size.txt.\n");
        return 1;
    }

    int rows, cols, tc = 1;

    printf("Running synthetic test cases...\n");
    while (fscanf(fptr, "%d %d", &rows, &cols) == 2) {
        test_parser(tc++, rows, cols);

        if(tc == 11){
            printf("Running large testcases...\n");
        }
    }
    fclose(fptr);

    return 0;
}
