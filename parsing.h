#ifndef PARSING_H
#define PARSING_H


#include "validity.h"
#include "Functions.h"
#include "Node.h"
#include "Sheet.h"

bool parse(char* input, char** first, char** second, char symbol);

void parseExpr(char* expression, char* op, char* val1, char* val2);

#endif