/* Ray circle */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293
#define RADIUS 200.0
#define DOT(a,b) ((a)*(b) + (a)*(b))
#define DOT2(ax,ay,bx,by) ((ax)*(bx) + (ay)*(by))

double sx, sy, cx, cy, xc, yc, t, thit;

void drawray(double *sx, double *sy, double *cx, double *cy, double t)
{
  moveto(*sx, *sy);
  *sx = *sx + *cx * t;
  *sy = *sy + *cy * t;
  lineto(*sx, *sy);
}

void tinh_hit(double *thit)
{
  double AA, wx, wy, BB, CC, discrim;

  AA = cx * cx + cy * cy;
  wx = sx - xc;
  wy = sy - yc;
  BB = wx * cx + wy * cy;
  CC = wx * wx + wy * wy - RADIUS * RADIUS;
  if (AA != 0.0)
  {
    discrim = BB * BB - AA * CC;
    if (discrim < 0.0)
      *thit = -1.0;
    else
      *thit = (-BB - sqrt(discrim)) / AA;
  }
}

void run()
{
  double nx, ny, coef;
  t = 0.0;
  do {
    tinh_hit(&thit);
    drawray(&sx, &sy, &cx, &cy, thit);
    delay(100);
    nx = sx - xc;
    ny = sy - yc;
    coef = 2.0 * (cx*nx + cy*ny) / (nx*nx + ny*ny);
    cx = cx - coef * nx;
    cy = cy - coef * ny;
  } while (!kbhit());
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  xc = getmaxx() / 2;
  yc = getmaxy() / 2;
  sx = 200.0;
  cx = 10.0;
  sy = 200.0;
  cy = 40.0;
  circle(xc, yc, RADIUS);
  run();
  getch();
  closegraph();
}