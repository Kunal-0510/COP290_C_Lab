import os
import random
import string
import subprocess

def random_cell():
    letters = string.ascii_uppercase
    cell = ''.join(random.choice(letters) for _ in range(random.randint(1, 3)))
    cell += str(random.randint(1, 99))
    return cell

def random_expression():
    operations = ['+', '-', '*', '/']
    functions = ['MAX', 'MIN', 'SUM', 'AVG', 'STDEV', 'SLEEP']
    r = random.random()
    if r < 0.7:
        # 70% probability: binary expression
        if random.choice(functions) == 'SLEEP':
            return f"{random.choice(functions)}({random.randint(1, 10)})"
        else:
            return f"{random.choice(functions)}({random_cell()}:{random_cell()})"
    else:
        # 30% probability: other expression type.
        r2 = random.random()
        if r2 < 1/3:
            return str(random.randint(0, 100))
        elif r2 < 2/3:
            return random_cell()
        else:
            return f"{random_cell()}{random.choice(operations)}{random_cell()}"

def generate_input(tc_num, rows, cols):
    input_filename = f"testcase/input/input{tc_num}.txt"
    with open(input_filename, 'w') as infile:
        for _ in range(rows):
            cell = random_cell()
            expression = random_expression()
            infile.write(f"{cell}={expression}\n")
        infile.write("q\n")

def generate_output(tc_num, rows, cols):
    input_filename = f"testcase/input/input{tc_num}.txt"
    output_filename = f"testcase/output/output{tc_num}.txt"
    command = f"./sheet {rows} {cols} < {input_filename} > {output_filename}"
    try:
        subprocess.run(command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error: Command '{command}' failed with exit code {e.returncode}")

def main():
    num_testcases = 10  # Reduced number of test cases for debugging
    min_size = 5
    max_rows = 10  # Reduced maximum rows for debugging
    max_cols = 10  # Reduced maximum columns for debugging
    
    os.makedirs("testcase/input", exist_ok=True)
    os.makedirs("testcase/output", exist_ok=True)
    
    with open("testcase/size.txt", 'w') as size_file:
        for tc in range(1, num_testcases + 1):
            print(f"Generating testcase {tc}...")
            rows = random.randint(min_size, max_rows)
            cols = random.randint(min_size, max_cols)
            size_file.write(f"{rows} {cols}\n")
            generate_input(tc, rows, cols)
            generate_output(tc, rows, cols)
            print(f"Testcase {tc} generated!")

if __name__ == "__main__":
    main()
