/* Bai tap 2_6 - Chuong trinh ve duong Superellipse */
#include <conio.h>
#include <graphics.h>
#include <math.h>

double _X(double a, double t, double n)
{
  if (cos(t) != 0.0)
    if (cos(t) > 0.0)
      return a * pow(cos(t), 2 / n);
    else
      return - a * pow(fabs(cos(t)), 2 / n);
  else
    return 0.0;
}

double _Y(double b, double t, double n)
{
  if (sin(t) != 0.0)
    if (sin(t) > 0.0)
      return b * pow(sin(t), 2 / n);
    else
      return - b * pow(fabs(sin(t)), 2 / n);
  else
    return 0.0;
}

void superellipse(double a, double b, double n)
{
   double t = - M_PI ;
   double f, xc, yc, x, y;

   xc = getmaxx() / 2;
   yc = getmaxy() / 2;
   while (!kbhit() && t<M_PI )
   {
      x = _X(a, t, n);
      y = _Y(b, t, n);
      putpixel(xc + x, yc + y, YELLOW);
      t += 0.001;
   }
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  double a, b, n;

  printf("\nCho biet ban kinh a : ");
  scanf("%lf", &a);
  printf("\nCho biet ban kinh b : ");
  scanf("%lf", &b);
  printf("\nCho biet bac n : ");
  scanf("%lf", &n);
  initgraph(&gr_drive, &gr_mode, "");
  superellipse(a, b, n);

  getch();
  closegraph();
}