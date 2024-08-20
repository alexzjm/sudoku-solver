#include <Stdbool.h>
#include <stdio.h>

typedef struct sodokuSquare {
  int value;
  bool possible[9];
} Square;

bool checkSquare(Square board[9][9], int row, int col);

bool hasSolution(Square board[9][9], int row, int col);

bool scanForSolution(Square board[9][9]);

void printAllPossibilities(Square board[9][9]);

bool wrongSolution(Square board[9][9]);

bool isSolved(Square board[9][9]);

void copyBoard(Square dest[9][9], Square source[9][9]);

void solve(Square main[9][9], Square board[9][9]);

void findSquareToGuess(Square board[9][9], int *row, int *col, int arr[9]);

int main(void) {
  Square main[9][9];
  Square board[9][9];
  printf("Enter the configuration: \n");
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      char userInput;
      scanf(" %c", &userInput);
      board[i][j].value = userInput - 48;
      if (board[i][j].value == 0) {
        for (int k = 0; k < 9; k++) {
          board[i][j].possible[k] = true;
        }
      }
    }
  }

  printf("\nYour entry is: \n");
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%d ", board[i][j].value);
    }
    printf("\n");
  }

  /*bool status = true;

  while (status) {
    status = false;

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j].value == 0) {
          bool elim = checkSquare(board, i, j);
          bool solu = hasSolution(board, i, j);
          if (elim || solu) {
            status = true;
          }
        }
      }
    }

    bool scan = scanForSolution(board);
    if (scan) {
      status = true;
    }
  }*/

  solve(main, board);

  if (isSolved(main)) {
    printf("\nYour solution is: \n");
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        printf("%d ", main[i][j].value);
      }
      printf("\n");
    }
  } else {
    printf("\nIt appears that there is no solution to your problem.");
  }

  printf("\n");
  // printAllPossibilities(board);
}

// only use this for empty squares!!!
bool checkSquare(Square board[9][9], int row, int col) {
  bool change = false;
  // checking row & column
  for (int i = 0; i < 9; i++) {
    if (board[row][i].value != 0 &&
        board[row][col].possible[board[row][i].value - 1]) {
      board[row][col].possible[board[row][i].value - 1] = false;
      change = true;
    }
    if (board[i][col].value != 0 &&
        board[row][col].possible[board[i][col].value - 1]) {
      board[row][col].possible[board[i][col].value - 1] = false;
      change = true;
    }
  }

  // checking block
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[(row / 3) * 3 + i][(col / 3) * 3 + j].value != 0 &&
          board[row][col]
              .possible[board[(row / 3) * 3 + i][(col / 3) * 3 + j].value -
                        1]) {
        board[row][col]
            .possible[board[(row / 3) * 3 + i][(col / 3) * 3 + j].value - 1] =
            false;
        change = true;
      }
    }
  }

  return change;
}

bool hasSolution(Square board[9][9], int row, int col) {
  int count = 0;
  int val = -1;
  for (int i = 0; i < 9; i++) {
    if (board[row][col].possible[i]) {
      count++;
      val = i + 1;
    }
  }
  if (count == 1) {
    board[row][col].value = val;
    return true;
  }
  return false;
}

void printAllPossibilities(Square board[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("(%d, %d): ", i, j);
      if (board[i][j].value != 0) {
        printf("%d ", board[i][j].value);
      } else {
        for (int k = 0; k < 9; k++) {
          if (board[i][j].possible[k]) {
            printf("%d ", k + 1);
          }
        }
      }
      printf("\n");
    }
  }
}

bool scanForSolution(Square board[9][9]) {
  bool action = false;
  // row
  for (int row = 0; row < 9; row++) {
    for (int n = 1; n <= 9; n++) {
      int count = 0, colIndex = -1;
      bool alreadyExist = false;
      for (int c = 0; c < 9; c++) {
        if (board[row][c].value == 0 && board[row][c].possible[n - 1]) {
          count++;
          colIndex = c;
        } else if (board[row][c].value == n) {
          alreadyExist = true;
        }
      }
      if (count == 1 && !alreadyExist) {
        board[row][colIndex].value = n;
        action = true;
      }
    }
  }

  // col
  for (int col = 0; col < 9; col++) {
    for (int n = 1; n <= 9; n++) {
      int count = 0, rowIndex = -1;
      bool alreadyExist = false;
      for (int r = 0; r < 9; r++) {
        if (board[r][col].value == 0 && board[r][col].possible[n - 1]) {
          count++;
          rowIndex = r;
        } else if (board[r][col].value == n) {
          alreadyExist = true;
        }
      }
      if (count == 1 && !alreadyExist) {
        board[rowIndex][col].value = n;
        action = true;
      }
    }
  }

  // block
  for (int bRow = 0; bRow < 3; bRow++) {
    for (int bCol = 0; bCol < 3; bCol++) {
      // for each block
      for (int n = 1; n <= 9; n++) {
        int count = 0, rowIndex = -1, colIndex = -1;
        bool alreadyExist = false;
        for (int r = bRow * 3; r < bRow * 3 + 3; r++) {
          for (int c = bCol * 3; c < bCol * 3 + 3; c++) {
            if (board[r][c].value == 0 && board[r][c].possible[n - 1]) {
              count++;
              rowIndex = r;
              colIndex = c;
            } else if (board[r][c].value == n) {
              alreadyExist = true;
            }
          }
        }
        if (count == 1 && !alreadyExist) {
          board[rowIndex][colIndex].value = n;
          action = true;
        }
      }
    }
  }

  return action;
}

bool wrongSolution(Square board[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j].value == 0) {
        bool hasSolution = false;
        for (int k = 0; k < 9; k++) {
          if (board[i][j].possible[k]) {
            hasSolution = true;
          }
        }
        if (!hasSolution) {
          return true;
        }
      }
    }
  }
  return false;
}

bool isSolved(Square board[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j].value == 0) {
        return false;
      }
    }
  }
  return true;
}

void copyBoard(Square dest[9][9], Square source[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      dest[i][j].value = source[i][j].value;
      for (int k = 0; k < 9; k++) {
        dest[i][j].possible[k] = source[i][j].possible[k];
      }
    }
  }
}

void findSquareToGuess(Square board[9][9], int *row, int *col, int arr[9]) {
  int num = 2;
  for (int i = 0; i < 9; i++) {
    arr[i] = -1;
  }

  bool notFound = true;
  while (notFound) {
    for (int i = 0; i < 9 && notFound; i++) {
      for (int j = 0; j < 9 && notFound; j++) {
        int count = 0;
        if (board[i][j].value == 0) {
          for (int k = 0; k < 9; k++) {
            if (board[i][j].possible[k]) {
              count++;
            }
          }
          if (count == num) {
            int index = 0;
            *row = i;
            *col = j;
            for (int n = 1; n <= 9; n++) {
              if (board[i][j].possible[n - 1]) {
                arr[index] = n;
                index++;
              }
            }
            notFound = false;
          }
        }
      }
    }
    num++;
  }
}

void solve(Square main[9][9], Square board[9][9]) {
  bool status = true;

  while (status) {
    status = false;

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j].value == 0) {
          bool elim = checkSquare(board, i, j);
          bool solu = hasSolution(board, i, j);
          if (elim || solu) {
            status = true;
          }
        }
      }
    }

    bool scan = scanForSolution(board);
    if (scan) {
      status = true;
    }
  }

  if (isSolved(board)) {
    copyBoard(main, board);
  } else if (wrongSolution(board)) {
    return;
  } else {
    int row, col, arr[9];
    findSquareToGuess(board, &row, &col, arr);
    int index = 0;
    while (arr[index] != -1) {
      Square temp[9][9];
      copyBoard(temp, board);
      temp[row][col].value = arr[index];
      index++;
      solve(main, temp);
    }
  }
}