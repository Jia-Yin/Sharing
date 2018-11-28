#include "hiddenball.h"
#include "rlutil.h"

using namespace std;
using namespace rlutil;

HiddenBall::HiddenBall(Board *pbd) : Ball(pbd)
{
    //ctor
}

int HiddenBall::Run()
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
    setColor(m_color);
    if ((m_tick/m_speed) % 10 < 5) cout << m_ch;
    return m_cx*100+m_cy;
}

HiddenBall::~HiddenBall()
{
    //dtor
}
