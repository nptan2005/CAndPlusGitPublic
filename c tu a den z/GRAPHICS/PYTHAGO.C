/* Cay Pythagoras */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293

void quadrat( double x, double y, double a, double angle)
{
  double cp, sp;

  setcolor(RED);
  if (a < 35)
    setcolor(2);
  if (a < 8)
    setcolor(7);
  cp = a * cos(angle);
  sp = a * sin(angle);
  line(x, 200 - y, x + cp, 200 - (y+sp));
  line(x, 200 - y, x - cp, 200 - (y+cp));
  line(x+cp, 200 - (y+sp), x - sp + cp, 200 - (y+sp+cp));
  line(x-sp, 200 - (y+cp), x - sp + cp, 200 - (y+sp+cp));
  if (a > 2)
  {
    quadrat(x - sp, y + cp, 3 * a / 5, angle + 0.93);
    quadrat(x - sp + 3 * a / 5 * cos(angle + 0.93),
            y + cp + 3 * a / 5 * sin (angle + 0.93), a * 4 / 5,
            angle - 0.64);
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  setcolor(7);
  quadrat(250, -120, 70, 0);
  getch();
  closegraph();
}