#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"
#include <ctime>

class CSnake:public CFramedWindow
{
private:
    CPoint aphel_pos;
public:
  CSnake(CRect r, char _c = ' ');
  void paint();
  void Apfel();
  //bool handleEvent(int key);

};

#endif
