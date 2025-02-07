#include "validity.h"

bool isValidNumber(char* num){

    int n=strlen(num);
    for(int i=0;i<n;i++){

        if((num[0]=='-' || num[0]=='+') && n>1){
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


bool isValidRange(char* first,char* second,Sheet* sheet){

    if(!isValidCell(first) || !isValidCell(second)){
        return false;
    }

    char letter1[4];
    char number1[4];
    char letter2[4];
    char number2[4];

    separate_cell(first,letter1,number1);
    separate_cell(second,letter2,number2);

    int r1=atoi(number1)-1;
    int c1=get_column(letter1)-1;

    int r2=atoi(number2)-1;
    int c2=get_column(letter2)-1;

    if(r1>r2 || c1>c2){
        return false;
    }

    if(r2>sheet->rows || c2>sheet->cols){
        return false;
    }

    return true;
}