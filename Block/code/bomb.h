#ifndef BOMB_H
#define BOMB_H

#include "ball.h"

class Bomb : public Ball
{
    public:
        Bomb(Board *pbd);
        int Run();
        void setDir(int dx, int dy) { m_dx=dx; m_dy=dy; }
        void setPos(int pos) { m_cx=pos/100; m_cy=pos%100; }
        virtual ~Bomb();
    protected:
    private:
};

#endif // BOMB_H
