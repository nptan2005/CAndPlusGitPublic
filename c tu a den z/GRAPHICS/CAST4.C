/* Bai tap 2_59 - Ve duong Bezier bang thuat toan Casteljau cho bon diem */
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include "mouse.inc"
#include <math.h>

#define MAXPOINTS 100
#define SOBUOC    10

struct xycoord {
  double xcoord, ycoord;
} pt[MAXPOINTS];

void cast4(p1, p2, p3, p4, buoc)
struct xycoord p1, p2, p3, p4;
int buoc;
{
  struct xycoord xm1, xm2, xm3, xm12, xm23, xm;

  xm1.xcoord = (p1.xcoord + p2.xcoord)/2;
  xm1.ycoord = (p1.ycoord + p2.ycoord)/2;
  xm2.xcoord = (p2.xcoord + p3.xcoord)/2;
  xm2.ycoord = (p2.ycoord + p3.ycoord)/2;
  xm3.xcoord = (p3.xcoord + p4.xcoord)/2;
  xm3.ycoord = (p3.ycoord + p4.ycoord)/2;
  xm12.xcoord = (xm1.xcoord + xm2.xcoord)/2;
  xm12.ycoord = (xm1.ycoord + xm2.ycoord)/2;
  xm23.xcoord = (xm2.xcoord + xm3.xcoord)/2;
  xm23.ycoord = (xm2.ycoord + xm3.ycoord)/2;
  xm.xcoord = (xm12.xcoord + xm23.xcoord)/2;
  xm.ycoord = (xm12.ycoord + xm23.ycoord)/2;

  putpixel(xm.xcoord, xm.ycoord, GREEN);
  if (buoc > 0)
  {
    cast4(p1, xm1, xm12, xm, buoc-1);
    cast4(xm, xm23, xm3, p4, buoc-1);
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode, n=4, x, y, i;
  unsigned char lbutton = 0, rbutton = 0;
  char s[50];

  initgraph(&gr_drive, &gr_mode, "");
  reset_mouse();
  show_mouse();
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());
  sprintf(s, "Nhap nut trai chuot de chon toa do %d diem", n);
  outtextxy(100, 10, s);
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
  line(pt[0].xcoord, pt[0].ycoord, pt[1].xcoord, pt[1].ycoord);
  line(pt[1].xcoord, pt[1].ycoord, pt[2].xcoord, pt[2].ycoord);
  line(pt[2].xcoord, pt[2].ycoord, pt[3].xcoord, pt[3].ycoord);
  cast4(pt[0], pt[1], pt[2], pt[3], SOBUOC);
  show_mouse();
  getch();
  closegraph();
}