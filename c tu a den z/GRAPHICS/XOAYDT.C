/* Bai tap 2_36 - Xoay duong thang */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293

void xoay(double x1, double y1, double x2, double y2)
{
  double xc, yc;
  double goc1, goc2, r1, r2;

  xc = getmaxx() / 2;
  yc = getmaxy() / 2;
  goc1 = atan2(y1 - yc, x1 - xc);
  goc2 = atan2(y2 - yc, x2 - xc);
  r1 = sqrt((x1-xc)*(x1-xc) + (y1-yc)*(y1-yc));
  r2 = sqrt((x1-xc)*(x1-xc) + (y1-yc)*(y1-yc));
  do {
    setcolor(YELLOW);
    line (x1, y1, x2, y2);
    setcolor(RED);
    line (x1, y1, xc, yc);
    line (x2, y2, xc, yc);
    setcolor(WHITE);
    line(xc - 3, yc, xc + 3, yc);
    line(xc, yc - 3, xc, yc + 3);
    delay(10);
    setcolor(BLACK);
    line (x1, y1, x2, y2);
    line (x1, y1, xc, yc);
    line (x2, y2, xc, yc);
    goc1 += 0.01;
    goc2 += 0.01;
    x1 = xc + r1 * cos(goc1);
    y1 = yc + r1 * sin(goc1);
    x2 = xc + r2 * cos(goc2);
    y2 = yc + r2 * sin(goc2);
  } while (!kbhit());
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  double x1, x2, y1, y2;

  printf("\nNhap toa do cua diem dau doan thang : ");
  scanf("%lf%lf", &x1, &y1);
  printf("\nNhap toa do cua diem cuoi doan thang : ");
  scanf("%lf%lf", &x2, &y2);

  initgraph(&gr_drive, &gr_mode, "");
  xoay(x1, y1, x2, y2);

  getch();
  closegraph();
}