#ifndef VALIDITY_H
#define VALIDITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "hash.h"
#include "Sheet.h"

/*
Validity Module

This module ensures input validation and error handling. 
It includes functions to validate numbers, cell addresses, values, and ranges within the spreadsheet.
*/

bool isValidNumber(char* num);
bool isValidCell(char* cell, Sheet* sheet);
bool isValidValue(char* val, Sheet* sheet);
bool isValidRange(char* first, char* second, Sheet* sheet);

#endif