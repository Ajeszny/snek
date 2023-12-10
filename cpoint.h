#ifndef __CPOINT_H__
#define __CPOINT_H__

#include <list>

using namespace std;

struct CPoint
{
  int x;
  int y;
  CPoint(int _x=0, int _y=0): x(_x), y(_y) {};
  CPoint& operator+=(const CPoint& delta)
  {
    x+=delta.x;
    y+=delta.y;
    return *this;
  }
  bool operator == (bool other) const {
      if (!other) {
          return (this->x == 0 && this->y == 0);
      }
      return !(this->x == 0 && this->y == 0);
  }

    bool operator == (const CPoint& other) const {
        return (this->x == other.x && this->y == other.y);
    }
};



struct CRect
{
  CPoint topleft;
  CPoint size;
  CRect(CPoint t1=CPoint(), CPoint s=CPoint()):
    topleft(t1), size(s) {};
};

#endif
