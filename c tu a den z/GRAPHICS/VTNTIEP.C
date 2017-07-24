/* Bai tap 2_72 - Chuong trinh ve vong tron noi tiep */
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <math.h>
#include "mouse.inc"

#define NPOINTS 3

struct xycoord {
  double xcoord, ycoord;
}pt [NPOINTS];

double crossproduct(struct xycoord p1, struct xycoord p2)
{
  return p1.xcoord * p2.xcoord + p1.ycoord * p2.ycoord;
}

void vephangiac(p1, p2, p3, p)
struct xycoord p1, p2, p3, *p;
{
  struct xycoord n1, n2, n3;
  double a, b, c, cos1, cos2, cos3;

  n1.xcoord = p2.xcoord - p1.xcoord;
  n1.ycoord = p2.ycoord - p1.ycoord;
  n2.xcoord = p3.xcoord - p1.xcoord;
  n2.ycoord = p3.ycoord - p1.ycoord;

  a = sqrt(crossproduct(n1, n1)); /* tinh chieu dai canh 1 */
  b = sqrt(crossproduct(n2, n2)); /* tinh chieu dai canh 2 */

  /* Cho hai vector n2 va n1 co chieu dai bang nhau */
  n2.xcoord *= a / b;
  n2.ycoord *= a / b;

  /* Nhu the n1 va n2 tao thanh tam giac can.
     Nghia la duong phan giac cung la duong trung tuyen
  */
  n3.xcoord = (n1.xcoord + n2.xcoord) / 2;
  n3.ycoord = (n1.ycoord + n2.ycoord) / 2;

  setcolor(GREEN);
  line(p1.xcoord, p1.ycoord, p1.xcoord + n3.xcoord,p1.ycoord + n3.ycoord);

  (*p).xcoord = p1.xcoord + n3.xcoord;
  (*p).ycoord = p1.ycoord + n3.ycoord;
}

void giaodiem(p1, p2, p3, p4, p)
struct xycoord p1, p2, p3, p4, *p;
{
  double dx, dy, da, db, x, y, t, tich;
  dx = p2.xcoord - p1.xcoord;
  dy = p2.ycoord - p1.ycoord;
  da = p4.xcoord - p3.xcoord;
  db = p4.ycoord - p3.ycoord;
  tich = db * dx - da * dy;
  if (tich != 0)
  {
    t = ((p3.xcoord - p1.xcoord) * dy - (p3.ycoord - p1.ycoord) * dx) / tich;
    if (t>=0.0 && t<=1.0)
    {
      x = t * (p4.xcoord - p3.xcoord) + p3.xcoord;
      y = t * (p4.ycoord - p3.ycoord) + p3.ycoord;
      setfillstyle(SOLID_FILL, RED);
      fillellipse(x, y, 3, 3);
      (*p).xcoord = x;
      (*p).ycoord = y;
    }
  }
}

double khoangcach(p1, p2, p)
struct xycoord p1, p2, p;
{
  struct xycoord n1, n2, n;
  double c;

  n1.xcoord = p2.xcoord - p1.xcoord;
  n1.ycoord = p2.ycoord - p1.ycoord;
  n2.xcoord = p.xcoord - p1.xcoord;
  n2.ycoord = p.ycoord - p1.ycoord;

  c = crossproduct(n2, n1) / crossproduct(n1,n1);
  n.xcoord = n1.xcoord * c - n2.xcoord;
  n.ycoord = n1.ycoord * c - n2.ycoord;
  return sqrt(crossproduct(n, n));
}

void vtnoitiep()
{
  struct xycoord p1, p2, p;
  double radius;

  vephangiac(pt[0], pt[1], pt[2], &p1);
  vephangiac(pt[1], pt[2], pt[0], &p2);
  vephangiac(pt[2], pt[1], pt[0], &p1);
  /* Tim tam vong tron noi tiep */
  giaodiem(pt[1], p2, pt[2], p1, &p);
  /* Tim ban kinh vong tron noi tiep */
  radius = khoangcach(pt[0], pt[1], p);
  setcolor(WHITE);
  circle(p.xcoord, p.ycoord, radius);
}

void main()
{
  int gr_drive = DETECT, gr_mode, n, x, y;
  unsigned char lbutton = 0, rbutton = 0;
  char s[50];

  initgraph(&gr_drive, &gr_mode, "");
  reset_mouse();
  show_mouse();
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());
  sprintf(s, "Nhap nut trai chuot de chon toa do %d diem de ve", NPOINTS);
  outtextxy(100, 10, s);
  for (n=0; n<NPOINTS; n++)
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
  }
  setcolor(RED);
  hide_mouse();
  moveto(pt[0].xcoord, pt[0].ycoord);
  for (n=1; n<NPOINTS; n++)
    lineto(pt[n].xcoord, pt[n].ycoord);
  lineto(pt[0].xcoord, pt[0].ycoord);
  setcolor(YELLOW);
  vtnoitiep();
  show_mouse();

  getch();
  closegraph();
}