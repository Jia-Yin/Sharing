#ifndef BALL_H
#define BALL_H

#include "board.h"

enum BallType { BALL, COLORBALL, HIDDENBALL };

class Ball
{
    public:
        Ball(Board *pbd);
        virtual BallType Type() { return BALL; }
        virtual ~Ball();
        virtual int Run();
        int getPos() { return 100*m_cx+m_cy; }
        void SetDelay(int s) { m_speed=s; }
    protected:
        int m_cx;
        int m_cy;
        int m_dx;
        int m_dy;
        int m_color;
        int m_tick;
        int m_speed;
        char m_ch;
        Board *m_pbd;
};

#endif // BALL_H
