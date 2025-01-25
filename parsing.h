#include "validity.h"
#include "Functions.h"

bool parse(char* input, char** first, char** second, char symbol) {
    char* sign = strchr(input, symbol);

    if (!sign || sign == input || *(sign + 1) == '\0') {
        return false;
    }

    int firstLength = sign - input;
    int secondLength = strlen(input) - firstLength - 1;

    *first = (char*)malloc(firstLength + 1);
    *second = (char*)malloc(secondLength + 1);

    if (!*first || !*second) {
        free(*first);
        free(*second);
        return false;
    }

    // Copy into first
    for (int i = 0; i < firstLength; i++) {
        (*first)[i] = input[i];
    }
    (*first)[firstLength] = '\0';

    // Copy into second
    for (int i = 0; i < secondLength; i++) {
        (*second)[i] = sign[1 + i];
    }
    (*second)[secondLength] = '\0';

    return true;
}

 /*

    Invalid = -1
    Constant Assignment = 0
    Cell Assignment = 1
    Arithmetic Expression = 2
    MIN = 3
    MAX = 4
    AVG = 5
    SUM = 6
    STDEV = 7
    SLEEP = 8

*/

int parseExpr(char* expression) {

    int n = strlen(expression);
    char* val1 = (char*)malloc((n + 1) * sizeof(char));
    char* val2 = (char*)malloc((n + 1) * sizeof(char));

    if (!val1 || !val2) {
        free(val1);
        free(val2);
        return -1;
    }

    int len1 = 0, len2 = 0;
    char* op = NULL;

    for (int i = 0; i < n; i++) {
        char c = expression[i];

        if (c == '(') {
            int j = i + 1;
            while (j < n && expression[j] != ')') {
                val2[len2++] = expression[j];
                j++;
            }
            val2[len2] = '\0';
            break;
        }

        if (c=='+' || c=='-' || c=='*' || c=='/') op = &c;
        else if (op) val2[len2++] = c;
        else val1[len1++] = c;
    }

    val1[len1] = '\0';

    int type = -1;

    if (strchr(val2, ':')) {
        char* first = NULL;
        char* second = NULL;

        if (parse(val2, &first, &second, ':') && isValidRange(first, second)) {
            if (strcmp(val1, "MIN") == 0) type = 3;
            else if (strcmp(val1, "MAX") == 0) type = 4;
            else if (strcmp(val1, "AVG") == 0) type = 5;
            else if (strcmp(val1, "SUM") == 0) type = 6;
            else if (strcmp(val1, "STDEV") == 0) type = 7;
        }

        free(first);
        free(second);
    }
    else if(isValidNumber(val2) && (strcmp(val1,"SLEEP")==0)){
        type=8;
    }
    else if (op && isValidValue(val1) && isValidValue(val2)) {
        if (isValidNumber(val1) && isValidNumber(val2)) {
            type = 0;
        } 
        else {
            type = 2;
        }
    }
    else if (len2 == 0) {
        if (isValidNumber(val1)) {
            type = 0;
        } 
        else if(isValidCell(val1)) {
            type = 1;
        }
    }

    if (type != -1) {
        evaluate(val1, val2, op, type);
    }

    free(val1);
    free(val2);

    return type;
}
