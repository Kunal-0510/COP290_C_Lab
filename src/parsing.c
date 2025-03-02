#include "parsing.h"

// Parses the input string based on the given symbol and separates it into two parts
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


    Constant Assignment = 0 // set op_val to the assignment value. All the operations of cell= value + - * / value are included in this type

    Arithmetic operation = 1 
    if cell = value + cell or cell = cell + value -> op_val= value and cell1= hash(cell) else -> op_val=0 and cell1,cell2 = hash(cells).
    ***Cell assignments (like (A1=A2)) are also of this type, with op_val =0 and cell1= hash(cell assigned)***

    MIN = 2
    MAX = 3
    AVG = 4
    SUM = 5
    STDEV = 6
    cell= func(c1:c2)-> cell1= hash(c1) cell2= hash(c2). set corresponding types

    SLEEP = 7
    cell = SLEEP(c1)-> cell1= hash(c1)  cell2=-1
    cell= SLEEP(val)-> cell1=cell2=-1 op_val=val

*/

// Parses an expression and separates it into operator and operands
void parseExpr(char* expression, char* op, char* val1, char* val2) {
    int n = strlen(expression);
    int len1 = 0, len2 = 0;
    int insideParentheses = 0;
    
    for (int i = 0; i < n; i++) {
        // printf("i: %d val1:%s val2:%s op:%c\n",i, val1, val2, op);
        char c = expression[i];

        if(i==0 && (c=='-' || c=='+')){
            // negative number
            val1[len1++]=c;
            continue;
        }

        if (c == '(') {
            insideParentheses = 1;
            continue;
        }

        if (c == ')') {
            insideParentheses = 0;
            continue;
        }

        if (insideParentheses) {
            val2[len2++] = c;
            continue;
        }

        if ((c == '+' || c == '-' || c == '*' || c == '/') && *op=='\0') {
            *op = c;
            continue;
        }
        else if (*op!='\0') {
            val2[len2++] = c;
        } else {
            val1[len1++] = c;
        }
    }

    val1[len1] = '\0';
    val2[len2] = '\0';
}

// Converts a cell address string to a Node pointer
Node* str_to_node(char* cellAddress,Sheet* sheet){

    Node* cell=(sheet->matrix + get_hash(cellAddress,sheet->cols));
    return cell;

}

// Assigns the properties of the cell and then calls the check_cycle function, if the cycleis found,  returns false
// else it it calls the delete_edge function and assigns the properties, calls the add edge function and then the recalculate_node function
bool assign_cell(char* cellAddress, char* expr, Sheet* sheet) {

    Node* cell = str_to_node(cellAddress, sheet);

    int cell1=-1;
    int cell2=-1;
    int type=0;
    int op_val=0;
    int isValid=1;
    char newop= '\0';
    char op = '\0';
    char val1[256] = {0};
    char val2[256] = {0};

    parseExpr(expr, &op, val1, val2);


    if (op != '\0') {
        type = 1;
        newop = op;

        if (isValidCell(val1, sheet)) {
            cell1 = get_hash(val1, sheet->cols);

            if (isValidCell(val2, sheet)) {
                cell2 = get_hash(val2, sheet->cols);
                op_val = 0;
            }
            
            else if (isValidNumber(val2)) {
                int num = atoi(val2);
                op_val = num;
                cell2 = -1;
            }
            else return false;
        }
        
        else if (isValidNumber(val1)) {
            int num = atoi(val1);
            op_val = num;
            cell1 = -1;

            if (isValidCell(val2, sheet)) {
                cell2 = get_hash(val2, sheet->cols);
            }
            
            else if (isValidNumber(val2)) {
                type = 0;
                isValid=1;
                int num1 = atoi(val1);
                int num2 = atoi(val2);
                int ans = 0;

                if (op == '+') ans = num1 + num2;
                else if (op == '-') ans = num1 - num2;
                else if (op == '*') ans = num1 * num2;
                else if (op == '/' && num2 != 0) ans = num1 / num2;
                else if (op == '/' && num2==0) isValid=0;

                cell1 = -1;
                cell2 = -1;
                op_val = ans;
            }
        } 
        
        else return false;
    } 
    
    else {
       
        if (val2[0] == '\0') {
            if (isValidNumber(val1)) {
                type = 0;
                isValid=1;
                op_val = atoi(val1);
            } 
            
            else if (isValidCell(val1, sheet)) {
                type = 1;
                cell1 = get_hash(val1, sheet->cols);
                cell2 = -1;
                op_val = 0;
                newop='+';
            }
            else return false;
        } 
        
        else {
            if (strcmp(val1, "SLEEP") == 0) {
                if (isValidCell(val2, sheet)) {
                    type = 7;
                    cell1 = get_hash(val2, sheet->cols);
                    cell2 = -1;
                    op_val = 0;
                } 
                
                else if (isValidNumber(val2)) {
                    type = 7;
                    cell1 = -1;
                    cell2 = -1;
                    op_val = atoi(val2);
                }
                else return false;
            } 
            
            else {
                char* first = NULL;
                char* second = NULL;

                if (parse(val2, &first, &second, ':') && isValidRange(first, second, sheet)) {
                    if (strcmp(val1, "MIN") == 0) type = 2;
                    else if (strcmp(val1, "MAX") == 0) type = 3;
                    else if (strcmp(val1, "AVG") == 0) type = 4;
                    else if (strcmp(val1, "SUM") == 0) type = 5;
                    else if (strcmp(val1, "STDEV") == 0) type = 6;

                    cell1 = get_hash(first, sheet->cols);
                    cell2 = get_hash(second, sheet->cols);
                    op_val = 0;
                }
                else return false;

                free(first);
                free(second);
            }
        }
    }
    int flag=0;
    int n= sheet->rows*sheet->cols;
    Stack* st= (Stack*)malloc(sizeof(Stack));
    int* vis= (int*)malloc(n*sizeof(int));
    StackInit(st);
    CHECK_CYCLE(cell, vis, sheet, cell1, cell2, &flag, type, st);


    if(!flag){
        delete_edge(cell, sheet);
        cell->cell1=cell1;
        cell->cell2=cell2;
        cell->isValid=isValid;
        cell->op_val=op_val;
        cell->operator=newop;
        cell->type=type;
        add_edge(cell, sheet);
        recalculate_node(cell, sheet, st);
    }
    else{
        return false;
    }

    return true;
}

// Parses the input command and processes it
bool parseInput(char* input, Sheet* sheet) {


    char* cellAddress = NULL;
    char* expression = NULL;

    if (!parse(input, &cellAddress, &expression, '=')) {
        free(cellAddress);
        free(expression);
        return false;
    }

    if(!isValidCell(cellAddress,sheet)){
        free(cellAddress);
        free(expression);
        return false;
    }
    

    bool result = assign_cell(cellAddress, expression, sheet);
    
    free(cellAddress);
    free(expression);

    return result;
}
