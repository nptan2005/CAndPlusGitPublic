/* Bai tap 2_24 -Chuong trinh ve duong Dragons */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293

#define LEFT 0
#define RIGHT 1

void Dragons(int dir, double len, int n, int leftright)
{
  if (n>0)
  {
    if (leftright==LEFT)
    {
       dir += 45;
       Dragons(dir, len * FCT, n-1, LEFT);
       dir -= 90;
       Dragons(dir, len * FCT, n-1, RIGHT);
       dir += 45;
    }
    else
    {
       dir -= 45;
       Dragons(dir, len * FCT, n-1, LEFT);
       dir += 90;
       Dragons(dir, len * FCT, n-1, RIGHT);
       dir -= 45;
    }
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
  Dragons(0, 300, 16, LEFT);

  getch();
  closegraph();
}