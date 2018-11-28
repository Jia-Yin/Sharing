#include "ball.h"
#include <cstdlib>
#include "rlutil.h"

using namespace std;
using namespace rlutil;

Ball::Ball(Board *pbd)
{
    int t;
    m_pbd = pbd;
    m_color = LIGHTBLUE;
    m_ch = 'X';
    t = pbd->Getrx()-pbd->Getlx();
    m_cx = pbd->Getlx()+3+(rand()%(t-5));
    t = pbd->Getry()-pbd->Getly();
    m_cy = pbd->Getly()+3+(rand()%(t-5));
    locate(m_cx, m_cy);
    setColor(m_color);
    m_dx=m_dy=1;
    m_tick=0;
    m_speed=5;
    cout << m_ch;
}

int Ball::Run()
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
    cout << m_ch;
    return m_cx*100+m_cy;
}

Ball::~Ball()
{
    locate(m_cx, m_cy);
    std::cout << ' ';
}
