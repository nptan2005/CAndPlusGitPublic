/* Sphinx */
#include <graphics.h>
#include <conio.h>
#include <math.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293
double curangle = 0.0;
double curx, cury;

void lineforward(double angle, double length)
{
  curangle += angle;
  curx += length*cos(curangle*RADS);
  cury += length*sin(curangle*RADS);
  lineto(curx, cury);
}

void moveforward(double angle, double length)
{
  curangle += angle;
  curx += length*cos(curangle*RADS);
  cury += length*sin(curangle*RADS);
  moveto(curx, cury);
}

void Sphinx(double angle, double length, int level, int leftright)
{
  double len4, len2, len1, oldx, oldy, oldangle;
  if (leftright)
  {
    if (level == 0)
    {
      len1 = length / 3;
      lineforward(angle, length);
      lineforward(-120,len1*2);
      lineforward(-120,len1);
      lineforward(+60,len1);
      lineforward(-60,len1);
    }
    else
    {
      Sphinx(angle, length, 0, leftright);
      len4 = length / 4;
      Sphinx(240, len4, 0, 1);
      moveforward(240, len4);
      Sphinx(0, len4, 0, 1);
      moveforward(240, len4);
      Sphinx(0, len4, 0, 1);
      moveforward(240, len4);
      Sphinx(0, len4, 0, 1);
      moveforward(240, len4);
      moveforward(-120, len4*2/3);
      Sphinx(0, len4, 0, 0);
      moveforward(240, len4);
      Sphinx(0, len4, 0, 0);
      moveforward(-180, len4*2/3);
      Sphinx(-120, len4, 0, 0);
      moveforward(240, len4/3);
      Sphinx(-240, len4, 0, 1);
      moveforward(240, len4);
      Sphinx(0, len4, 0, 1);
      moveforward(240, len4);
      Sphinx(-60, len4, 0, 0);
      moveforward(-180, len4*2/3);
      lineforward(-60, len4);
      moveforward(60, len4/3);
      moveforward(-120, len4);
      Sphinx(-180, len4, 0, 0);
    }
  }
  else
  {
    if (level == 0)
    {
      len1 = length / 3;
      lineforward(angle, length);
      lineforward(-120,len1);
      lineforward(-60,len1);
      lineforward(60,len1);
      lineforward(-120,len1*2);
    }
    else
    {
      Sphinx(angle, length, 0, leftright);
      len4 = length / 4;
    }
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  double angle, xc, yc;

  initgraph(&gr_drive, &gr_mode, "");
  xc = getmaxx() / 2;
  yc = getmaxy() / 2;
  for (angle=0; angle<360; angle = angle + 60)
  {
    curangle = 0;
    moveto(xc, yc);
    curx = xc;
    cury = yc;
//    setcolor(angle/60+1);
    Sphinx(angle, 240, 1, 1);
  }
  getch();
  closegraph();
}