#include "snake.h"

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
    //TY PIDOR
    srand(time(nullptr));
    aphel_pos = CPoint(rand() % geom.size.x+ geom.topleft.x, rand() % geom.size.y + geom.topleft.y);
    waz_pos = CPoint(2, 2);
    snek_size = 2;
    timer = 0;
    time_cap = 20;
    points = 0;
    level = 1;
    old_pos.assign(snek_size, waz_pos);
}

bool CSnake::handleEvent(int key)
{
    switch (key)
    {
        case KEY_UP:
            waz_dir = (CPoint (0, -1));
            return true;
        case KEY_DOWN:
            waz_dir = (CPoint (0, 1));
            return true;
        case KEY_RIGHT:
            waz_dir = CPoint (1, 0);
            return true;
        case KEY_LEFT:
            waz_dir = CPoint (-1, 0);
            return true;
    };
    if ((time_cap-(points*level)) >= timer) {
        timer++;
        return false;
    }
    timer = 0;
    return true;
}

void CSnake::move_waz(CPoint direction) {
    old_pos.push_front(waz_pos);
    waz_pos += direction;
    while (snek_size < old_pos.size()) {
        old_pos.pop_back();
    }
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
    gotoyx(geom.topleft.y -1, geom.topleft.x);
    printl("STEUFE: %i APFELN: %i", level, points);
    if (waz_dir == 0) {
        gotoyx(geom.topleft.y+6, geom.topleft.x+1);
        printl("%s", "p: Pauzen");
        gotoyx(geom.topleft.y+8, geom.topleft.x+1);
        printl("%s", "h: Nach spacieren");
        gotoyx(geom.topleft.y+10, geom.topleft.x+1);
        printl("%s", "r: ");
        gotoyx(geom.topleft.y+12, geom.topleft.x+1);
        printl("%s", "Pfeile: Der Wąż steuren");
    } else {
        move_waz(waz_dir);
    }
    for (auto i = old_pos.begin(); i != old_pos.end(); ++i) {
        gotoyx(i->y, i->x);
        printl("%c", '#');
    }

    gotoyx(waz_pos.y, waz_pos.x);
    printl("%c", '*');
    if (waz_pos == aphel_pos) {
        aphel_pos = CPoint(rand() % geom.size.x + geom.topleft.x, rand() % geom.size.y + geom.topleft.y);
        snek_size++;
        points++;
    }
    Apfel();
}

void CSnake::Apfel() {
    gotoyx(aphel_pos.y, aphel_pos.x);
    printl("%c", 'O');
}