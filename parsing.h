<<<<<<< HEAD
#include <stdio.h>


=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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


int* giveIndex(char* cell) {

    int n=strlen(cell);
    int m=1,p=1;

    int* index=(int*)malloc(2*sizeof(int)); //? row, col
    index[0]=-1;
    index[1]=-1;

    int x=0,y=0;
    
    if(!isValidCell(cell,n)){
        free(index);
        return NULL;
    }

    int i = 0;
    //* Letters (column)
    while (isalpha(cell[i])) {
        int val=(cell[i]-'A'+1);
        y=y*26+val;
        i++;
    }

    //* Numbers (row)
    while (isdigit(cell[i])) {
        int val=(cell[i]-'0');
        x=x*10+val;
        i++;
    }

    index[0] = x;
    index[1] = y;

    return index;
}


>>>>>>> origin/nimit/interface
