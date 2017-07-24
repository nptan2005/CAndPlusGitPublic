/* Bai tap 2_54 - Chuong trinh xen mot duong thang vao trong hinh chu nhat */
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include "mouse.inc"

#define NPOINTS 2
#define FALSE 0
#define TRUE 1

struct xycoord {
  double xcoord, ycoord;
} min, max, pt[NPOINTS];

#define LEFT_EDGE   0x1
#define RIGHT_EDGE  0x2
#define TOP_EDGE    0x4
#define BOTTOM_EDGE 0x8

#define INSIDE(a) (!a)
#define REJECT(a,b) (a&b)
#define ACCEPT(a,b) (!(a|b))

unsigned char encode(double x, double y)
{
  unsigned char code = 0x00;

  if (x < min.xcoord)
    code = code | LEFT_EDGE;
  if (x > max.xcoord)
    code = code | RIGHT_EDGE;
  if (y < min.ycoord)
    code = code | TOP_EDGE;
  if (y > max.ycoord)
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

void cohen_sutherland(double x1, double y1, double x2, double y2)
{
  unsigned char code1, code2;
  int done = FALSE, draw = FALSE;
  double m;

  while (!done)
  {
    code1 = encode(x1, y1);
    code2 = encode(x2, y2);
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
          y1 += (min.xcoord - x1) * m;
          x1 = min.xcoord;
        }
        else
          if (code1 & RIGHT_EDGE)
          {
            y1 += (max.xcoord - x1) * m;
            x1 = max.xcoord;
          }
          else
            if (code1 & BOTTOM_EDGE)
            {
              if (x2 != x1)
                x1 += (max.ycoord - y1) / m;
              y1 = max.ycoord;
            }
            else
              if (code1 & TOP_EDGE)
              {
                if (x2 != x1)
                  x1 += (min.ycoord - y1) / m;
                y1 = min.ycoord;
              }
      }
    }
  }
  if (draw)
    line(x1, y1, x2, y2);
}

void polyrec(int n)
{
  int i;
  setcolor(YELLOW);
  for (i=0; i<n-1; i++)
    cohen_sutherland(pt[i].xcoord, pt[i].ycoord, pt[i+1].xcoord, pt[i+1].ycoord);
  cohen_sutherland(pt[n-1].xcoord, pt[n-1].ycoord, pt[0].xcoord, pt[0].ycoord);
}

void main()
{
  int gr_drive = DETECT, gr_mode, n, x, y, i;
  unsigned char lbutton = 0, rbutton = 0;
  char s[50];

  initgraph(&gr_drive, &gr_mode, "");
  reset_mouse();
  show_mouse();
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());
  outtextxy(100, 10, "Nhap nut trai chuot de chon toa do goc trai tren hinh chu nhat");
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  } while (lbutton == 0 && rbutton == 0);
  min.xcoord = x;
  min.ycoord = y;
  while (lbutton || rbutton)
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  setfillstyle(SOLID_FILL, BLACK);
  setcolor(BLACK);
  bar(100, 10, getmaxx()-1, 20);
  setcolor(YELLOW);
  outtextxy(100, 10, "Nhap nut trai chuot de chon toa do goc phai duoi hinh chu nhat");
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  } while (lbutton == 0 && rbutton == 0);
  max.xcoord = x;
  max.ycoord = y;
  while (lbutton || rbutton)
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  hide_mouse();
  setcolor(WHITE);
  rectangle(min.xcoord, min.ycoord, max.xcoord, max.ycoord);
  show_mouse();
  setfillstyle(SOLID_FILL, BLACK);
  setcolor(BLACK);
  bar(100, 10, getmaxx()-1, 20);
  setcolor(YELLOW);
  sprintf(s, "Nhap nut trai chuot de chon toa do %d diem de ve", NPOINTS);
  outtextxy(100, 10, s);
  n = 0;
  do
  {
    do {
      get_mouse_button(&lbutton, &rbutton, &x, &y);
    } while (lbutton == 0 && rbutton == 0);
    pt[n].xcoord = x;
    pt[n].ycoord = y;
    hide_mouse();
    circle(x, y, 3);
    show_mouse();
    while (lbutton || rbutton)
      get_mouse_button(&lbutton, &rbutton, &x, &y);
    n++;
  } while (n<NPOINTS);
  setcolor(RED);
  hide_mouse();
  moveto(pt[0].xcoord, pt[0].ycoord);
  for (i=1; i<n; i++)
    lineto(pt[i].xcoord, pt[i].ycoord);
  lineto(pt[0].xcoord, pt[0].ycoord);
  polyrec(n);
  show_mouse();

  getch();
  closegraph();
}