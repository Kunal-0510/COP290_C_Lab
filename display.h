#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Node.h"
#include "Sheet.h"
#include "hash.h"

int min(int a, int b);
int max(int a, int b);
char* mapping(int col);
void display_sheet(struct Sheet* sheet);
void scroll_up(struct Sheet* sheet);
void scroll_down(struct Sheet* sheet);
void scroll_right(struct Sheet* sheet);
void scroll_left(struct Sheet* sheet);
void disable_display(struct Sheet*  sheet);
void enable_display(struct Sheet* sheet);
void scroll_to(char* cell, struct Sheet* sheet);

#endif