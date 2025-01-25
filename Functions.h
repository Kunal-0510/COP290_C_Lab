#include <stdio.h>
#include <math.h>
#include <limits.h>

/*
This is the max function will use a pointer for 2d array
and expects the collumns and rows in the input.
0 based indexing required.
*/

int MIN( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix ){

    int max = INT_MIN;

    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            int element = *( matrix + i*max_col +j );
            if( max < element ){
                max = element;
            }
        }
    }

    return max;

}

/*
Min Function is similar to max.
Expects same inputs.
*/

int MAX( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix ){
    
    int min = INT_MAX;

    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            int element = *( matrix + i*max_col +j );
            if( min > element ){
                min = element;
            }
        }
    }

    return min;

}

/*
Average also takes the same inputs.
*/

int AVG( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix ){
    
    int avg_sum = 0;

    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            avg_sum += *( matrix + i*max_col +j );
        }
    }

    int num_elements = ( to_row - from_row + 1 )*( to_col - from_col + 1 );
    int avg = avg_sum/num_elements;

    return avg;

}

int SUM( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix ){
    
    int sum = 0;

    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            sum += *( matrix + i*max_col +j );
        }
    }

    return sum;

}

//* Change made by Kunal
void evaluate(char* val1,char* val2,char* op,int type){

    
}
