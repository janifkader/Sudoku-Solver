#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

/**
 * This function checks if the current Sudoku grid (not necessarily complete)
 * is valid. A Sudoku grid is considered valid if, ignoring the 0s, each rows,
 * column, and 3x3 subgrid does not repeat any digits from 1 to 9.
 *
 * @note An incomplete Sudoku grid may be valid if the criteria above is met.
 *
 * @param sudoku The 9x9 Sudoku grid to be checked.
 * @return 1 if the Sudoku is valid, 0 if it's not.
 */
EXPORT void initialize_array(int arr[]){
    for (int i = 0; i < 9; ++i){
        arr[i] = 0;
    }
}
EXPORT int is_valid_sudoku(int sudoku[9][9]) {
    int rows[9];
    initialize_array(rows);
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            if (sudoku[i][j] < 0 || sudoku[i][j] > 9){
                return 0;
            }
            if (sudoku[i][j] != 0){
                rows[sudoku[i][j] - 1]++;
                if (rows[sudoku[i][j] - 1] > 1){
                    return 0;
                }
            }
        }
        initialize_array(rows);
    }

    int columns[9];
    initialize_array(columns);
    for (int a = 0; a < 9; ++a){
        for (int b = 0; b < 9; ++b){
            if (sudoku[b][a] != 0){
                columns[sudoku[b][a] - 1]++;
                if (columns[sudoku[b][a] - 1] > 1){
                    return 0;
                }
            }
        }
        initialize_array(columns);
    }

    int squares[9];
    initialize_array(squares);
    int hor = 0;
    int ver = 0;
    int n = 0;
    while(n != 4){
        for (int c = hor; c < hor+3; ++c){
            for (int d = ver; d < ver+3; ++d){
                if (sudoku[d][c] != 0){
                    squares[sudoku[d][c] - 1]++;
                    if (squares[sudoku[d][c] - 1] > 1){
                        return 0;
                    }
                }
            }
        }
        n++;
        if (hor == 6 && ver == 6){
            break;
        }
        if (n == 3){
            hor = 0;
            ver += 3;
            n = 0;
        }
        else{
            hor += 3;
        }
        initialize_array(squares);
    }
    return 1;
}

/**
 * Given a (possibly partially) completed Sudoku grid, this function attempts
 * to solve the Sudoku. The `sudoku` array is changed to contain the solution
 * if one exists. None of the digits in the input grid should be changed.
 *
 * @note: Empty spots in the grid are denoted with 0s.
 *
 * @param sudoku The 9x9 Sudoku grid to be solved.
 * @return 1 if the Sudoku was solved successfully and the `sudoku` array is
 * updated, 0 if it's not possible to solve the Sudoku, and the input `sudoku`
 * array remains unchanged in this case.
 */
EXPORT int check_completion(int sudoku[9][9], int *row, int *col){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            if (sudoku[i][j] == 0){
                *row = i;
                *col = j;
                return 0;
            }
        }
    }
    return 1;
}
EXPORT int solve_sudoku(int sudoku[9][9]){
    int row;
    int col;
    if (check_completion(sudoku, &row, &col) == 1){
        return 1;
    }
    for (int i = 1; i <= 9; ++i){
        if (is_valid_sudoku(sudoku) == 1){
            sudoku[row][col] = i;
            if (solve_sudoku(sudoku) == 1 && is_valid_sudoku(sudoku) == 1){
                return 1;
            }
            sudoku[row][col] = 0;
        }
    }
    return 0;
}

#ifndef __testing__

#endif