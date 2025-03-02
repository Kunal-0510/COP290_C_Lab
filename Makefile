# Compiler and flags
CC = gcc
CFLAGS = -O3 -w -Iheaders  # Suppress warnings (-w), include debugging information (-g), and add header directory
LDFLAGS = -lm   # Linker flag for math library

# Target executable
TARGET = target/release/spreadsheet

# Source files
SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, Node.c Sheet.c linkedlist.c linked_stack.c hash.c validity.c parsing.c Functions.c display.c main.c stack.c set.c)

# Object files (replace .c with .o for each source file)
OBJ = $(SRC:.c=.o)

# Header files directory
HEADER_DIR = headers
HEADERS = $(addprefix $(HEADER_DIR)/, Node.h Sheet.h linkedlist.h linked_stack.h hash.h validity.h parsing.h Functions.h display.h stack.h set.h)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJ)
	mkdir -p $(dir $(TARGET))
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rules for individual object files
Node.o: $(SRC_DIR)/Node.c $(HEADER_DIR)/Node.h $(HEADER_DIR)/linkedlist.h
	$(CC) $(CFLAGS) -c $< -o $@

Sheet.o: $(SRC_DIR)/Sheet.c $(HEADER_DIR)/Sheet.h $(HEADER_DIR)/Node.h
	$(CC) $(CFLAGS) -c $< -o $@

linkedlist.o: $(SRC_DIR)/linkedlist.c $(HEADER_DIR)/linkedlist.h
	$(CC) $(CFLAGS) -c $< -o $@

linked_stack.o: $(SRC_DIR)/linked_stack.c $(HEADER_DIR)/linked_stack.h $(HEADER_DIR)/linkedlist.h
	$(CC) $(CFLAGS) -c $< -o $@

set.o: $(SRC_DIR)/set.c $(HEADER_DIR)/set.h
	$(CC) $(CFLAGS) -c $< -o $@

hash.o: $(SRC_DIR)/hash.c $(HEADER_DIR)/hash.h
	$(CC) $(CFLAGS) -c $< -o $@

validity.o: $(SRC_DIR)/validity.c $(HEADER_DIR)/validity.h $(HEADER_DIR)/hash.h $(HEADER_DIR)/Sheet.h
	$(CC) $(CFLAGS) -c $< -o $@

parsing.o: $(SRC_DIR)/parsing.c $(HEADER_DIR)/parsing.h $(HEADER_DIR)/hash.h $(HEADER_DIR)/validity.h $(HEADER_DIR)/Node.h $(HEADER_DIR)/Sheet.h $(HEADER_DIR)/Functions.h
	$(CC) $(CFLAGS) -c $< -o $@

Functions.o: $(SRC_DIR)/Functions.c $(HEADER_DIR)/Functions.h $(HEADER_DIR)/stack.h $(HEADER_DIR)/hash.h $(HEADER_DIR)/linkedlist.h $(HEADER_DIR)/linked_stack.h $(HEADER_DIR)/Node.h $(HEADER_DIR)/Sheet.h 
	$(CC) $(CFLAGS) -c $< -o $@

display.o: $(SRC_DIR)/display.c $(HEADER_DIR)/display.h $(HEADER_DIR)/Node.h $(HEADER_DIR)/Sheet.h
	$(CC) $(CFLAGS) -c $< -o $@

stack.o: $(SRC_DIR)/stack.c $(HEADER_DIR)/stack.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: $(SRC_DIR)/main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Test Suite Section ---
TEST_DIR = testcase
TEST_SRC = $(TEST_DIR)/test_suite.c
TEST_OBJ = $(TEST_DIR)/test_suite.o
TEST_TARGET = $(TEST_DIR)/test_suite

# Compile the test suite source into an object file.
$(TEST_OBJ): $(TEST_SRC)
	$(CC) $(CFLAGS) -c -o $(TEST_OBJ) $(TEST_SRC)

# Link the test suite object file into an executable.
$(TEST_TARGET): $(TEST_OBJ) $(TARGET)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJ)

# Target to run the test suite.
test: $(TEST_TARGET)
	@echo "Running tests..."
	$(TEST_TARGET)


# Rule to compile LaTeX report
report.pdf: report.tex
	pdflatex report.tex
	pdflatex report.tex  # Run twice to resolve references

report: report.pdf

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(TARGET) report.pdf report.aux report.log report.out report.toc report.synctex.gz

# Phony targets (not actual files)
.PHONY: all clean report
