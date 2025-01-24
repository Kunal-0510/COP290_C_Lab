#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "hash.h";

bool isValidNumber(char* num){

    int n=strlen(num);
    for(int i=0;i<n;i++){

        if(num[0]=='-' && n>1){
            continue;
        }

        if(!isdigit(num[i])){
            return false;
        }
    }
    return true;
}

bool isValidCell(char* cell, int rows, int cols) {
    
    int n=strlen(cell);
    if (n>6 || n<2) {
        return false;
    }

    int i=0;
    while(i<n && isupper(cell[i]))
        i++;
    int letterCount=i;

    while (i<n && isdigit(cell[i]))
        i++;
    int digitCount=i-letterCount;

    if (i!=n || letterCount==0 || digitCount==0 || letterCount>3 || digitCount>3)
        return false;
    
    char* letters[4];
    char* numbers[4];

    separate_cell(cell, letters, numbers);

    int row= atoi(numbers);
    int col = get_column(letters);

    if(row>rows){
        return false;
    }
    if(col>cols){
        return false;
    }
    return true;
}


bool isValidValue(char* val, int row, int col){
    return isValidCell(val, row, col ) || isValidNumber(val);
}

//TODO
bool isValidExpr(char* expression){

    
    return true;
}

bool isValidRange(char* first,char* second){

    return true;
}