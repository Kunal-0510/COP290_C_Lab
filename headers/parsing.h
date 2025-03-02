#ifndef PARSING_H
#define PARSING_H

#include "validity.h"
#include "Functions.h"
#include "Node.h"
#include "Sheet.h"

/*
Parsing Module

This module handles user input parsing and assigns the properties of each of the nodes. 
It includes functions to parse input strings, validate them, and update the corresponding nodes in the spreadsheet.
*/

bool parse(char* input, char** first, char** second, char symbol);
void parseExpr(char* expression, char* op, char* val1, char* val2);
Node* str_to_node(char* cellAddress, Sheet* sheet);
bool assign_cell(char* cellAddress, char* expr, Sheet* sheet);
bool parseInput(char* input, Sheet* sheet);

#endif