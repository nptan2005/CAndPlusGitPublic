/* F Scaling */
#include <conio.h>
#include <graphics.h>
#include <math.h>

#define NUMPOINTS 10
#define xc (getmaxx()/2)
#define yc (getmaxy()/2)

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293

typedef struct tagpoint {
  double x, y;
} POINT;

POINT P[NUMPOINTS] = {{-50,-100}, {40,-100}, {40,-60}, {-20,-60}, {-20,-20},
                      {10,-20}, {10,20}, {-20,20}, {-20,100}, {-50,100}};

void drawF()
{
  int i;

  moveto(xc+P[0].x, yc+P[0].y);
  for (i=1; i<NUMPOINTS; i++)
    lineto(xc+P[i].x, yc+P[i].y);
  lineto(xc+P[0].x, yc+P[0].y);
}

void scaling(double tyle)
{
  int i;
  /* Lay diem 0 lam diem chuan */
  for (i=1; i<NUMPOINTS; i++)
  {
    P[i].x = (P[i].x - P[0].x) * tyle + P[0].x;
    P[i].y = (P[i].y - P[0].y) * tyle + P[0].y;
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  double n=1.0;

  initgraph(&gr_drive, &gr_mode, "");
  drawF();
  outtextxy(0, 0, "Nhan phim bat ky de bat dau shear");
  getch();
  do {
    cleardevice();
    scaling(1.1);
    drawF();
    delay(100);
    n++;
  } while (n<5);
  getch();
  closegraph();
}