#ifndef FUNCTIONS_H
#define FUNCTIONS_H


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
int MASTER( char* cell1,char* cell2,int func_type,int* matrix,int max_col,int val );
/*
This is the max function will use a pointer for 2d array
and expects the collumns and rows in the input.
0 based indexing required.
*/


int MIN( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix );
/*
Min Function is similar to max.
Expects same inputs.
*/

int MAX( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix );

/*
Average also takes the same inputs.
*/

int AVG( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix );

int SUM( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix );

int STDEV( int from_row,int from_col,int to_row,int to_col,int max_col,int* matrix );

void SLEEP( int sec );

// Check cycle function checks for cycle in the graph using kahns. Gives 1 for true 0 for false.
int CHECK_CYCLE( Node* matrix );



#endif