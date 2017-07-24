/* Bai tap 2_25 - Chuong trinh ve duong C-Curve */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293

void CCurve(int dir, double len, int n)
{
  if (n>0)
  {
    dir += 45;
    CCurve(dir, len * FCT, n-1);
    dir -= 90;
    CCurve(dir, len * FCT, n-1);
    dir += 45;
  }
  else
    linerel(len * cos(RADS * dir), len * sin(RADS * dir));
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  double temp;

  initgraph(&gr_drive, &gr_mode, "");
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());

  moveto(200,150);
  CCurve(0, 260, 14);

  getch();
  closegraph();
}