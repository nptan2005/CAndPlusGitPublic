/* Bai tap 2_38 - Kiem tra xem mot diem nam trong hay ngoai mot da giac loi */
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include "mouse.inc"
#include <math.h>

#define MAXPOINTS 100

struct xycoord {
  double xcoord, ycoord;
} pt[MAXPOINTS], p;

double crossproduct(struct xycoord p1, struct xycoord p2)
{
  return p1.xcoord * p2.xcoord + p1.ycoord * p2.ycoord;
}

int testtamgiac(p1, p2, p3)
struct xycoord p1, p2, p3;
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

int testpoly(int n)
{
  int i;
  for (i=1; i<n-1; i++)
  {
    if (testtamgiac(pt[0], pt[i], pt[i+1]))
      return 1;
  }
  return 0;
}

void main()
{
  int gr_drive = DETECT, gr_mode, n, x, y, i;
  unsigned char lbutton = 0, rbutton = 0;
  char s[50];

  printf("\nCho biet so dinh da giac : ");
  do {
    scanf("%d", &n);
  } while (n<3 || n>MAXPOINTS);
  initgraph(&gr_drive, &gr_mode, "");
  reset_mouse();
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());
  sprintf(s, "Nhap nut trai chuot de chon toa do %d diem de ve da giac loi", n);
  outtextxy(100, 10, s);
  show_mouse();
  for (i=0; i<n; i++)
  {
    do {
      get_mouse_button(&lbutton, &rbutton, &x, &y);
    } while (lbutton == 0 && rbutton == 0);
    pt[i].xcoord = x;
    pt[i].ycoord = y;
    hide_mouse();
    circle(x, y, 3);
    show_mouse();
    while (lbutton || rbutton)
      get_mouse_button(&lbutton, &rbutton, &x, &y);
  }
  setcolor(RED);
  hide_mouse();
  moveto(pt[0].xcoord, pt[0].ycoord);
  for (i=1; i<n; i++)
    lineto(pt[i].xcoord, pt[i].ycoord);
  lineto(pt[0].xcoord, pt[0].ycoord);
  show_mouse();
  setcolor(GREEN);
  outtextxy(100, 20, "Nhap nut trai chuot de chon toa do diem can xet");
  do {
    do {
      get_mouse_button(&lbutton, &rbutton, &x, &y);
    } while (lbutton == 0 && rbutton == 0 && !kbhit());
    p.xcoord = x;
    p.ycoord = y;
    hide_mouse();
    circle(x, y, 3);
    setfillstyle(SOLID_FILL, 0);
    setcolor(BLACK);
    bar(100,40, getmaxx()-3, 50);
    setcolor(YELLOW);
    if (testpoly(n))
      outtextxy(100, 40, "Diem chon nam trong da giac");
    else
      outtextxy(100, 40, "Diem chon nam ngoai da giac");
    show_mouse();
  } while (!kbhit());
  closegraph();
}