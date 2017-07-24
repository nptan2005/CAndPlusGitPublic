/* Bai tap 2_37 - Morphing */
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293
#define INTERLACE 100
#define NODE 10

struct pointtype T [] = {{-100, -75}, {-100, -100}, {0, -100}, {100, -100},
             {100, -75}, {20, -75}, {20, 100}, {-20, 100}, {-20, -75}, {-100, -75}};
struct pointtype HOUSE [] = {{-100, 50}, {-100, -50}, {0, -75}, {100, -50},
             {100, 50}, {20, 50}, {20, -30}, {-20, -30}, {-20, 50}, {-100, 50}};
int xc, yc;

void morphing()
{
  struct pointtype tmp[NODE];
  int i, n = 0;
  for (i=0; i<NODE; i++)
    tmp[i] = T[i];
  do {
    setcolor(BLACK);
    moveto(xc + tmp[0].x, yc + tmp[0].y);
    for (i=1; i<NODE; i++)
      lineto(xc + tmp[i].x, yc + tmp[i].y);
    for (i=0; i<NODE; i++)
    {
      tmp[i].x = T[i].x + (HOUSE[i].x - T[i].x) * n / INTERLACE;
      tmp[i].y = T[i].y + (HOUSE[i].y - T[i].y) * n / INTERLACE;
    }
    n++;
    setcolor(YELLOW);
    moveto(xc + tmp[0].x, yc + tmp[0].y);
    for (i=1; i<NODE; i++)
      lineto(xc + tmp[i].x, yc + tmp[i].y);
    delay(100);
  } while (n<100 && !kbhit());
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  xc = getmaxx() / 2;
  yc = getmaxy() / 2;

  morphing();
  getch();
  closegraph();
}