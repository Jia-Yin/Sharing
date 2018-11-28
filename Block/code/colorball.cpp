#include "colorball.h"
#include "rlutil.h"

using namespace std;
using namespace rlutil;

ColorBall::ColorBall(Board *pbd) : Ball(pbd)
{
    //ctor
}

int ColorBall::Run()
{
    m_tick++;
    if (m_tick%m_speed) return m_cx*100+m_cy;
    locate(m_cx, m_cy);
    cout << ' ';
    if (m_cx == m_pbd->Getlx()+1) m_dx = -m_dx;
    if (m_cx == m_pbd->Getrx()-1) m_dx = -m_dx;
    if (m_cy == m_pbd->Getly()+1) m_dy = -m_dy;
    if (m_cy == m_pbd->Getry()-1) m_dy = -m_dy;
    m_cx += m_dx;
    m_cy += m_dy;
    locate(m_cx, m_cy);
    setColor(m_color++);
    if (m_color>15) m_color=0;
    cout << m_ch;
    return m_cx*100+m_cy;
}



ColorBall::~ColorBall()
{
    //dtor
}
