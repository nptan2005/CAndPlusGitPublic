/* Bai tap 2_37 - Ve duong phan giac giua hai doan thang */
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include "mouse.inc"
#include <math.h>

#define MAXPOINTS 100

struct xycoord {
  double xcoord, ycoord;
} pt[MAXPOINTS], p;

double dotproduct(struct xycoord p1, struct xycoord p2)
{
  return p1.xcoord * p2.xcoord + p1.ycoord * p2.ycoord;
}

void vephangiac()
{
  struct xycoord n1, n2, n3;
  double a, b, c, cos1, cos2, cos3;

  n1.xcoord = pt[1].xcoord - pt[0].xcoord;
  n1.ycoord = pt[1].ycoord - pt[0].ycoord;
  n2.xcoord = pt[2].xcoord - pt[0].xcoord;
  n2.ycoord = pt[2].ycoord - pt[0].ycoord;

  a = sqrt(dotproduct(n1, n1)); /* tinh chieu dai canh 1 */
  b = sqrt(dotproduct(n2, n2)); /* tinh chieu dai canh 2 */

  /* Cho hai vector n3 va n1 co chieu dai bang nhau */
  n3.xcoord = n2.xcoord * a / b;
  n3.ycoord = n2.ycoord * a / b;

  /* Nhu the n1 va2 n3 tao thanh tam giac can.
     Nghia la duong phan giac cung la duong trung tuyen
  */
  n3.xcoord = (n1.xcoord + n3.xcoord) / 2;
  n3.ycoord = (n1.ycoord + n3.ycoord) / 2;

  setcolor(GREEN);
  line(pt[0].xcoord, pt[0].ycoord, pt[0].xcoord + n3.xcoord,pt[0].ycoord + n3.ycoord);
}

void main()
{
  int gr_drive = DETECT, gr_mode, n=3, x, y, i;
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
  line(pt[0].xcoord, pt[0].ycoord, pt[2].xcoord, pt[2].ycoord);
  vephangiac();
  show_mouse();
  getch();
  closegraph();
}