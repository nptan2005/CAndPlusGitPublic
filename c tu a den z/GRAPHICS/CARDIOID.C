/* Bai tap 2_7 - Chuong trinh ve duong Cardioid */
#include <conio.h>
#include <graphics.h>
#include <math.h>

#define K 150

void cardioid()
{
   double goc = 0.0;
   double f, xc, yc;

   xc = getmaxx() / 2;
   yc = getmaxy() / 2;
   while (!kbhit())
   {
      f = K * (1 + cos(goc));
      putpixel(xc + f * cos(goc), yc + f * sin(goc), YELLOW);
      goc += 0.01;
   }
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  cardioid();

  getch();
  closegraph();
}