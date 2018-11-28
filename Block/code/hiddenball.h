#ifndef HIDDENBALL_H
#define HIDDENBALL_H

#include "ball.h"


class HiddenBall : public Ball
{
    public:
        HiddenBall(Board *pbd);
        BallType Type() { return HIDDENBALL; }
        int Run();
        virtual ~HiddenBall();
    protected:
    private:
};

#endif // HIDDENBALL_H
