#include <iostream>
#include <vector>
#include "board.h"
#include "player.h"
#include "rlutil.h"
#include "hiddenball.h"
#include "colorball.h"
#include "bomb.h"

using namespace std;
using namespace rlutil;

int main()
{
    Board brd(1,1,60,20);
    brd.Score();
    Player p1(&brd);
    vector<Ball*> balls;
    int score, lastkey=0, bpos;
    Bomb *bb = NULL;
    balls.push_back(new Ball(&brd));
    balls.push_back(new Ball(&brd));
    balls[0]->SetDelay(4);
    balls[1]->SetDelay(8);
    hidecursor();
    while (true) {
        if (kbhit()) {
            int k = getkey();
            if (k==KEY_ESCAPE) break;
            if (k==KEY_UP) p1.up();
            if (k==KEY_DOWN) p1.down();
            if (k==KEY_LEFT) p1.left();
            if (k==KEY_RIGHT) p1.right();
            if (k==KEY_SPACE) {
                if (!bb) {
                    bb = new Bomb(&brd);
                    int pos = p1.getPos();
                    if (lastkey==KEY_UP) {
                        bb->setDir(0,-1); bb->setPos(pos-1);
                    }
                    if (lastkey==KEY_DOWN) {
                        bb->setDir(0,1); bb->setPos(pos+1);
                    }
                    if (lastkey==KEY_LEFT) {
                        bb->setDir(-1,0); bb->setPos(pos-100);
                    }
                    if (lastkey==KEY_RIGHT) {
                        bb->setDir(1,0); bb->setPos(pos+100);
                    }
                }
            }
            if (k!=KEY_SPACE) lastkey = k;
        }
        for (vector<Ball*>::iterator it=balls.begin(); it!=balls.end(); it++) {
            int pos;
            if(bb) {
                bpos = bb->Run();
                if (bpos==9999) {
                    delete bb; bb=NULL;
                }
            }
            pos = (*it)->Run();
            if (pos == p1.getPos()) {
                if((*it)->Type()==COLORBALL) {
                    brd.Life();
                    brd.Flash();
                    p1.right();
                    p1.right();
                    p1.right();
                    p1.down();
                }
                else if(brd.Kill()) {
                    brd.Flash();
                    p1.right();
                    p1.right();
                    p1.right();
                    p1.down();
                } else {
                    brd.Gameover(); return 0;
                }

            }
            if (pos==bpos) {
                it = balls.erase(it);
                it--;
                continue;
            }
        }
        score = brd.Score();
        if (score%800==0) balls.push_back(new HiddenBall(&brd));
        if (score%1000==0) balls.push_back(new ColorBall(&brd));
        msleep(10);
    }
    return 0;
}
