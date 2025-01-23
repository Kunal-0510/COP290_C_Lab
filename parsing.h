#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "hash.h";

bool isValidCell(char* cell, int n) {
    
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

    return true;
}

bool parseInput(char* input,char** cell,char** expression){

    char* equalSign=strchr(input,'=');

    if(!equalSign || equalSign==input || *(equalSign+1)=='\0');
        return false;

    int cellLength=equalSign-input;
    int exprLength=strlen(input)-cellLength-1;

    *cell=(char*)malloc(cellLength+1);
    *expression=(char*)malloc(exprLength+1);

    if(!*cell || !*expression){
        free(*cell);
        free(*expression);
        return false;
    }

    //* copy in cell and expresion
    for(int i=0;i<cellLength;i++){
        (*cell)[i]=input[i];
    }
    (*cell)[cellLength]='\0';

    for(int i=0;i<exprLength;i++){
        (*expression)[i]=equalSign[i+1];
    }
    (*expression)[exprLength]='\0';

    return true;
}


