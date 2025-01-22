#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "display.h"

//* Input parsing part
void parseInput(const char *input, char *cell, char *expression) {
    const char *equalSign = strchr(input, '=');
    if (equalSign) {
        strncpy(cell, input, equalSign - input);
        cell[equalSign - input] = '\0';  // Null-terminate
        strcpy(expression, equalSign + 1);
    } else {
        cell[0] = '\0';  // Indicate error
        expression[0] = '\0';
    }
}

int main(){


    return 0;
}