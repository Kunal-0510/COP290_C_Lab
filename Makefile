# Compiler and flags
CC = gcc
CFLAGS = -w -g  # Suppress warnings (-w) and include debugging information (-g)
LDFLAGS = -lm   # Linker flag for math library

# Target executable
TARGET = sheet

# Source files
SRC = Node.c Sheet.c linkedlist.c Queue.c hash.c validity.c parsing.c Functions.c display.c main.c

# Object files (replace .c with .o for each source file)
OBJ = $(SRC:.c=.o)

# Header files
HEADERS = Node.h Sheet.h linkedlist.h Queue.h hash.h validity.h parsing.h Functions.h display.h

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rules for individual object files
Node.o: Node.c Node.h linkedlist.h
	$(CC) $(CFLAGS) -c $<

Sheet.o: Sheet.c Sheet.h Node.h
	$(CC) $(CFLAGS) -c $<

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c $<

Queue.o: Queue.c Queue.h
	$(CC) $(CFLAGS) -c $<

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c $<

validity.o: validity.c validity.h hash.h Sheet.h
	$(CC) $(CFLAGS) -c $<

parsing.o: parsing.c parsing.h hash.h validity.h Node.h Sheet.h Functions.h
	$(CC) $(CFLAGS) -c $<

Functions.o: Functions.c Functions.h Node.h Sheet.h hash.h linkedlist.h Queue.h
	$(CC) $(CFLAGS) -c $<

display.o: display.c display.h Node.h Sheet.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets (not actual files)
.PHONY: all clean
