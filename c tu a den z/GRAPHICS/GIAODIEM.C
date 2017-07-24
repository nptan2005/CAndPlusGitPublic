/* giao diem hai doan thang */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293

void giaodiem(double x1, double y1, double x2, double y2,
              double a1, double b1, double a2, double b2)
{
  double dx, dy, da, db, x, y, t, tich;
  dx = x2 - x1;
  dy = y2 - y1;
  da = a2 - a1;
  db = b2 - b1;
  tich = db * dx - da * dy;
  if (tich != 0)
  {
    t = ((a1 - x1) * dy - (b1 - y1) * dx) / tich;
    if (t>=0.0 && t<=1.0)
    {
      x = t * (a2 - a1) + a1;
      y = t * (b2 - b1) + b1;
      line(x1, y1, x2, y2);
      line(a1, b1, a2, b2);
      setfillstyle(SOLID_FILL, RED);
      fillellipse(x, y, 3, 3);
    }
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  double x1, y1, x2, y2, a1, b1, a2, b2;

  printf("\nNhap vao toa do doan thang thu nhat : ");
  scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
  printf("\nNhap vao toa do doan thang thu hai : ");
  scanf("%lf%lf%lf%lf", &a1, &b1, &a2, &b2);

  initgraph(&gr_drive, &gr_mode, "");
  giaodiem(x1, y1, x2, y2, a1, b1, a2, b2);
  getch();
  closegraph();
}