#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Node.h"
#include "Sheet.h"
#include "hash.h"

/*
Display Module

This module controls the spreadsheet display and handles the scroll functionalities. 
It includes functions to display the sheet, scroll in different directions, and enable or disable the display.
*/

int min(int a, int b);
char* mapping(int col);
void clearScreen();
void display_sheet(Sheet* sheet);
void scroll_up(Sheet* sheet);
void scroll_down(Sheet* sheet);
void scroll_right(Sheet* sheet);
void scroll_left(Sheet* sheet);
void disable_display(Sheet* sheet);
void enable_display(Sheet* sheet);
void scroll_to(char* cell, Sheet* sheet);

#endif