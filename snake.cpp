#include "snake.h"

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
    srand(time(nullptr));
    aphel_pos = CPoint(rand() % geom.size.x, rand() % geom.size.y + geom.topleft.y);
}

void CSnake::paint() {
    //Nie, ja NIE BĘDE UŻYWAL TEGO CZAROWNICTWA Z DZIEDZICZENIEM
    //Po-pierwsze ono jest od diabla po-drugie cholernie wszystko complikuje.
    for (int y = geom.topleft.y; y < geom.topleft.y + geom.size.y; y++)
        for (int x = geom.topleft.x; x < geom.topleft.x + geom.size.x; x++)
        {
            gotoyx(y, x);
            printl("%c", c);
        }
    gotoyx(geom.topleft.y + 2, geom.topleft.x + 2);
    printl("%c", '#');
    gotoyx(geom.topleft.y + 2, geom.topleft.x + 1);
    printl("%c", '*');
    gotoyx(geom.topleft.y -1, geom.topleft.x);
    printl("%s", "STUFE 1");
    gotoyx(geom.topleft.y+6, geom.topleft.x+1);
    printl("%s", "p: Pauzen");
    gotoyx(geom.topleft.y+8, geom.topleft.x+1);
    printl("%s", "h: Nach spacieren");
    gotoyx(geom.topleft.y+10, geom.topleft.x+1);
    printl("%s", "r: Restarten");
    gotoyx(geom.topleft.y+12, geom.topleft.x+1);
    printl("%s", "Pfeile: Der Wąż steuren");
    Apfel();
}

void CSnake::Apfel() {
    gotoyx(aphel_pos.y + geom.topleft.y, aphel_pos.x + geom.topleft.x);
    printl("%c", 'O');
}