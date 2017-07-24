/* Etipool */
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293
#define XRADIUS 200.0
#define YRADIUS 150.0
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
  double A, B, C, delta;

  A = (cx/XRADIUS)*(cx/XRADIUS) + (cy/YRADIUS)*(cy/YRADIUS);
  B = 2 * ((sx-xc)*cx/(XRADIUS*XRADIUS) + (sy-yc)*cy/(YRADIUS*YRADIUS));
  C = ((sx-xc)/XRADIUS)*((sx-xc)/XRADIUS) + ((sy-yc)/YRADIUS)*((sy-yc)/YRADIUS) - 1.0;

  /* Ta phai giai he phuong trinh Atý+Bt+C = 0 de tim t*/
  delta = B*B - 4*A*C; /* Vi tia luon cat nen delta luon > 0*/
  *thit = (-B + sqrt(delta)) / (2 * A);
}

void run()
{
  double nx, ny, coef;
  t = 0.0;
  do {
    tinh_hit(&thit);
    drawray(&sx, &sy, &cx, &cy, thit);
    delay(100);
    nx = - YRADIUS * YRADIUS * (sx - xc);
    ny = - XRADIUS * XRADIUS * (sy - yc);
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
  randomize();
  sx = 200.0;
  cx = random(20)+20;
  sy = 200.0;
  cy = random(10) + 10;
  ellipse(xc, yc, 0, 360, XRADIUS, YRADIUS);
  setcolor(YELLOW);
  run();
  getch();
  closegraph();
}