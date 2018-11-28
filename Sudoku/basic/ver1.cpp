#include <cstdio>

void print_board(int puzzle[][9]);
int solve_sudoku(int puzzle[][9], int row, int col);
int isValid(int number, int puzzle[][9], int row, int col);

int main()
{
    int puzzle[9][9]= {
        {0, 0, 0, 0, 0, 0, 0, 9, 0},
        {1, 9, 0, 4, 7, 0, 6, 0, 8},
        {0, 5, 2, 8, 1, 9, 4, 0, 7},
        {2, 0, 0, 0, 4, 8, 0, 0, 0},
        {0, 0, 9, 0, 0, 0, 5, 0, 0},
        {0, 0, 0, 7, 5, 0, 0, 0, 9},
        {9, 0, 7, 3, 6, 4, 1, 8, 0},
        {5, 0, 6, 0, 8, 1, 0, 7, 4},
        {0, 8, 0, 0, 0, 0, 0, 0, 0}
    };

    if (solve_sudoku(puzzle, 0, 0)) print_board(puzzle);
    else printf("No solution!");

    return 0;
}

int solve_sudoku(int puzzle[][9], int row, int col)
{
    if (row==9) return 1;

    if (puzzle[row][col]) {
        if (col==8) {
            if (solve_sudoku(puzzle, row+1, 0)) return 1;
        } else {
            if (solve_sudoku(puzzle, row, col+1)) return 1;
        }
        return 0;
    }

    for (int nextNum = 1; nextNum<10; nextNum++) {
        if(isValid(nextNum, puzzle, row, col)) {
            puzzle[row][col] = nextNum;
            if (col<8) {
                if (solve_sudoku(puzzle, row, col+1)) return 1;
            } else {
                if (solve_sudoku(puzzle, row+1, 0)) return 1;
            }
            // We failed to find a valid value for this 
            puzzle[row][col] = 0;
        }
    }
    return 0;
}

int isValid(int number, int puzzle[][9], int row, int col)
{
    int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;

    for(int i=0; i<9; ++i)
    {
        if (puzzle[row][i] == number) return 0;
        if (puzzle[i][col] == number) return 0;
        if (puzzle[rowStart + (i%3)][colStart + (i/3)] == number) return 0;
    }
    return 1;
}

void print_board(int puzzle[][9])
{
    printf("\n +-------+-------+-------+\n");
    for(int i=1; i<10; ++i) {
        for(int j=1; j<10; ++j) {
            if (j%3==1) printf(" | ");
            else printf(" ");
            printf("%d", puzzle[i-1][j-1]);
        }
        printf(" |\n");
        if (i%3 == 0) printf(" +-------+-------+-------+\n");
    }
}
