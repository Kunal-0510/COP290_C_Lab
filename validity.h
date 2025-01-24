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

bool isValidCell(char* cell) {
    
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

    return true;
}

bool isValidValue(char* val){
    return isValidCell(val) || isValidNumber(val);
}

//TODO
bool isValidExpr(char* expression){

    
    return true;
}

bool isValidRange(char* first,char* second){

    return true;
}