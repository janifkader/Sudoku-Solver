# Sudoku Solver

This program is able to solve any 9x9 sudoku with a C backend to handle the validation and solving side of things while a Tkinter Python program handles the frontend GUI.
The frontend access the functions from the `sudoku_solver.c` file through the compressed functions in the Dynamic Link Library file `sudoku.dll`.