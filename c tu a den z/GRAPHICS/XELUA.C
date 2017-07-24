/* Ve banh xe lua */
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293
#define RADIUS 21

void banhxelua()
{
  double angle = 45, xc = 100, yc, xl, yl;
  yc = 448 - RADIUS;
  while (!kbhit())
  {
     setcolor(YELLOW);
     xl = RADIUS * cos(angle * RADS);
     yl = RADIUS * sin(angle * RADS);
     circle(xc, yc, RADIUS);
     circle(xc + 100, yc, RADIUS);
     setcolor(RED);
     line(xc + xl, yc + yl, xc + xl + 100, yc + yl);
     line(xc - xl, yc - yl, xc - xl + 100, yc - yl);
     delay(10);
     setcolor(BLACK);
     circle(xc, yc, RADIUS);
     circle(xc + 100, yc, RADIUS);
     line(xc + xl, yc + yl, xc + xl + 100, yc + yl);
     line(xc - xl, yc - yl, xc - xl + 100, yc - yl);
     angle += 1;
     xc += 2 * M_PI * RADIUS / 360;
     if (xc-RADIUS >getmaxx())
      xc = - RADIUS - 100;
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  line(0, 450, getmaxx(), 450);
  line(0, 451, getmaxx(), 451);
  banhxelua();
  getch();
  closegraph();
}