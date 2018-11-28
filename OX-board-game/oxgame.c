#include <stdio.h>
#include <stdlib.h>

#define D2(x,y)  ((x)*(x)+(y)*(y))

int board[3][3];
void init_board();
void print_board();
int check(int row, int col, int player);

int main()
{
    int cnt, player, row, col, row2, col2;
    char rc, cc;
    init_board();
    print_board();
    for (cnt=0; ;cnt++) {
        player = (cnt%2) ? 'X' : 'O';
        if (cnt<6) {
            do {
                printf("%c move: ", player);
                scanf("\n%c%c", &cc, &rc);
                row2 = rc-'1';
                col2 = cc-'A';
            } while (row2<0 || row2>2 || col2<0 || col2>2 || board[row2][col2]!=' ');
            board[row2][col2] = player;
        } else {
            do {
                do {
                    printf("%c move, from: ", player);
                    scanf("\n%c%c", &cc, &rc);
                    row = rc-'1';
                    col = cc-'A';
                } while (row<0 || row>2 || col<0 || col>2 || board[row][col]!=player);
                do {
                    printf("%c move, to: ", player);
                    scanf("\n%c%c", &cc, &rc);
                    row2 = rc-'1';
                    col2 = cc-'A';
                } while (row2<0 || row2>2 || col2<0 || col2>2 || board[row2][col2]!=' ');
            } while (D2(row-row2, col-col2)!=1);
            board[row2][col2] = player;
            board[row][col] = ' ';
        }
        print_board();

        if (check(row2, col2, player)) break;
    }
    printf("%c wins!\n\n", player);
    return 0;
}

int check(int row, int col, int player)
{
    if (board[row][0]==player && board[row][1]==player && board[row][2]==player) return 1;
    if (board[0][col]==player && board[1][col]==player && board[2][col]==player) return 1;
    if (board[0][0]==player && board[1][1]==player && board[2][2]==player) return 1;
    if (board[0][2]==player && board[1][1]==player && board[2][0]==player) return 1;
    return 0;
}

void init_board()
{
    int i, j;
    for (i=0; i<3; i++) for (j=0; j<3; j++) board[i][j]=' ';
}

void print_board()
{
    printf("\n    A   B   C\n\n");
    printf("1   %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("   ---+---+---\n");
    printf("2   %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("   ---+---+---\n");
    printf("3   %c | %c | %c\n\n", board[2][0], board[2][1], board[2][2]);
}

