#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"
#include <ctime>
#include <vector>

class CSnake:public CFramedWindow
{
private:
    CPoint aphel_pos;
    CPoint waz_pos;
    CPoint waz_dir;
    int snek_size;
    int time_cap;
    int timer;
    int points;
    int level;
    bool fail;
    list<CPoint> old_pos;
public:
  CSnake(CRect r, char _c = ' ');
  void paint();
  void Apfel();
  void move_waz(CPoint direction);
  bool handleEvent(int key);
  bool in_frame();
};

#endif
