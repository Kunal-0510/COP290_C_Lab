#ifndef PARSING_H
#define PARSING_H


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
    Constant Assignment = 0 // set op_val to the assignment value. All the operations of cell= value +-/* value are included in this type

    Arithmetic sum = 1 
    if value + cell or cell + value -> op_val= value and cell1= hash(cell) else -> op_val=0 and cell1,cell2 = hash(cells).
    ***Cell assignments (like (A1=A2)) are also of this type, with op_val =0 and cell1= hash(cell assigned)***

    Arithmetic diff= 2 
    if(cell= cell - val)-> cell1=hash(cell), cell2=-1, op_val= val
    if(cell= val- cell)-> cell1=-1, cell2=hash(cell), op_val= val
    else-> cell1 and cell2= hash values, op_val= 0

    Arithmetic product= 3
    if value * cell or cell * value -> op_val= value and cell1= hash(cell) else -> op_val=1 and cell1,cell2 = hash(cells).
   
    Arithmetic division= 4 
    if(cell= cell/val)-> cell1=hash(cell), cell2=-1, op_val= val **return error if val=0
    if(cell= val/cell)-> cell1=-1, cell2=hash(cell), op_val= val ** return error if cell->val=0
    else(cell=cell1/cell2)-> cell1 and cell2= hash values, op_val= 1 **return error if cell2->val=0

    MIN = 5
    MAX = 6
    AVG = 7
    SUM = 8
    STDEV = 9
    cell= func(c1:c2)-> cell1= hash(c1) cell2= hash(c2). set corresponding types

    SLEEP = 10
    cell = SLEEP(c1)-> cell1= hash(c1)  cell2=-1
    cell= SLEEP(val)-> cell1=cell2=-1 op_val=val

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

#endif