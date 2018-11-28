#include <cstdio>
#include "rlutil.h"
#include <cstdlib>
#include <ctime>

#define BCOLOR 8
#define CCOLOR 15
using namespace rlutil;

struct SudokuDataHeader {
    int numbers;
    int datasize;
};

struct SudokuProblem {
    int id;
    int data[9][9];
};

void print_board(SudokuProblem sp);
int solve(int puzzle[][9], int pos);
int isValid(int number, int puzzle[][9], int row, int col);
void hline(int r1, int c1, int c2, int color, char c);

int main()
{
    FILE *fp;
    SudokuDataHeader sdh;
    SudokuProblem sp;

    fp = fopen("sudoku.dat", "rb");
    fread((void*)&sdh, sizeof(sdh),  1, fp); // Read header
    printf("\nTotal Problems = %d\n", sdh.numbers);
    printf("Each occupys %d bytes.\n\n", sdh.datasize);

    srand(time(NULL)); // Randomize the seed
    int k = 13; //rand()%sdh.numbers; // Select int from 0~numbers-1
    fseek(fp, k*sdh.datasize, SEEK_CUR); // Jump k records
    fread((void*)&sp, sizeof(sp), 1, fp);

    print_board(sp);
    //if (solve(sp.data, 0)) print_board(sp);
    //else printf("No solution!");

    return 0;
}

int solve(int puzzle[][9], int pos)
{
    if (pos==81) return 1;

    int row=pos/9, col=pos%9;

    if (puzzle[row][col]) return (solve(puzzle, pos+1));

    for (int nextNum = 1; nextNum<10; nextNum++) {
        if(isValid(nextNum, puzzle, row, col)) {
            puzzle[row][col] = nextNum;
            if (solve(puzzle, pos+1)) return 1;
        }
    }
    // ¢Ôailed to find a valid value, go back to previous cell for another try
    puzzle[row][col] = 0; // reset before goback
    return 0;
}

void hline(int r1, int c1, int c2, int color, char c)
{
    setColor(color);
    locate(r1, c1);
    for (int i=c1; i<=c2; i++) printf("%c", c);
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

void print_board(SudokuProblem sp)
{
    //hline(1,1,20,3,'#');
    cls();
    printf("\n     Problem ID = %d\n", sp.id);
    setColor(BCOLOR);
    printf("\n +=======================+\n");
    for(int i=1; i<10; ++i) {
        for(int j=1; j<10; ++j) {
            if (j%3==1) printf(" | ");
            else printf(" ");
            setColor(CCOLOR);
            int t = sp.data[i-1][j-1];
            printf("%c", t ? t+'0' : ' ');
            setColor(BCOLOR);
        }
        printf(" |\n");
        if (i%3 == 0) printf(" +=======================+\n");
    }
}
