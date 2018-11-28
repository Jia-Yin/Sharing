#ifndef COLORBALL_H
#define COLORBALL_H

#include "ball.h"

class ColorBall : public Ball
{
    public:
        int Run();
        BallType Type() { return COLORBALL; }
        ColorBall(Board *pbd);
        virtual ~ColorBall();
    protected:
    private:
};

#endif // COLORBALL_H
