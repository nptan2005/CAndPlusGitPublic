/* Bai tap 2_27 - Chuong trinh ve duong Koch */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293

void Koch(int dir, double len, int n)
{
  if (n>0)
  {
    Koch(dir, len / 3, n-1);
    dir += 60;
    Koch(dir, len / 3, n-1);
    dir -= 120;
    Koch(dir, len / 3, n-1);
    dir += 60;
    Koch(dir, len / 3, n-1);
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

  moveto(100,350);
  Koch(0, 420 , 4);
  Koch(-120, 420 , 4);
  Koch(120, 420 , 4);
  getch();

  closegraph();
}