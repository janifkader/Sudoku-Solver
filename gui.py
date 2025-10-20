import tkinter as tk
from tkinter import ttk
import sv_ttk
import numpy as np
import ctypes
from ctypes import c_int, POINTER

def clear():
    for k in range(81):
        cells[k].set("")
    suc.configure(text="")

def submit():
    j = 0
    sud = []
    for n in range(81):
        if cells[j].get():
            sud.append(int(cells[j].get()))
        else:
            sud.append(0)
        j += 1

    sud_ctypes = IntArray81(*sud)
    res = lib.solve_sudoku(sud_ctypes)
    if res == 1:
        solved = np.array(list(sud_ctypes)).reshape((9, 9))
        if 0 in solved:
            suc.configure(text="Unable to Solve Sudoku")
            clear()
        else:
            rep = solved.reshape(81, 1)

            for k in range(81):
                cells[k].set(str(int(rep[k][0])))
            suc.configure(text="Sudoku Solved!")
    else:
        print(res)
        suc.configure(text="Unable to Solve Sudoku")



def only_numbers(char):
    if char == "":
        return True
    if len(char) > 1:
        return False
    return char.isdigit() and int(char) != 0

if __name__ == "__main__":

    IntArray81 = ctypes.c_int * 81

    lib = ctypes.CDLL('./sudoku.dll')
    lib.solve_sudoku.argtypes = [IntArray81]
    lib.solve_sudoku.restype = ctypes.c_int

    root = tk.Tk()
    root.title("Sudoku Solver")

    cells = []

    for i in range(81):
        var = tk.StringVar()
        cells.append(var)


    main_frame = ttk.Frame(root)
    main_frame.grid(row=0, column=0, padx=10, pady=10)

    frm = ttk.Frame(main_frame)
    frm.grid(row=0, column=0)

    button_frame = ttk.Frame(main_frame)
    button_frame.grid(row=0, column=1, padx=20)

    valid = (root.register(only_numbers), '%P')

    frm.grid_columnconfigure(4, minsize=12)
    frm.grid_columnconfigure(8, minsize=12)

    frm.grid_rowconfigure(3, minsize=12)
    frm.grid_rowconfigure(7, minsize=12)

    m = 0
    for r in range(11):
        if r == 3 or r == 7:
            continue
        for c in range(11):
            if c == 3 or c == 7:
                continue
            ttk.Entry(frm, textvariable=cells[m], validate='key', validatecommand=valid, width=1,
                      font=('calibre', 10, 'normal')).grid(column=c+1, row=r)
            m += 1

    suc = ttk.Label(button_frame, text="")
    suc.grid(row=0, column=0, pady=5, sticky="ew")

    ttk.Button(button_frame, text="Quit", command=root.destroy).grid(row=1, column=0, pady=5, sticky="ew")
    ttk.Button(button_frame, text="Generate", command=submit).grid(row=2, column=0, pady=5, sticky="ew")
    ttk.Button(button_frame, text="Clear Board", command=clear).grid(row=3, column=0, pady=5, sticky="ew")

    sv_ttk.use_dark_theme()

    root.mainloop()