#include "board.h"
#include "rlutil.h"
#include <cstdio>

using namespace std;
using namespace rlutil;

Board::Board(int lx, int ly, int rx, int ry)
{
    m_lx = lx;
    m_ly = ly;
    m_rx = rx;
    m_ry = ry;
    m_color = WHITE;
    m_ch = '#';
    m_score = 0;
    life = 3;
    PlotBorder();
    //ctor
}

int Board::Score()
{
    int left = (m_lx + m_rx)/2 - 3;
    locate(left, m_ry);
    setColor(WHITE);
    printf(" %05d ", m_score++);
    return m_score;
}

void Board::Gameover()
{
    int left = (m_lx + m_rx)/2 - 5;
    int top  = (m_ly + m_ry)/2 - 2;
    locate(left, top);
    setColor(WHITE);
    printf(" GAME OVER ");
    locate(left-2, top+1);
    printf("              ");
    locate(left-2, top+2);
    printf(" SCORE = %05d ", m_score);
    locate(left-2, top+3);
    printf("              ");
}

int Board::Kill()
{
    life--;
    return life;
}

void Board::Flash()
{
    int original = m_color;
    m_color = 13;
    PlotBorder();
    msleep(500);
    m_color = 12;
    PlotBorder();
    msleep(500);
    m_color = original;
    PlotBorder();
}

void Board::PlotBorder()
{
    setColor(m_color);
    for (int i=m_lx; i<=m_rx; i++) { locate(i, m_ly); cout << m_ch; }
    for (int i=m_ly; i<=m_ry; i++) { locate(m_lx, i); cout << m_ch; }
    for (int i=m_ly; i<=m_ry; i++) { locate(m_rx, i); cout << m_ch; }
    for (int i=m_lx; i<=m_rx; i++) { locate(i, m_ry); cout << m_ch; }
    locate(m_lx+4, m_ly);
    cout << " LIFE = " << life << " ";
}

Board::~Board()
{
    //dtor
}
