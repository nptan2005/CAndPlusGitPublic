/* Bai tap 2_3 - Polygon */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293
#define K 200

void polygon(int n)
{
  int goc = 0, i;
  double xc, yc;

  xc = getmaxx() / 2;
  yc = getmaxy() / 2;
  setcolor(YELLOW);
  moveto(xc + K, yc);
  for (i=0; i<n-1; i++)
  {
    goc += 360 / n;
    lineto(xc + K * cos(goc * RADS), yc + K * sin(goc * RADS));
  }
  lineto(xc + K, yc);
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  int n;

  do {
    printf("\nNhap vao so canh da giac : ");
    scanf("%d", &n);
  } while (n<3);
  initgraph(&gr_drive, &gr_mode, "");
  polygon(n);

  getch();
  closegraph();
}