/* Bai tap 2_23 - Chuong trinh ve PolySpirals */
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293

void PolySpiral(int first, int changed_angle, int changed_length)
{
  int angle, x, y, centerx, centery, len = 0;
  cleardevice();
  moveto(getmaxx() / 2, getmaxy() / 2);
  centerx = getmaxx() / 2;
  centery = getmaxy() / 2;
  angle = first;
  do {
    x = centerx + len * cos((double)angle * RADS);
    y = centery + len * sin((double)angle * RADS);
    lineto(x, y);
    angle += changed_angle;
    len   += changed_length;
    angle %= 360;
    delay(100);
  } while ((getx()>=0) && (getx() <= getmaxx()) &&
           (gety()>=0) && (gety() <= getmaxy()));
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  setcolor(YELLOW);

  PolySpiral(-90, 144, 3);
  getch();

  PolySpiral(0, 170, 2);
  getch();

  PolySpiral(0, 60, 2);
  getch();

  PolySpiral(0, 89, 3);
  getch();

  closegraph();
}