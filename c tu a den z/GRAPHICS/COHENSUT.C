/* Cohen-Sutherland */
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>

#define ROUND(a) ((double)(a+0.5)

#define TRUE  1
#define FALSE 0

#define LEFT_EDGE   0x1
#define RIGHT_EDGE  0x2
#define TOP_EDGE    0x4
#define BOTTOM_EDGE 0x8

#define INSIDE(a) (!a)
#define REJECT(a,b) (a&b)
#define ACCEPT(a,b) (!(a|b))

unsigned char encode(double x, double y, double xmin, double ymin,
                     double xmax, double ymax)
{
  unsigned char code = 0x00;

  if (x < xmin)
    code = code | LEFT_EDGE;
  if (x > xmax)
    code = code | RIGHT_EDGE;
  if (y < ymin)
    code = code | TOP_EDGE;
  if (y > ymax)
    code = code | BOTTOM_EDGE;

  return code;
}

void swap(double *a, double *b)
{
  double tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

void swapcode(unsigned char *a, unsigned char *b)
{
  unsigned char tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

void cohen_sutherland(double x1, double y1, double x2, double y2,
       double xmin, double ymin, double xmax, double ymax)
{
  unsigned char code1, code2;
  int done = FALSE, draw = FALSE;
  double m;

  setcolor(WHITE);
  line(x1, y1, x2, y2);
  while (!done)
  {
    code1 = encode(x1, y1, xmin, ymin, xmax, ymax);
    code2 = encode(x2, y2, xmin, ymin, xmax, ymax);
    if (ACCEPT(code1, code2))
    {
      done = TRUE;
      draw = TRUE;
    }
    else
    {
      if (REJECT(code1, code2))
        done = TRUE;
      else
      {
        if (INSIDE(code1))
        {
          swap(&x1, &x2);
          swap(&y1, &y2);
          swapcode(&code1, &code2);
        }
        if (x2 != x1)
          m = (y2 - y1) / (x2 - x1);
        if (code1 & LEFT_EDGE)
        {
          y1 += (xmin - x1) * m;
          x1 = xmin;
        }
        else
          if (code1 & RIGHT_EDGE)
          {
            y1 += (xmax - x1) * m;
            x1 = xmax;
          }
          else
            if (code1 & BOTTOM_EDGE)
            {
              if (x2 != x1)
                x1 += (ymax - y1) / m;
              y1 = ymax;
            }
            else
              if (code1 & TOP_EDGE)
              {
                if (x2 != x1)
                  x1 += (ymin - y1) / m;
                y1 = ymin;
              }
      }
    }
  }
  setcolor(YELLOW);
  if (draw)
    line(x1, y1, x2, y2);
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  char c;
  double x1, y1, x2, y2;

  initgraph(&gr_drive, &gr_mode, "");
  rectangle(100,50, getmaxx()-100, getmaxy()-50);
  randomize();
  outtextxy(100, getmaxy()-10, "Nhan phim bat ky de sinh duong khac; ESC de thoat");
  do {
    x1 = random(getmaxx() / 2);
    y1 = random(getmaxy());
    x2 = getmaxx()/2 + random(getmaxx() / 2);
    y2 = random(getmaxy());
    cohen_sutherland(x1, y1, x2, y2, 100, 50, getmaxx()-100, getmaxy()-50);
    c = getch();
  } while (c != 27);

  closegraph();
}