/* Bai tap 2_2 - Thuat toan Bresenham de ve duong tron */
#include <graphics.h>
#include <conio.h>

void Bresenham_Circle(int xc, int yc, int Radius, int color)
{
  int x, y, d;

  x = 0;
  y = Radius;
  d = 3 - 2 * Radius;

  while (x <= y)
  {
    putpixel(xc + x, yc + y, color);
    putpixel(xc - x, yc + y, color);
    putpixel(xc + x, yc - y, color);
    putpixel(xc - x, yc - y, color);
    putpixel(xc + y, yc + x, color);
    putpixel(xc - y, yc + x, color);
    putpixel(xc + y, yc - x, color);
    putpixel(xc - y, yc - x, color);
    if (d < 0)
      d += 4 * x + 6;
    else
    {
      d += 4 * (x-y) + 10;
      y--;
    }
    x++;
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");

  Bresenham_Circle(getmaxx() / 2, getmaxy() / 2, 150, 4);
  getch();
  closegraph();
}