# Postfix Expression Variable Solver
This project is a C program developed to solve mathematical expressions in Postfix (Reverse Polish Notation) notation and find the unknowns in the equation.

## Project Features
The program automatically detects the unknown variables (a, b, c) in a given equation. It lists all possible combinations that reach the result 0 by trying the following:
- Mathematical operators (+, -, *, /, ^)
- Integers between 1 and 20
using a recursive algorithm.

## Technical Details
- Linked List: Divides the expression read from the file into parts and stores them in dynamic memory.
- Stack: Enables the execution of mathematical calculations according to RPN logic.
- Brute-Force Algorithm: Scans all possible cases for variables to find the exact results. - Error Handling: Filters results that do not result in division by zero or integers in division operations.

## Usage
1. Add the DataStructureInput.txt file to the main directory.
2. Write the equation in postfix format with "= 0" at the end. (Example: 3 1 + a 2 / - = 0)
3. Compile and run the project:
gcc main.c -o solver -lm
./solver

## File Structure
- main.c: Algorithm and data structure definitions. - DataStructureInput.txt: Input data.
- 150123008prj1.c.dev: Dev-C++ project file.
- DATA STRUCTURE PROJECT 1 REPORT.docx: Project analysis report.

Developer: Osman Erdem Gulhan
