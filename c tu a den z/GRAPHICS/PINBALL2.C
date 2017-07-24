/* Bai tap 2_80 - Chuong trinh minh hoa chuyen dong cua
   mot trai pinball co tam do o duoi */
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>

#define RADIUS 3
#define BALLCOLOR 14
#define BACKCOLOR 0
#define DELAY 3

void run_pinball()
{
  int dx, dy, x, y, dung = 0, i;
  int xpad, ypad;
  char c;

  randomize();
  do {
    dx = random(3) - 1;
  } while (dx == 0);
  do {
    dy = random(3) - 1;
  } while (dy == 0);
  x = random(getmaxx());
  y = random(getmaxy());
  xpad = getmaxx()/2 - 20;
  ypad = getmaxy() - 11;

  rectangle(0, 0, getmaxx(), getmaxy());
  rectangle(xpad, ypad, xpad + 40, ypad+10);
  do {
    setcolor(BALLCOLOR);
    setfillstyle(SOLID_FILL, BALLCOLOR);
    fillellipse(x, y, RADIUS, RADIUS);
    delay(DELAY);
    setcolor(BACKCOLOR);
    setfillstyle(SOLID_FILL, BACKCOLOR);
    fillellipse(x, y, RADIUS, RADIUS);
    x += dx;
    y += dy;
    if (x < RADIUS +1 || x > getmaxx() - RADIUS - 1)
    {
      dx = -dx;
      x += 2 * dx;
      dung = 1;
    }
    if (y < RADIUS + 1 || y > getmaxy() - RADIUS - 1)
    {
      dy = -dy;
      y += 2 * dy;
      dung = 1;
    }
    if (abs(y-ypad) <= RADIUS && (x-xpad)<40 && (x-xpad)>0)
    {
      dy = -dy;
      y += 2 * dy;
      dung = 1;
    }
    if (dung)
    {
      sound (1000);
      dung = 0;
      i = 20;
    }
    if (i>0)
    {
      i--;
      if (i == 0)
        nosound();
    }
    if (kbhit())
    {
      c = getch();
      if (c == 0)
        c = getch();
      setcolor(BLACK);
      rectangle(xpad, ypad, xpad + 40, ypad+10);
      switch(c)
      {
        case 75 : if (xpad > 0)
                    xpad -= 20;
                  break;
        case 77 : if (xpad < getmaxx() - 40)
                    xpad += 20;
                  break;
      }
      setcolor(WHITE);
      rectangle(xpad, ypad, xpad + 40, ypad+10);
    }
  } while (c != 27);
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");

  run_pinball();
  closegraph();
  nosound();
}