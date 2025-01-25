#include <stdio.h>
#include "parsing.h"

int main() {
    char input[100];
    printf("Enter input : ");
    scanf("%s", input);

    char* cell = NULL;
    char* expression = NULL;

    if (parse(input, &cell, &expression,'=')) {
        printf("Cell: %s\n", cell);
        printf("Expression: %s\n", expression);
    } else {
        printf("Invalid Command\n");
    }

    int type=parseExpr(expression);
    printf("Type : %d\n",type);

    free(cell);
    free(expression);

    return 0;
}
