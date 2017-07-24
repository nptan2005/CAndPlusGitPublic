/* Bai tap 2_17 - Chuong trinh minh hoa chuyen dong cua mot trai pinball */
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>

#define RADIUS 4
#define BALLCOLOR 14
#define BACKCOLOR 0
#define DELAY 10

void run_pinball()
{
  int dx, dy, x, y, dung = 0;

  randomize();
  do {
    dx = random(3) - 1;
  } while (dx == 0);
  do {
    dy = random(3) - 1;
  } while (dy == 0);
  x = random(getmaxx());
  y = random(getmaxy());

  rectangle(0, 0, getmaxx(), getmaxy());
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
    if (dung)
    {
      sound (1000);
      delay(50);
      nosound();
      dung = 0;
    }
  } while (!kbhit());
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");

  run_pinball();
  getch();
  closegraph();
}