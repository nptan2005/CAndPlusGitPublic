/* Bai tap 2_1 - Thuat toan Bresenham de ve duong thang (0<m<1) */
#include <graphics.h>
#include <conio.h>

void Bresenham_Line(int x1, int y1, int x2, int y2, int color)
{
  int x, y, dx, dy, e_inc, e_noinc, e;

  y = y1;
  dx = x2 - x1;
  dy = y2 - y1;
  e_noinc = dy + dy;
  e = e_noinc - dx;
  e_inc = e - dx;
  for (x=x1; x<=x2; x++)
  {
    putpixel(x, y, color);
    if (e < 0)
      e += e_noinc;
    else
    {
      y ++;
      e += e_inc;
    }
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");

  line(0, 0, getmaxx()-120, getmaxy()-150);
  Bresenham_Line(0, 0, getmaxx()-120, getmaxy()-150, 4);
  getch();
  closegraph();
}