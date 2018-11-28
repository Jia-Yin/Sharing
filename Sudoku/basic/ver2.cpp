#include <cstdio>

void print_board(int puzzle[][9]);
int solve(int puzzle[][9], int pos);
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

    if (solve(puzzle, 0)) print_board(puzzle);
    else printf("No solution!");

    return 0;
}

int solve(int puzzle[][9], int pos)
{
    if (pos>80) return 1;

    int row=pos/9, col=pos%9;

    if (puzzle[row][col]) return (solve(puzzle, pos+1));

    for (int nextNum=1; nextNum<10; nextNum++) {
        if(isValid(nextNum, puzzle, row, col)) {
            puzzle[row][col] = nextNum;
            if (solve(puzzle, pos+1)) return 1;
        }
    }
    // Ｆailed to find a valid value, go back to previous cell for another try
    puzzle[row][col] = 0; // reset before goback
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
