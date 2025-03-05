# COP290_C_Lab Spreadsheet Project

## Overview

This project implements a spreadsheet application with various functionalities such as arithmetic operations, functions (MAX, MIN, SUM, AVG, STDEV, SLEEP), and error handling. The project includes a test suite to validate the functionality of the spreadsheet.

## Building the Project

To build the project, you need to have `make` installed on your system. 
Use make command to run the spreadsheet

## Running the Spreadsheet

To run the spreadsheet application, use the following command:

```sh
./target/release/spreadsheet <rows> <cols>
```

- `<rows>`: Number of rows in the spreadsheet.
- `<cols>`: Number of columns in the spreadsheet.

Example:

```sh
./target/release/spreadsheet 10 10 < testcase/input/input1.txt > testcase/output/output1.txt
```

## Running the Test Suite

The project includes a test suite to validate the functionality of the spreadsheet. The test suite compares the output of the spreadsheet with the expected output for various test cases.

To run the test suite, follow these steps:

Run the test suite:
    ```sh
    ./testcase/test_suite
    ```

The test suite will run all the test cases and print the results, indicating whether each test case passed or failed.

## Directory Structure

- `src/`: Contains the source code for the spreadsheet application.
- `testcase/`: Contains the test cases and the test suite.
  - `input/`: Contains the input files for the test cases.
  - `output/`: Contains the expected output files for the test cases.
  - `size.txt`: Contains the size (rows and columns) for each test case.
  - `test_suite.c`: The test suite implementation.
- `Makefile`: Makefile to build the project.

## Example Input File

An example input file (`testcase/input/input1.txt`) might look like this:

```
A1=5
B1=10
C1=A1+B1
D1=MAX(A1:B1)
E1=SLEEP(2)
q
```

## Example Output File

An example output file (`testcase/output/output1.txt`) might look like this:

```
[0.0] (ok) > 5
[0.0] (ok) > 10
[0.0] (ok) > 15
[0.0] (ok) > 10
[2.0] (ok) > 
```