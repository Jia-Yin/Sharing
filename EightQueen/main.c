#include <stdio.h>

void solve(int pos, int cnt);
void printBoard();
int  isValid(int pos);

int board[8][8] = {{0}};
int total=0;

int main()
{
	solve(0, 0);
	return 0;
}

void solve(int pos, int cnt)
{
	if (cnt==8) { printBoard(); return; }
	if (pos==64) return;
	if (isValid(pos)) {
		board[pos/8][pos%8] = 1;
		solve(pos+1, cnt+1);
	}
	board[pos/8][pos%8] = 0;
	solve(pos+1, cnt);
}	

void printBoard()
{
	printf("Solution %d:\n", ++total);
	for (int i=0; i<8; i++) {
		for (int j=0; j<8; j++) printf(" %c ", board[i][j]? 'O': '+');
		printf("\n");
	}
	printf("\n\n");
}

int isValid(int pos)
{
	int row=pos/8, col=pos%8;
	int diff=row-col, sum=row+col;
	for (int p=0; p<pos; p++) {
		int r=p/8, c=p%8;
		if (board[r][c]==0) continue;
		if (row==r || col==c || diff==r-c || sum==r+c) return 0;
	}
	return 1;
}

