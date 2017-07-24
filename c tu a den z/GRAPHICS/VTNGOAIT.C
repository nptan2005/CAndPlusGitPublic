/* Bai tap 2_73 - Chuong trinh ve vong tron ngoai tiep */
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

void vetrungtruc(p1, p2, p, m)
struct xycoord p1, p2, *p, *m;
{
  (*m).xcoord = (p2.xcoord + p1.xcoord)/2;
  (*m).ycoord = (p2.ycoord + p1.ycoord)/2;
  (*p).xcoord = ((*m).xcoord + p2.ycoord - p1.ycoord);
  (*p).ycoord = ((*m).ycoord + p1.xcoord - p2.xcoord);

  setcolor(GREEN);
  line((*m).xcoord, (*m).ycoord,(*p).xcoord, (*p).ycoord);
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

void vtngoaitiep()
{
  struct xycoord p1, p2, p3, p4, p;
  double radius;

  vetrungtruc(pt[0], pt[1], &p1, &p2);
  vetrungtruc(pt[1], pt[2], &p3, &p4);
  vetrungtruc(pt[2], pt[0], &p1, &p2);
  /* Tim tam vong tron ngoai tiep */
  giaodiem(p1, p2, p3, p4, &p);
  /* Tim ban kinh vong tron ngoai tiep */
  p1.xcoord = p.xcoord - pt[0].xcoord;
  p1.ycoord = p.ycoord - pt[0].ycoord;
  radius = sqrt(crossproduct(p1, p1));
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
  vtngoaitiep();
  show_mouse();

  getch();
  closegraph();
}