# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable
TARGET = main

# Source files
SRC = Node.c Sheet.c linkedlist.c Queue.c hash.c validity.c parsing.c Functions.c main.c

# Object files (replace .c with .o for each source file)
OBJ = $(SRC:.c=.o)

# Header files
HEADERS = Node.h Sheet.h linkedlist.h Queue.h hash.h validity.h parsing.h Functions.h display.h

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rules for individual object files
Node.o: Node.c Node.h
	$(CC) $(CFLAGS) -c $<

Sheet.o: Sheet.c Sheet.h Node.h
	$(CC) $(CFLAGS) -c $<

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c $<

Queue.o: Queue.c Queue.h
	$(CC) $(CFLAGS) -c $<

hash.o: hash.c hash.h Sheet.h
	$(CC) $(CFLAGS) -c $<

validity.o: validity.c validity.h
	$(CC) $(CFLAGS) -c $<

parsing.o: parsing.c parsing.h hash.h validity.h Node.h Sheet.h Functions.h
	$(CC) $(CFLAGS) -c $<

Functions.o: Functions.c Functions.h Node.h Sheet.h hash.h linkedlist.h Queue.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets (not actual files)
.PHONY: all clean
