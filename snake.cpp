#include "snake.h"

CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
    srand(time(nullptr));
    aphel_pos = CPoint(rand() % geom.size.x+ geom.topleft.x, rand() % geom.size.y + geom.topleft.y);
    waz_pos = CPoint(2, 2);
    snek_size = 2;
    timer = 0;
    time_cap = 20;
    points = 0;
    level = 1;
    old_pos.assign(snek_size, waz_pos);
    fail = false;
    pause = false;
    help = false;
}



bool CSnake::handleEvent(int key)
{
    switch (key)
    {
        case KEY_UP:
            if (!(waz_dir == CPoint (0, 1))&&!pause) waz_dir = (CPoint (0, -1));
            return true;
        case KEY_DOWN:
            if (!(waz_dir == CPoint (0, -1))&&!pause) waz_dir = (CPoint (0, 1));
            return true;
        case KEY_RIGHT:
            if (!(waz_dir == CPoint (-1, 0))&&!pause) waz_dir = CPoint (1, 0);
            return true;
        case KEY_LEFT:
            if (!(waz_dir == CPoint (1, 0))&&!pause) waz_dir = CPoint (-1, 0);
            return true;
        case 'p':
            pauses();
            return true;
        case 'r':
            restart();
            return true;
        case 'h':
            help = !help;
            return true;
        case 'w':
            move (CPoint (0, -1));
            return true;
        case 'a':
            move (CPoint (0, 1));
            return true;
        case 's':
            move (CPoint (1, 0));
            return true;
        case 'd':
            move (CPoint (-1, 0));
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
    if (direction == false) {
        return;
    }
    old_pos.push_front(waz_pos);
    waz_pos += direction;
    if (waz_pos.x <= geom.topleft.x) {
        waz_pos.x += geom.size.x;
    }
    if (waz_pos.x == geom.topleft.x + geom.size.x) {
        waz_pos.x = geom.topleft.x;
    }
    if (waz_pos.y <= geom.topleft.y) {
        waz_pos.y += geom.size.y;
    }
    if (waz_pos.y == geom.topleft.y + geom.size.y) {
        waz_pos.y = geom.topleft.y;
    }
    while (snek_size < old_pos.size()) {
        old_pos.pop_back();
    }
}

void CSnake::paint() {
    for (int y = geom.topleft.y; y < geom.topleft.y + geom.size.y; y++)
        for (int x = geom.topleft.x; x < geom.topleft.x + geom.size.x; x++)
        {
            gotoyx(y, x);
            printl("%c", c);
        }
    gotoyx(geom.topleft.y -1, geom.topleft.x);
        const char* paused = (pause) ? "PAUZEN": "";
    printl("STEUFE: %i APFELN: %i %s", level, points, paused);
    for (auto i = old_pos.begin(); i != old_pos.end(); ++i) {
        if (waz_pos.x == i->x&& waz_pos.y == i->y&&in_frame()) {
            waz_dir = 0;
            fail = true;
        }
    }
    if (fail) {
        gotoyx(geom.topleft.y+6, geom.topleft.x+1);
        printl("%s", "DER WĄŻ HAT GESTERBT!!!");
    }
    else if (waz_dir == 0&&!pause) {
        gotoyx(geom.topleft.y+6, geom.topleft.x+1);
        printl("%s", "p: Pauzen");
        gotoyx(geom.topleft.y+8, geom.topleft.x+1);
        printl("%s", "h: Hilfe");
        gotoyx(geom.topleft.y+10, geom.topleft.x+1);
        printl("%s", "r: Neustart");
        gotoyx(geom.topleft.y+12, geom.topleft.x+1);
        printl("%s", "Pfeile: Der Wąż steuren");
    } else {
        move_waz(waz_dir);
        if (help) {
            gotoyx(geom.topleft.y + 14, geom.topleft.x + 1);
            printl("Wazpozition: %i %i", waz_pos.x, waz_pos.y);
            gotoyx(geom.topleft.y + 13, geom.topleft.x + 1);
            printl("Windowpozition: %i %i", geom.topleft.x, geom.topleft.y);
            gotoyx(geom.topleft.y + 6, geom.topleft.x + 1);
            printl("%s", "p: Pauzen");
            gotoyx(geom.topleft.y + 8, geom.topleft.x + 1);
            printl("%s", "h: Hilfe");
            gotoyx(geom.topleft.y + 10, geom.topleft.x + 1);
            printl("%s", "r: Neustart");
            gotoyx(geom.topleft.y + 12, geom.topleft.x + 1);
            printl("%s", "Pfeile: Der Wąż steuren");
        }
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

bool CSnake::in_frame() {
    bool is_in_x = (waz_pos.x >= geom.topleft.x)&&(waz_pos.x <= geom.topleft.x + geom.size.x);
    bool is_in_y = (waz_pos.y >= geom.topleft.y)&&(waz_pos.y <= geom.topleft.y + geom.size.y);
    return (is_in_x&&is_in_y);
}

void CSnake::pauses() {
    pause = !pause;
    if (pause_dir == false) {
        pause_dir = waz_dir;
        waz_dir.x = 0, waz_dir.y = 0;
    } else {
        waz_dir = pause_dir;
        pause_dir.x = 0, pause_dir.y = 0;
    }
}

void CSnake::restart() {
    aphel_pos = CPoint(rand() % geom.size.x+ geom.topleft.x, rand() % geom.size.y + geom.topleft.y);
    waz_pos = CPoint(2, 2);
    snek_size = 2;
    timer = 0;
    time_cap = 20;
    points = 0;
    level = 1;
    old_pos.clear();
    old_pos.assign(snek_size, waz_pos);
    waz_dir.x =0, waz_dir.y = 0;
    fail = false;
    pause = false;
    help = false;
}
