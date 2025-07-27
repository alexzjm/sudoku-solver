# Sudoku Solver

A backtracking Sudoku solver written in C that applies logical deduction and recursive guessing to solve 9×9 puzzles.

## Features

- Supports standard 9×9 Sudoku puzzles
- Uses logical elimination and backtracking
- Tracks and updates possible values for each cell
- Detects unsolvable states and exits cleanly
- Console-based input/output for quick testing

## How It Works

1. Accepts a Sudoku grid input (use `0` for empty cells)
2. Applies logic-based elimination (row, column, block)
3. Recursively guesses possible values with backtracking
4. Prints solution if one exists, or reports failure
