#include <cstdio>
#include "rlutil.h"
#include <cstdlib>
#include <ctime>

#define BCOLOR 8
#define CCOLOR 15
#define CURSOR 12
using namespace rlutil;

struct SudokuDataHeader {
    int numbers;
    int datasize;
};

struct SudokuProblem {
    int id;
    int data[9][9];
};

SudokuProblem CurProblem, Solution;

void print_board(SudokuProblem sp);
int solve(int puzzle[][9], int pos);
int isValid(int number, int puzzle[][9], int row, int col);
void hline(int r1, int c1, int c2, int color, char c);
void gotopos(int k);
void gotopos(int r, int c);
bool process_input(int k, int r, int c);
void moveup();
bool finished();

int CurPos = 18;
int Lives = 5;

int main()
{
    FILE *fp;
    SudokuDataHeader sdh;
    int k;

    cls();
    fp = fopen("sudoku.dat", "rb");
    fread((void*)&sdh, sizeof(sdh),  1, fp); // Read header
    printf("\n\nMy Sudoku Game\n\n");
    printf("\nTotal Problems = %d\n", sdh.numbers);
    printf("Select problem ID (Input 0 for random) : ");
    scanf("%d", &k);
    srand(time(NULL)); // Randomize the seed
    if (k<1 || k>sdh.numbers) k = rand() % sdh.numbers;
    printf("\n\nOK, Problem ID = %d\n", k);
    fseek(fp, (k-1)*sdh.datasize, SEEK_CUR); // Jump k records
    fread((void*)&CurProblem, sizeof(CurProblem), 1, fp);

    printf("Use arrow keys to move. Type number for the blank position.\n");
    printf("If you make 5 mistakes, then you are out!\n");
    anykey("Press any key to start. Good luck!");

    Solution = CurProblem;
    solve(Solution.data, 0);
    print_board(CurProblem);

    int r=0, c=0;
    gotopos(r,c);
    gotoxy(40, 2); std::cout <<"(0,0)"; // Output player
    gotoxy(40, 3); std::cout <<"Lives = " << Lives;
    int cnt=0;
    bool finish=false;
    while (1) {
        hidecursor();
        if (kbhit()) {
            int k = rlutil::getkey(); // Get character
            if (k == rlutil::KEY_LEFT) --c;
            else if (k == rlutil::KEY_RIGHT) ++c;
            else if (k == rlutil::KEY_UP) --r;
            else if (k == rlutil::KEY_DOWN) ++r;
            else if (k >= '1' && k <= '9') {
                finish = process_input(k, r, c);
                if (finish) break;
                if (!Lives) break;
            } else if (k == rlutil::KEY_ESCAPE) break;
            gotoxy(40, 2); std::cout <<"("<<r+1<<","<<c+1<<")"; // Output player
            gotoxy(40, 3); std::cout <<"Lives = " << Lives;
        }
        if (!(++cnt%2000)) { gotoxy(40, 4); std::cout << "Times = " << cnt/2000; }
        std::cout.flush();
        r = (r+9) % 9;
        c = (c+9) % 9;
        showcursor();
        gotopos(r,c);
    }
    gotoxy(40, 3); std::cout <<"Lives = " << Lives;
    gotoxy(30,18);
    setColor(15);
    if (finish) printf("You did it! Spent time = %d!\n\n", cnt/2000);
    else if (!Lives) printf("You lose the game!\n\n");
    else printf("You abandoned!\n\n");

    return 0;
}

bool finished()
{
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if(CurProblem.data[i][j]==0) return false;
        }
    }
    return true;
}

bool process_input(int k, int r, int c)
{
    if (CurProblem.data[r][c]==0) {
        if (k-'0' == Solution.data[r][c]) {
            printf("%c", k);
            CurProblem.data[r][c] = k-'0';
            if (finished()) return true;
        } else {
            Lives--;
            gotoxy(40, 6);
            printf("Error!\x07");
            msleep(500);
            gotoxy(40, 6);
            printf("          ");
        }
    }
    return false;
}

void gotopos(int r, int c)
{
    int ypos[] = {5, 6, 7, 9, 10, 11, 13, 14, 15};
    int xpos[] = {4, 6, 8, 12, 14, 16, 20, 22, 24};
    setColor(CURSOR);
    locate(xpos[c], ypos[r]);
}

void gotopos(int k)
{
    gotopos(k/9, k%9);
}

void moveup()
{
    int nr, np;
    bool found=false;
    int r=CurPos/9, c=CurPos%9;
    for (int i=1; i<9; i++) {
        nr = (r+9-i) % 9;
        if (!CurProblem.data[nr][c]) {
            np = nr*9 + c;
            found=true; break;
        }
    }
    if (!found) {
        for (int p=1; p<81; p++) {
            np = (CurPos+81-p) % 81;
            if (!CurProblem.data[np/9][np%9]) { found=true; break; }
        }
    }
    if (found) { CurPos = np; gotopos(np); }
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
    // ¢?ailed to find a valid value, go back to previous cell for another try
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

void print_board(SudokuProblem sp)
{
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
            printf("%c", t ? t+'0' : '_');
            setColor(BCOLOR);
        }
        printf(" |\n");
        if (i == 9) printf(" +=======================+\n");
        else if (i%3 == 0) printf(" +-----------------------+\n");
    }
}
