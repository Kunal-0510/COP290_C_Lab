#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Separates the cell address into letters and numbers
void separate_cell(char *input, char *letters, char *numbers) {
    int i = 0, letter_idx = 0, number_idx = 0;
    while (input[i] != '\0') {
        if (isalpha(input[i])) {
            letters[letter_idx++] = input[i];
        } 
        else if (isdigit(input[i])) {
            numbers[number_idx++] = input[i];
        }
        i++;
    }
    letters[letter_idx] = '\0';
    numbers[number_idx] = '\0';
}

// Converts column letters to a column number
int get_column(char *letters) {
    int column = 0;
    for (int i = 0; letters[i] != '\0'; i++) {
        column = column * 26 + (letters[i] - 'A'+1);
    }
    return column;
}

// Returns the hash of the given cell address
int get_hash(char* address, int col_num){
    char letters[4];
    char numbers[4];
    separate_cell(address, letters, numbers);
    int row= atoi(numbers)-1;
    int col = get_column(letters)-1;

    return (row*col_num+col);
}
