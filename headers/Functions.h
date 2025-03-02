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
Functions Module

This module implements all the basic functions of the spreadsheet. 
It also handles the functionality to check for cyclic dependencies and the addition and removal of edges in the graph during assignment or reassignment.
*/

int MASTER(Node* node, Sheet* sheet);
void MIN(int from_row, int from_col, int to_row, int to_col, int max_col, Sheet* sheet, Node* node);
void MAX(int from_row, int from_col, int to_row, int to_col, int max_col, Sheet* sheet, Node* node);
void AVG(int from_row, int from_col, int to_row, int to_col, int max_col, Sheet* sheet, Node* node);
void SUM(int from_row, int from_col, int to_row, int to_col, int max_col, Sheet* sheet, Node* node);
void STDEV(int from_row, int from_col, int to_row, int to_col, int max_col, Sheet* sheet, Node* node);
void SLEEP(Node* node, Sheet* sheet);
void CHECK_CYCLE(Node* node, int* vis, Sheet* sheet, int cell1, int cell2, int* flag, int type, Stack* st);
int delete_edge(Node* node, Sheet* sheet);
int add_edge(Node* node, Sheet* sheet);
void recalculate_node(Node* node, Sheet* sheet, Stack* st);

#endif