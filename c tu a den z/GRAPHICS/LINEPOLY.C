/* Bai tap 2_55 - Chuong trinh ve phan duong thang nam trong hinh da giac */
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <math.h>
#include "mouse.inc"

#define NPOINTS 8
#define FALSE 0
#define TRUE 1

struct xycoord {
  double xcoord, ycoord;
} a, b, pt[NPOINTS];

double crossproduct(struct xycoord p1, struct xycoord p2)
{
  return p1.xcoord * p2.xcoord + p1.ycoord * p2.ycoord;
}

int testtamgiac(p1, p2, p3, p)
struct xycoord p1, p2, p3, p;
{
  struct xycoord n1, n2, n3;
  double a, b, c, cos1, cos2, cos3;

/* Lay n lam chuan */
  n1.xcoord = p1.xcoord - p.xcoord;
  n1.ycoord = p1.ycoord - p.ycoord;
  n2.xcoord = p2.xcoord - p.xcoord;
  n2.ycoord = p2.ycoord - p.ycoord;
  n3.xcoord = p3.xcoord - p.xcoord ;
  n3.ycoord = p3.ycoord - p.ycoord ;

  a = sqrt(crossproduct(n1, n1));
  b = sqrt(crossproduct(n2, n2));
  c = sqrt(crossproduct(n3, n3));

  n1.xcoord = n1.xcoord / a;
  n1.ycoord = n1.ycoord / a;

  n2.xcoord = n2.xcoord / b;
  n2.ycoord = n2.ycoord / b;

  n3.xcoord = n3.xcoord / c;
  n3.ycoord = n3.ycoord / c;

  cos1 = acos(crossproduct(n1,n2));
  cos2 = acos(crossproduct(n2, n3));
  cos3 = acos(crossproduct(n3, n1));
  if (fabs((cos1+cos2+cos3)-2*M_PI) < 0.0001)
    return 1;
  return 0;
}

void linepoly(int n)
{
  int i;
  double t;
  struct xycoord p;

  do {
    p.xcoord = (b.xcoord - a.xcoord)*t + a.xcoord;
    p.ycoord = (b.ycoord - a.ycoord)*t + a.ycoord;
    for (i=1; i<n-1; i++)
    {
      if (testtamgiac(pt[0], pt[i], pt[i+1], p))
      {
        putpixel(p.xcoord, p.ycoord, GREEN);
        break;
      }
    }
    t += 0.001;
  } while (t<=1.0);
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
  sprintf(s, "Nhap nut trai chuot de chon toa do toi da %d diem de ve mot da gia loi", NPOINTS);
  outtextxy(100, 10, s);
  n = 0;
  do
  {
    do {
      get_mouse_button(&lbutton, &rbutton, &x, &y);
    } while (lbutton == 0 && rbutton == 0);
    if (rbutton != 0)
      break;
    pt[n].xcoord = x;
    pt[n].ycoord = y;
    hide_mouse();
    circle(x, y, 3);
    show_mouse();
    while (lbutton || rbutton)
      get_mouse_button(&lbutton, &rbutton, &x, &y);
    n++;
  } while (n<NPOINTS);
  while (lbutton || rbutton)
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  setcolor(RED);
  hide_mouse();
  moveto(pt[0].xcoord, pt[0].ycoord);
  for (i=1; i<n; i++)
    lineto(pt[i].xcoord, pt[i].ycoord);
  lineto(pt[0].xcoord, pt[0].ycoord);
  setfillstyle(SOLID_FILL, BLACK);
  setcolor(BLACK);
  bar(100, 10, getmaxx()-2, 20);
  setcolor(YELLOW);
  outtextxy(100, 10, "Nhap toa do mot dau duong thang");
  show_mouse();
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  } while (lbutton == 0 && rbutton == 0);
  a.xcoord = x;
  a.ycoord = y;
  while (lbutton || rbutton)
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  hide_mouse();
  circle(a.xcoord, a.ycoord, 3);
  setfillstyle(SOLID_FILL, BLACK);
  setcolor(BLACK);
  bar(100, 10, getmaxx()-2, 20);
  setcolor(YELLOW);
  outtextxy(100, 10, "Nhap toa do dau kia cua duong thang");
  show_mouse();
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  } while (lbutton == 0 && rbutton == 0);
  b.xcoord = x;
  b.ycoord = y;
  while (lbutton || rbutton)
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  hide_mouse();
  circle(b.xcoord, b.ycoord, 3);
  setcolor(BLUE);
  line(a.xcoord, a.ycoord, b.xcoord, b.ycoord);
  linepoly(n);
  show_mouse();

  getch();
  closegraph();
}