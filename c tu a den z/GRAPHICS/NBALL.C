/* Bai tap 2_81 - Chuong trinh minh hoa chuyen dong cua nhieu trai pinball */
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>

#define RADIUS 3
#define BALLCOLOR 14
#define BACKCOLOR 0
#define DELAY 2
#define MAXBALLS 10

struct tagball {
  int x, y, dx, dy;
} nball[MAXBALLS];

void run_pinball()
{
  int i, dung = 0;

  randomize();
  for (i=0; i<MAXBALLS; i++)
  {
    do {
      nball[i].dx = random(3) - 1;
    } while (nball[i].dx == 0);
    do {
      nball[i].dy = random(3) - 1;
    } while (nball[i].dy == 0);
    nball[i].x = random(getmaxx());
    nball[i].y = random(getmaxy());
  }
  rectangle(0, 0, getmaxx(), getmaxy());
  do {
    setcolor(BALLCOLOR);
    setfillstyle(SOLID_FILL, BALLCOLOR);
    for (i=0; i<MAXBALLS; i++)
      fillellipse(nball[i].x, nball[i].y, RADIUS, RADIUS);
    delay(DELAY);
    for (i=0; i<MAXBALLS; i++)
    {
      setcolor(BACKCOLOR);
      setfillstyle(SOLID_FILL, BACKCOLOR);
      fillellipse(nball[i].x, nball[i].y, RADIUS, RADIUS);
      nball[i].x += nball[i].dx;
      nball[i].y += nball[i].dy;
      if (nball[i].x < RADIUS +1 || nball[i].x > getmaxx() - RADIUS - 1)
      {
        nball[i].dx = -nball[i].dx;
        nball[i].x += 2 * nball[i].dx;
        dung = 1;
      }
      if (nball[i].y < RADIUS + 1 || nball[i].y > getmaxy() - RADIUS - 1)
      {
        nball[i].dy = -nball[i].dy;
        nball[i].y += 2 * nball[i].dy;
        dung = 1;
      }
      if (dung)
      {
        sound (1000);
        delay(20);
        nosound();
        dung = 0;
      }
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