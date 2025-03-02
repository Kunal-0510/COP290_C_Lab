#ifndef HASH_H
#define HASH_H

/*
Hash Module

This module provides utility functions for handling cell addresses and converting them to hash values. 
It includes functions to separate cell addresses into letters and numbers, convert column letters to numbers, and compute hash values for cell addresses.
*/

void separate_cell(char *input, char *letters, char *numbers);
int get_column(char *letters);
int get_hash(char* address, int col_num);

#endif