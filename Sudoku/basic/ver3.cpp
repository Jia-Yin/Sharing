#include <iostream>
#include <set>

using namespace std;

set<int> q[10];
set<int> p[81];
int count=0;
int board[9][9]={
    { 0,0,1,0,3,9,0,0,5 },
    { 3,0,0,4,0,0,0,0,0 },
    { 4,0,0,0,0,0,3,0,0 },
    { 5,7,0,0,6,0,0,0,0 },
    { 0,1,0,0,9,0,0,5,0 },
    { 0,0,0,0,8,0,0,1,6 },
    { 0,0,8,0,0,0,0,0,7 },
    { 0,0,0,0,0,7,0,0,3 },
    { 1,0,0,6,4,0,9,0,0 }
};

void initialize();
bool isValid(int pos, int num);
void nextState(int pos, int num);
void prevState(int pos, int num);
bool isRelated(int pos1, int pos2);
bool solve();

int main()
{
    initialize();
    solve();
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) printf("%d", board[i][j]);
        printf("\n");
    }
    return 0;
}

bool solve()
{
    if (count==81) return true;
    int index=1;
    while (q[index].empty()) index++; // Find the smallest index not empty
    int pos=*(q[index].begin());
    for (int num=1; num<10; num++) {
        if (isValid(pos, num)) {
            int r=pos/9, c=pos%9;
            board[r][c] = num;
            nextState(pos, num);
            count++;
            if (solve()) return true;
            count--;
            board[r][c] = 0;
            prevState(pos, num);
        }
    }
    return false;
}

bool isRelated(int pos1, int pos2)
{
    int r1=pos1/9, c1=pos1%9;
    int r2=pos2/9, c2=pos2%9;
    if (r1==r2 || c1==c2) return true;
    if ((r1/3)*3==(r2/3)*3 && (c1/3)*3==(c2/3)*3) return true;
    return false;
}

void prevState(int pos, int num)
{
    for (int i=0; i<81; i++) {
        if (pos==i) {
            q[p[i].size()].insert(i);
        } if (isRelated(pos, i)) {
            if (isValid(i, num) && !board[i/9][i%9]) { // Note: Empty pos before this check!
                q[p[i].size()].erase(i);
                p[i].insert(num);
                q[p[i].size()].insert(i);
            }
        }
    }
}

void nextState(int pos, int num)
{
    for (int i=0; i<81; i++) {
        if (pos==i) {
            q[p[i].size()].erase(i);
        } else if (isRelated(pos, i) && !board[i/9][i%9]) {
            if (p[i].find(num)!=p[i].end()) {
                q[p[i].size()].erase(i);
                p[i].erase(num);
                q[p[i].size()].insert(i);
            }
        }
    }
}

bool isValid(int pos, int num)
{
    int r=pos/9, c=pos%9;
    if(board[r][c]) return false;
    int sr=(r/3)*3, sc=(c/3)*3;
    for (int i=0; i<9; i++) {
        if(board[r][i]==num) return false;
        if(board[i][c]==num) return false;
        if(board[sr+i/3][sc+i%3]==num) return false;
    }
    return true;
}

void initialize()
{
    for(int pos=0; pos<81; pos++) {
        int r=pos/9, c=pos%9;
        if(board[r][c]) { count++; continue; }
        for(int num=1; num<10; num++) {
            if(isValid(pos,num)) p[pos].insert(num);
        }
        q[p[pos].size()].insert(pos);
    }
}
