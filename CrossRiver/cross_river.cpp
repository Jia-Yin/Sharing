#include <iostream>
#include <string>

using namespace std;

const int FATHER =   0x0001;
const int BOY1   =   0x0002;
const int BOY2   =   0x0004;
const int MOTHER =   0x0008;
const int GIRL1  =   0x0010;
const int GIRL2  =   0x0020;
const int SLAVE  =   0x0040;
const int DOG    =   0x0080;
const int BOYS   =   (BOY1+BOY2);
const int GIRLS  =   (GIRL1+GIRL2);

const int TOTALITEMS = 8;
const int MASK[TOTALITEMS]   = { FATHER, BOY1, BOY2, MOTHER, GIRL1, GIRL2, SLAVE, DOG };
const string TXT[TOTALITEMS] = { "父", "B1", "B2", "MO", "G1", "G2", "SV", "DG" };

const int INITLEFT = 0xFF;
const int MAXMOVES = 1000;
const int TOTALMOVES = 21;
const int MOVES[TOTALMOVES] = { FATHER, MOTHER, SLAVE,
    FATHER+BOY1, FATHER+BOY2, FATHER+MOTHER, FATHER+GIRL1, FATHER+GIRL2, FATHER+SLAVE, FATHER+DOG,
    MOTHER+BOY1, MOTHER+BOY2, MOTHER+GIRL1, MOTHER+GIRL2, MOTHER+SLAVE, MOTHER+DOG,
    SLAVE+BOY1, SLAVE+BOY2, SLAVE+GIRL1, SLAVE+GIRL2, SLAVE+DOG };

int Left=INITLEFT, Right=0x0;
int Step[MAXMOVES], Left_Arr[MAXMOVES];
int Counter=0;

int check_move(int step, int move, int dir); // return 1: OK;  0: BAD,   dir = 1:go;  -1:return;
void print_moves(int steps); // print results
void print_status(int flag); // print flag status
void find_solution(int step, int dir);  // dir = 1:go;  -1:return;
bool status_fail(int status); // check if status ok

int main()
{
    cout << "Program start..." << endl;

    Left_Arr[0] = INITLEFT;
    find_solution(0, 1);

    return 0;
}

void find_solution(int step, int dir)  // dir = 1:go;  0:return;
{
    if(Left_Arr[step]==0) { print_moves(step); return; }
    for(int i=0; i<TOTALMOVES; i++) { // check each move
        if(check_move(step, MOVES[i], dir)) { // OK to go
            Step[step] = MOVES[i];
            Left_Arr[step+1] = Left_Arr[step] - dir*MOVES[i];
            find_solution(step+1, -dir);
        }
    }
}

bool status_fail(int status)
{
    if((FATHER&status) && (GIRLS&status) && !(MOTHER&status)) return true;
    if((MOTHER&status) && (BOYS&status) && !(FATHER&status))  return true;
    if((DOG&status) && (status!=DOG) && !(SLAVE&status))      return true;
    return false;
}

int check_move(int step, int move, int dir) // return 1: OK;  0: BAD
{
    int s;

    if (dir==1) { // Go
        if ((move & Left_Arr[step]) != move) return 0;
    } else { // Return
        if ((move & (0xFF-Left_Arr[step])) != move) return 0;
    }

    s = Left_Arr[step] - move*dir; // new left status
    for(int i=step-1; i>=0; i-=2) if (s==Left_Arr[i]) return 0; // return back step

    if(status_fail(s)) return 0;
    if(status_fail(0xFF-s)) return 0;

    return 1;
}

void print_moves(int steps) // print results
{
    cout << "\nMethod " << ++Counter << " :" << endl;

    for(int i=0; i<steps; i++) {
        cout << "Left=[ ";
        print_status(Left_Arr[i]);
        cout << "], Right=[ ";
        print_status(INITLEFT-Left_Arr[i]);
        cout << "]" << endl;

        cout << i+1 << ". ";
        if(i&1) cout << " <== ";
        else    cout << " ==> ";
        print_status(Step[i]);
        cout << endl;
    }
    cout << "Finished!" << endl;
}

void print_status(int flag) // print left and right status
{
    for(int i=0; i<TOTALITEMS; i++) if(flag&MASK[i]) cout << TXT[i] << " ";
}
