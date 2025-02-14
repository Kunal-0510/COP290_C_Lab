#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OUTPUT 4096

/**
 * Runs a single test.
 *
 * @param test_name  A label for the test.
 * @param input      The input commands to send to the program.
 * @param expected   The expected output from the program.
 * @return           0 if the test passed, non-zero otherwise.
 */
int run_test(const char *test_name, const char *input, const char *expected) {
    
    char command[256];
    // Build a shell command that pipes the input to the sheet program.
    // Adjust the number of rows and columns as needed.
    snprintf(command, sizeof(command), "echo \"%s\" | ./sheet 10 10", input);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Test %s: Failed to run command.\n", test_name);
        return 1;
    }

    char output[MAX_OUTPUT] = "";
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strncat(output, buffer, MAX_OUTPUT - strlen(output) - 1);
    }
    pclose(fp);

    if (strcmp(output, expected) != 0) {
        fprintf(stderr, "Test %s FAILED:\n", test_name);
        fprintf(stderr, "Input:\n%s\n", input);
        fprintf(stderr, "Expected Output:\n%s\n", expected);
        fprintf(stderr, "Actual Output:\n%s\n", output);
        return 1;
    } else {
        printf("Test %s PASSED\n", test_name);
    }
    return 0;
}

int main(void) {
    int failures = 0;

    /*
     * Add test cases below.
     *
     * Each test case sends a command (or multiple commands) to your sheet
     * program and compares its output with the expected output.
     *
     * Adjust the expected outputs to match your program's behavior.
     */
    
    // Test arithmetic expression.
    failures += run_test("Arithmetic", "A1=1+2\n", "3\n");

    // Test MIN function.
    failures += run_test("MIN", "B1=MIN(3, 2, 5)\n", "2\n");

    // Test MAX function.
    failures += run_test("MAX", "B1=MAX(3, 2, 5)\n", "5\n");

    // Test AVG function.
    failures += run_test("AVG", "C1=AVG(3, 5, 7)\n", "5\n");

    // Test SUM function.
    failures += run_test("SUM", "C2=SUM(1, 2, 3)\n", "6\n");

    // Test STDEV function.
    // (Adjust expected output based on your program’s formatting.)
    failures += run_test("STDEV", "D1=STDEV(2, 4, 4, 4, 5, 5, 7, 9)\n", "2\n");

    // Test SLEEP command.
    // (Again, adjust expected output as needed.)
    failures += run_test("SLEEP", "E1=SLEEP(1)\n", "Slept 1 seconds\n");

    if (failures > 0) {
        fprintf(stderr, "%d test(s) failed.\n", failures);
        return EXIT_FAILURE;
    }
    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}
