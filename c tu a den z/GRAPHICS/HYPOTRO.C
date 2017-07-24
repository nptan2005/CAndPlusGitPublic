/* Bai tap 2_11 - Chuong trinh ve duong Hypotrochoid */
#include <conio.h>
#include <graphics.h>
#include <math.h>

double _X(double a, double b, double k, double t)
{
  return (a - b) * cos(2 * M_PI * t) -
         k * cos(2 * M_PI * (a-b) * t / b);
}

double _Y(double a, double b, double k, double t)
{
  return (a - b) * sin(2 * M_PI * t) -
         k * sin(2 * M_PI * (a-b) * t / b);
}

void epitro(double a, double b, double k)
{
   double t = 0.0;
   double f, xc, yc, x, y;

   xc = getmaxx() / 2;
   yc = getmaxy() / 2;
   while (!kbhit())
   {
      x = _X(a, b, k, t);
      y = _Y(a, b, k, t);
      putpixel(xc + x, yc + y, YELLOW);
      t += 0.001;
   }
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  double a, b, k;

  printf("\nCho biet ban kinh a : ");
  scanf("%lf", &a);
  printf("\nCho biet ban kinh b : ");
  scanf("%lf", &b);
  printf("\nCho biet ban kinh k : ");
  scanf("%lf", &k);
  initgraph(&gr_drive, &gr_mode, "");
  epitro(a, b, k);

  getch();
  closegraph();
}