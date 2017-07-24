/* Stereo Image */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293

void pars(int a, int b)
{
  line(a, b, a+20, b);
  line(a+20, b, a+20, b+20);
  line(a+20, b+20, a, b+20);
  line(a, b+20, a, b);
  line(a, b, a+20, b);
}

void main()
{
  int gr_drive = DETECT, gr_mode, i;

  initgraph(&gr_drive, &gr_mode, "");
  for (i=-7; i<=7; i++)
  {
    pars(300+30*i, 200);
    line(310 + 30*i, 220, 310+34*i, 250);
    pars(300+34*i, 250);
    line(310+34*i, 270, 310+30*i, 300);
    pars(300+30*i, 300);
  }
  getch();
  closegraph();
}