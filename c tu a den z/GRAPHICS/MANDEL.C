/* Mandelbrot */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293

int huge detectVGA(void);

void main()
{
  int gr_drive, gr_mode, k, l, n, color;
  double xl = -2.0, xr = 0.6, yu = -1.2, yo = 1.2, dx, dy;
  double re, im, x, y, xalt, yalt, xm, ym;

  gr_drive = installuserdriver("svga256", detectVGA);
  gr_mode  = 2; /* 640 x 480 - 256 color */
  initgraph(&gr_drive, &gr_mode, "");

  dx = (xr - xl) / getmaxx();
  dy = (yo - yu) / getmaxy();

  for (k=0; k<640; k++)
  {
    re = xl + k * dx;
    for (l=0; l<getmaxy(); l++)
    {
      im = yu + l * dy;
      x = 0; y = 0; n = 0;
      do {
        xalt = x;
        yalt = y;
        xm = xalt * xalt;
        ym = yalt * yalt;
        x = xm - ym + re;
        y = 2 * xalt * yalt + im;
        n++;
      } while (n<=120 && x*x + y*y <= 100);
      putpixel(k, l, n);
    }
  }

  getch();
  closegraph();
}

int huge detectVGA(void)
{
   int driver, mode, sugmode = 0;

   detectgraph(&driver, &mode);
   if (driver == VGA)
      return sugmode;
   else
      return grError;
}
