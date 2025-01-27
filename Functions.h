#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "hash.h"
#include "Node.h"

/*
Master function accepts arguments as strings of the cell name , the type of operation to be done , the matrix 
and number of collumns.
Returns int. For sleep int will simply return the number of seconds. On assignment it gives out 1 on success.
Use 0 based indexing for fun_type.
Give cell2 null for assignment and both cells null for sleep.
Give val as null wherever not needed.
**READ THIS KUNAL**
0-ASSIGNMENT
1-MIN
2-MAX
3-AVG
4-SUM
5-STDEV
6-SLEEP
*/
int MIN( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix );
int MAX( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix );
int AVG( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix );
int SUM( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix );
int STDEV( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix );
void SLEEP( int sec );

int MASTER( char* cell1,char* cell2,int func_type,int* matrix,int max_col,int val ){
    if( func_type == 0 ){
        //Will handle this later.
    }
    if( func_type == 1 ){

        int index_1 = get_hash( cell1,max_col );
        int index_2 = get_hash( cell2,max_col );
        int from_col = index_1%max_col;
        int to_col = index_2%max_col;
        int from_row = index_1/max_col;
        int to_row = index_2/max_col;

        return MIN( from_row,from_col,to_row,to_col,max_col,matrix );

    }
    if( func_type == 2 ){

        int index_1 = get_hash( cell1,max_col );
        int index_2 = get_hash( cell2,max_col );
        int from_col = index_1%max_col;
        int to_col = index_2%max_col;
        int from_row = index_1/max_col;
        int to_row = index_2/max_col;

        return MAX( from_row,from_col,to_row,to_col,max_col,matrix );

    }
    if( func_type == 3 ){
        
        int index_1 = get_hash( cell1,max_col );
        int index_2 = get_hash( cell2,max_col );
        int from_col = index_1%max_col;
        int to_col = index_2%max_col;
        int from_row = index_1/max_col;
        int to_row = index_2/max_col;

        return AVG( from_row,from_col,to_row,to_col,max_col,matrix );

    }
    if( func_type == 4 ){
        
        int index_1 = get_hash( cell1,max_col );
        int index_2 = get_hash( cell2,max_col );
        int from_col = index_1%max_col;
        int to_col = index_2%max_col;
        int from_row = index_1/max_col;
        int to_row = index_2/max_col;

        return SUM( from_row,from_col,to_row,to_col,max_col,matrix );

    }
    if( func_type == 5 ){
        
        int index_1 = get_hash( cell1,max_col );
        int index_2 = get_hash( cell2,max_col );
        int from_col = index_1%max_col;
        int to_col = index_2%max_col;
        int from_row = index_1/max_col;
        int to_row = index_2/max_col;

        return STDEV( from_row,from_col,to_row,to_col,max_col,matrix );

    }
    
    SLEEP( val );
    return 1;
}
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

int STDEV( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix ){

    int sum = SUM(from_row, from_col, to_row, to_col, max_col, matrix);
    int num_of_terms = ( to_col - from_col )*( to_row - from_row );
    int mean = sum / num_of_terms;
    int var = 0;

    for( int i = from_row; i <= to_row; i++ ){
        for( int j = from_col; j<=to_col; j++ ){
            var += (*( matrix + i*max_col +j ) - mean )*(*( matrix + i*max_col +j ) - mean );
        }
    }
    
    var /= num_of_terms;
    int std_dev = sqrt( var );;
    
    return std_dev;

}

void SLEEP( int sec ){

    clock_t strt_time =  clock(); // Initialising the start time of the program as the current time.
    clock_t end_time = strt_time + sec * CLOCKS_PER_SEC; //Marking the end time when the program must restart.

    while( clock() < end_time ) {}//Delaying using while loop.

}
