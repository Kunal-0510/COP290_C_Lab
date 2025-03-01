#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "hash.h"
#include "linkedlist.h"
#include "Node.h"
#include "stack.h"
#include "Sheet.h"
#include <string.h>

/*
Master function accepts arguments as strings of the cell name , the type of operation to be done , the matrix 
and number of collumns.
Returns int. For sleep int will simply return the number of seconds. On assignment it gives out 1 on success.
Use 0 based indexing for fun_type.
Give cell2 null for assignment and both cells null for sleep.
Give val as null wherever not needed.
**READ THIS KUNAL**
0-ASSIGNMENT
1-Arithematic sum
2-Arithematic difference
3-Arithematic product
4-Arithematic division
5-MIN
6-MAX
7-AVG
8-SUM
9-STDEV
10-SLEEP
*/
int MASTER( Node* node, Sheet* sheet );
/*
This is the max function will use a pointer for 2d array
and expects the collumns and rows in the input.
0 based indexing required.
*/


void MIN( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet, Node* node );
/*
Min Function is similar to max.
Expects same inputs.
*/

void MAX( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet, Node* node );

/*
Average also takes the same inputs.
*/

void AVG( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet, Node* node );

void SUM( int from_row,int from_col,int to_row,int to_col,int max_col,Sheet* sheet, Node* node );

void STDEV( int from_row,int from_col,int to_row,int to_col,int max_col, Sheet* sheet, Node* node );

void SLEEP( Node* node, Sheet* sheet );

// Check cycle function checks for cycle in the graph using kahns. Gives 1 for true 0 for false.

void CHECK_CYCLE( Node* node , int* vis , Sheet* sheet , int  cell1 , int cell2 ,int* flag , int type , Stack* st );
int delete_edge(Node* node , Sheet* sheet);
int add_edge(Node* node, Sheet* sheet);
// void topo_sort( int id , int* vis , Stack* st ,Sheet* sh );
void recalculate_node( Node* node , Sheet* sheet , Stack* st );
#endif