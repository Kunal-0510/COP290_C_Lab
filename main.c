#include <stdio.h>

int main() {
    char input[100];
    printf("Enter input : ");
    scanf("%s", input);

    char* cell = NULL;
    char* expression = NULL;

    if (parseInput(input, &cell, &expression)) {
        printf("Cell: %s\n", cell);
        printf("Expression: %s\n", expression);
    } else {
        printf("Invalid Command\n");
    }

    free(cell);
    free(expression);

    return 0;
}
