#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
// Self Explanatory
int min(int a, int b){
    return (a>b) ? b : a;
}


char* mapping(int col){//Args: Column number
    
    char* result = (char*)malloc(4*sizeof(char));

    if(col < 26){
        result[0] = 'A'+col;
        result[1] = '\0';
    }

    else if(col < ((26*26)+26)){
        int mod = col%26; 
        int div = col/26;
        result[1] = 'A'+mod;
        result[0] = 'A'+div-1;
        result[2] = '\0';
    }

    else{

        int x= col-(26*26)-26;
        int mod1= col%(26);
        int mod2= (col/(26))%26;
        int div= col/(26*26);
        result[2] = 'A'+mod1;
        result[1] = 'A'+mod2;
        result[0] = 'A'+div-1;
        result[3] = '\0';

    }
    return result;

}//Returns the string correspondind to the corresponding column number. Ex:- 0->'A'; 25->'Z'; 27->'AB'

void display_sheet(int* matrix, int rowtop, int coltop, int numrows, int numcols ){ // args: The sheet itself, current top left cell, number of rows and columns
    printf("   ");
    for(int j=coltop; j<min(coltop+10, numcols); j++){
        printf("%10s", mapping(j));
    }
    printf("\n");
    for(int i=rowtop; i<min(rowtop+10, numrows); i++){
        printf("%3d", i+1);
        for(int j= coltop; j<min(coltop+10, numcols); j++){
            printf("%10d", *(matrix+i*numcols+j));
        }
        printf("\n");
    }
}  // Displays the excel sheet in 10*10 grid

