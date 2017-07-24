/* Bai tap 2_45 - Ve Mat cong bac bon */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293
#define RADIUS 100

#define xc (getmaxx()/2)
#define yc (getmaxy()/2)
#define UX 20
#define UY 20
#define UZ 20
#define OX (0.8*M_PI)
#define OY (0.2*M_PI)
#define X(x,y,z) (xc+(x)*UX*cos(OX)+(y)*UY*cos(OY))
#define Y(x,y,z) (yc+(x)*UX*sin(OX)+(y)*UY*sin(OY)-(z)*UZ)

#define A 15
#define B 20
#define C 10
#define N2 1
#define N1 0.2

typedef struct {
  double x, y, z;
} Point3D;

Point3D ham(double u, double v)
{
  Point3D p;
  double cosu, cosv, sinu, sinv;

  if (cos(v) == 0.0)
    cosv = 0;
  else if (cos(v) < 0.0)
    cosv = -pow(fabs(cos(v)), 2/N1);
  else
    cosv = pow(cos(v), 2/N1);

  if (cos(u) == 0.0)
    cosu = 0;
  else if (cos(u) < 0.0)
    cosu = -pow(fabs(cos(u)), 2/N2);
  else
    cosu = pow(cos(u), 2/N2);

  if (sin(u) == 0.0)
    sinu = 0;
  else if (cos(u) < 0.0)
    sinu = -pow(fabs(sin(u)), 2/N2);
  else
    sinu = pow(sin(u), 2/N2);

  if (sin(v) == 0.0)
    sinv = 0;
  else if (cos(u) < 0.0)
    sinv = -pow(fabs(sin(v)), 2/N1);
  else
    sinv = pow(sin(v), 2/N1);

  p.x = A*cosv*cosu;
  p.y = B*cosv*sinu;
  p.z = C*sinv;
  return p;
}

void squad()
{
  double i, j;
  Point3D p;

  for (i=-M_PI; i<=M_PI; i+=0.1)
  {
    p = ham(i, -M_PI/2);
    moveto(X(p.x, p.z, p.y), Y(p.x, p.z, p.y));
    for (j=-M_PI/2; j<=M_PI/2; j+=0.1)
    {
      p = ham(i, j);
      lineto(X(p.x, p.z, p.y), Y(p.x, p.z, p.y));
    }
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");

  squad();
  getch();
  closegraph();
}