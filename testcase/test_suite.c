#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1024

// Trim trailing newline and carriage return characters.
void trim_newline(char *s) {
    size_t len = strlen(s);
    while(len > 0 && (s[len-1]=='\n' || s[len-1]=='\r')) {
        s[len-1] = '\0';
        len--;
    }
}

// Reads all nonempty lines from a file into an array of strings (one per command).
char **read_lines(const char *filename, int *count) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }
    char **lines = NULL;
    char buf[MAX_LINE];
    *count = 0;
    while (fgets(buf, sizeof(buf), f)) {
        trim_newline(buf);
        if (strlen(buf) == 0)
            continue; // skip empty lines
        lines = realloc(lines, ((*count)+1) * sizeof(char *));
        if (!lines) {
            fprintf(stderr, "Memory allocation error\n");
            fclose(f);
            return NULL;
        }
        lines[*count] = strdup(buf);
        (*count)++;
    }
    fclose(f);
    return lines;
}

// Improved read_blocks: Reads the file line by line and groups consecutive nonempty lines
// into one block. Blocks are separated by one or more empty lines.
char **read_blocks(const char *filename, int *count) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }
    char **blocks = NULL;
    *count = 0;
    char line[MAX_LINE];
    char *current_block = NULL;
    size_t current_size = 0;
    bool block_started = false;
    
    while (fgets(line, sizeof(line), f)) {
        trim_newline(line);
        if (strlen(line) == 0) {
            // Empty line: if we are in a block, finish it.
            if (block_started) {
                blocks = realloc(blocks, ((*count)+1) * sizeof(char *));
                blocks[*count] = current_block;
                (*count)++;
                current_block = NULL;
                current_size = 0;
                block_started = false;
            }
        } else {
            // Nonempty line: append it to current block.
            size_t line_len = strlen(line);
            char *temp = realloc(current_block, current_size + line_len + 2); // +1 for newline, +1 for null
            if (!temp) {
                fprintf(stderr, "Memory reallocation error\n");
                free(current_block);
                fclose(f);
                return NULL;
            }
            current_block = temp;
            memcpy(current_block + current_size, line, line_len);
            current_size += line_len;
            current_block[current_size] = '\n';
            current_size++;
            current_block[current_size] = '\0';
            block_started = true;
        }
    }
    // If the file didn't end with a blank line, add the last block.
    if (block_started) {
        blocks = realloc(blocks, ((*count)+1) * sizeof(char *));
        blocks[*count] = current_block;
        (*count)++;
    }
    fclose(f);
    return blocks;
}

// Reads output from the sheet program for one command.
// This function reads lines until it detects a line that contains the prompt indicator (">").
char *read_command_output(FILE *fp) {
    char *output = NULL;
    size_t out_size = 0;
    char buf[MAX_LINE];
    bool got_prompt = false;
    
    while (fgets(buf, sizeof(buf), fp)) {
        size_t line_len = strlen(buf);
        char *temp = realloc(output, out_size + line_len + 1);
        if (!temp) {
            fprintf(stderr, "Memory reallocation error\n");
            free(output);
            return NULL;
        }
        output = temp;
        memcpy(output + out_size, buf, line_len);
        out_size += line_len;
        output[out_size] = '\0';
        
        // If the line contains ">", assume it's the prompt.
        if (strchr(buf, '>') != NULL) {
            got_prompt = true;
            break;
        }
    }
    if (!got_prompt) {
        // Optional: add error handling if prompt is never received.
    }
    return output;
}

int main(void) {
    int cmd_count = 0;
    char **commands = read_lines("testcase/input.txt", &cmd_count);
    if (!commands) {
        fprintf(stderr, "Failed to read input commands.\n");
        return EXIT_FAILURE;
    }
    
    int expected_count = 0;
    char **expected_outputs = read_blocks("testcase/output.txt", &expected_count);
    if (!expected_outputs) {
        fprintf(stderr, "Failed to read expected outputs.\n");
        for (int i = 0; i < cmd_count; i++) free(commands[i]);
        free(commands);
        return EXIT_FAILURE;
    }
    
    // If your sheet program prints an initial matrix before any command,
    // you might want to ignore that block. For example, if expected file has one extra block:
    if (expected_count == cmd_count + 1) {
        // Shift expected_outputs pointer by one block.
        free(expected_outputs[0]); // free initial block if not needed
        for (int i = 0; i < expected_count - 1; i++) {
            expected_outputs[i] = expected_outputs[i + 1];
        }
        expected_count--;
    }
    
    if (cmd_count != expected_count) {
        fprintf(stderr, "Mismatch: %d commands vs %d expected output blocks.\n", cmd_count, expected_count);
        for (int i = 0; i < cmd_count; i++) free(commands[i]);
        free(commands);
        for (int i = 0; i < expected_count; i++) free(expected_outputs[i]);
        free(expected_outputs);
        return EXIT_FAILURE;
    }
    
    // Launch the sheet program in interactive mode.
    // Use "stdbuf -o0" to disable buffering if needed.
    FILE *fp = popen("stdbuf -o0 ./sheet 5 5", "r+");
    if (!fp) {
        fprintf(stderr, "Failed to run sheet program.\n");
        return EXIT_FAILURE;
    }
    
    // Optionally, read the initial output (if your program prints an initial matrix/prompt).
    char *initial = read_command_output(fp);
    free(initial);
    
    int failures = 0;
    // For each command, send the command and compare the output.
    for (int i = 0; i < cmd_count; i++) {
        fprintf(fp, "%s\n", commands[i]);
        fflush(fp);
        
        char *actual_output = read_command_output(fp);
        if (!actual_output) {
            fprintf(stderr, "Failed to read output for command: %s\n", commands[i]);
            failures++;
            continue;
        }
        
        if (strcmp(actual_output, expected_outputs[i]) != 0) {
            printf("Test for command \"%s\" FAILED.\n", commands[i]);
            printf("=== Expected Output ===\n%s\n", expected_outputs[i]);
            printf("=== Actual Output ===\n%s\n", actual_output);
            failures++;
        } else {
            printf("Test for command \"%s\" PASSED.\n", commands[i]);
        }
        free(actual_output);
    }
    
    fprintf(fp, "exit\n");
    fflush(fp);
    pclose(fp);
    
    for (int i = 0; i < cmd_count; i++) free(commands[i]);
    free(commands);
    for (int i = 0; i < expected_count; i++) free(expected_outputs[i]);
    free(expected_outputs);
    
    if (failures > 0) {
        printf("%d tests failed.\n", failures);
        return EXIT_FAILURE;
    } else {
        printf("All tests passed!\n");
        return EXIT_SUCCESS;
    }
}
