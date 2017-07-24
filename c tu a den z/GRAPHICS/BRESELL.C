/* Bai tap 2_49 - Thuat toan Bresenham de ve duong ellipse */
#include <graphics.h>
#include <conio.h>

#define ROUND(a) ((long)(a+0.5))

void plot(int xc, int yc, int x, int y, int color)
{
  putpixel(xc+x, yc+y, color);
  putpixel(xc-x, yc+y, color);
  putpixel(xc+x, yc-y, color);
  putpixel(xc-x, yc-y, color);
}

void Bresenham_Ellipse(int xc, int yc, int xRadius, int yRadius, int color)
{
  long x, y, px, py, rx2, ry2, p;

  x = 0;
  y = yRadius;
  rx2 = xRadius * xRadius;
  ry2 = yRadius * yRadius;
  px = 0;
  py = 2 * rx2 * y;
  plot(xc, yc, x,y, color);
  p = ROUND(ry2-(rx2*yRadius)+(0.25*rx2));
  while (px < py)
  {
    x++;
    px += 2*ry2;
    if (p<0)
      p += ry2 + px;
    else
    {
      y--;
      py -= 2*rx2;
      p+= ry2 + px - py;
    }
    plot(xc, yc, x, y, color);
  }
  p = ROUND(ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2);
  while (y>0)
  {
    y--;
    py -= rx2*2;
    if (p>0)
      p+=rx2-py;
    else
    {
      x++;
      px += ry2*2;
      p += rx2 - py + px;
    }
    plot(xc, yc, x, y, color);
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");

  Bresenham_Ellipse(getmaxx() / 2, getmaxy() / 2, 150, 80, 4);
  getch();
  closegraph();
}