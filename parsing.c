#include "parsing.h"

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
    if cell = value + cell or cell = cell + value -> op_val= value and cell1= hash(cell) else -> op_val=0 and cell1,cell2 = hash(cells).
    ***Cell assignments (like (A1=A2)) are also of this type, with op_val =0 and cell1= hash(cell assigned)***

    Arithmetic diff= 2 
    if(cell= cell - val)-> cell1=hash(cell), cell2=-1, op_val= val
    if(cell= val- cell)-> cell1=-1, cell2=hash(cell), op_val= val
    else-> cell1 and cell2= hash values, op_val= 0

    Arithmetic product= 3
    if value * cell or cell * value -> op_val= value and cell1= hash(cell) else -> op_val=1 and cell1,cell2 = hash(cells).
    *** if cell= cell*0 then the cell is type 0 and constant assigned =0 ***

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




void parseExpr(char* expression, char* op, char* val1, char* val2) {
    int n = strlen(expression);
    int len1 = 0, len2 = 0;
    int insideParentheses = 0;

    for (int i = 0; i < n; i++) {
        char c = expression[i];

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

        if (c == '+' || c == '-' || c == '*' || c == '/') {
            *op = c;
            continue;
        }

        if (*op) {
            val2[len2++] = c;
        } else {
            val1[len1++] = c;
        }
    }

    val1[len1] = '\0';
    val2[len2] = '\0';
}

Node* str_to_node(char* cellAddress,Sheet* sheet){

    Node* cell=(sheet->matrix + get_hash(cellAddress,sheet->cols));
    return cell;

}

bool assign_cell(char* cellAddress,char* expr,Sheet* sheet){

    Node* cell=str_to_node(cellAddress,sheet);

    char op='\0';
    char val1[15]={0};
    char val2[15]={0};

    parseExpr(expr, &op,val1,val2);

    int type=-1;

    val2[0]='\0';

    if(op!='\0'){

        type=1;
        cell->operator=op;

        if(isValidCell(val1)){

            cell->cell1=get_hash(val1,sheet->cols);

            if(isValidCell(val2)){ //* cell cell
                cell->cell2=get_hash(val2,sheet->cols);
                cell->op_val=0;
            }
            else if(isValidNumber(val2)){ //* cell const

                int num=atoi(val2);

                if(num==0 && op=='*'){
                    type=0;
                    cell->cell1=-1;
                    cell->cell2=-1;
                    cell->op_val=0;
                    return true;
                }

                cell->op_val=num;
                cell->cell2=-1;
            }
        }
        else if(isValidNumber(val1)){

            int num=atoi(val1);

            cell->op_val=num;
            cell->cell1=-1;

            if(isValidCell(val2)){ //* const cell

                if(num==0 && op=='*'){

                    type=0;
                    cell->cell1=-1;
                    cell->cell2=-1;
                    cell->op_val=0;
                    return true;
                }

                cell->cell2=get_hash(val2,sheet->cols);
            }

            else if(isValidNumber(val2)){ //* const const

                type=0;
                int num1=atoi(val1);
                int num2=atoi(val2);

                int ans=0;

                if(op=='+'){
                    ans=num1+num2;
                }
                else if(op=='-'){
                    ans=num1-num2;
                }
                else if(op=='*'){
                    ans=num1*num2;
                }
                else if(op=='/' && num2!=0){
                    ans=num1/num2;
                }

                cell->cell1=-1;
                cell->cell2=-1;
                cell->op_val=ans;
                
            }
        }
        else type=-1;
    }

    else{

        //* assignment
        if(val2[0]=='\0'){

            if(isValidNumber(val1)){
                type=0;
                cell->op_val= atoi(val1); //* cell = constant
            }
            else if(isValidCell(val1)){
                type=0;
                cell->cell1=get_hash(val1,sheet->cols);
                cell->cell2=-1;
                cell->op_val=0;
            }
        }

        else{

            //* val1 -> <func> val2-> <range>

            if(strcmp(val1,"SLEEP")){

                if(isValidCell(val2)){

                    type=8;
                    cell->cell1=get_hash(val1,sheet->cols);
                    cell->cell2=-1;
                    cell->op_val=0;

                }
                else if(isValidNumber(val2)){

                    type=8;
                    cell->cell1=-1;
                    cell->cell2=-1;
                    cell->op_val=atoi(val2);

                }
            }

            else{

                char* first = NULL;
                char* second = NULL;

                if (parse(val2, &first, &second, ':') && isValidRange(first, second,sheet)) {
                    if (strcmp(val1, "MIN") == 0) type = 5;
                    else if (strcmp(val1, "MAX") == 0) type = 6;
                    else if (strcmp(val1, "AVG") == 0) type = 7;
                    else if (strcmp(val1, "SUM") == 0) type = 8;
                    else if (strcmp(val1, "STDEV") == 0) type = 9;

                    cell->cell1=get_hash(first,sheet->cols);
                    cell->cell2=get_hash(second,sheet->cols);
                    cell->op_val=0;
                }

                free(first);
                free(second);
            }
        }

    }

    cell->type=type;

    free(cell);

    return (type!=-1);
}

bool parseInput(char* input,Sheet* sheet){

    char cellAddress[15];
    char expression[15];

    if(!parse(input,&cellAddress,&expression,'=')){
        return false;
    }

    if(!assign_cell(cellAddress,expression,sheet)){
        return false;
    }

    return true;

}

