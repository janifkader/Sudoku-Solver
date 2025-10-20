# Sudoku Solver

This program is able to solve any 9x9 sudoku with a C backend to handle the validation and solving side of things while a Tkinter Python program handles the frontend GUI.

The frontend access the functions from the `sudoku_solver.c` file through the compressed functions in the Dynamic Link Library file `sudoku.dll`.

## Instructions

1. Clone the repository and then navigate to it

2. Run `pip install -r requirements.txt`

3. Run `python gui.py`

You should then be able to input your unsolved sudoku and wait for a solution.