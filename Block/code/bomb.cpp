#include "bomb.h"
#include "rlutil.h"

using namespace rlutil;

Bomb::Bomb(Board *pbd) : Ball(pbd)
{
    locate(m_cx, m_cy);
    std::cout << ' ';
    m_cx = 20;
    m_cy = 3;
    m_dx = 1;
    m_dy = 0;
    m_ch = '=';
    m_color = 15;
    m_speed = 3;
}

int Bomb::Run()
{
    int pos;
    pos = Ball::Run();
    if (m_cx==m_pbd->Getlx()+1) return 9999;
    if (m_cx==m_pbd->Getrx()-1) return 9999;
    if (m_cy==m_pbd->Getly()+1) return 9999;
    if (m_cy==m_pbd->Getry()-1) return 9999;
    return pos;
}

Bomb::~Bomb()
{
}
