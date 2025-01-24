#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <time.h>


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

