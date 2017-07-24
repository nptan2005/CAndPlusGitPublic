/* Bai tap 2_50 - Ve Mat cong ham hai bien */
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
#define UZ 200
#define OX (0.8*M_PI)
#define OY (0.2*M_PI)
#define X(x,y,z) (xc+(x)*UX*cos(OX)+(y)*UY*cos(OY))
#define Y(x,y,z) (yc+(x)*UX*sin(OX)+(y)*UY*sin(OY)-(z)*UZ)

#define A 10
#define B 10
#define C 10

typedef struct {
  double x, y, z;
} Point3D;

Point3D ham(double u, double v)
{
  Point3D p;

  p.x = u;
  p.y = v;
//  p.z = sin(M_PI*(u*u+v*v))/(u*u+v*v);
  p.z = exp(-(u*u+v*v));
  return p;
}

void mat()
{
  double i, j;
  Point3D p;

  for (i=-6.0; i<=6.0; i+=0.2)
  {
    p = ham(i, -6.0);
    moveto(X(p.x, p.y, p.z), Y(p.x, p.y, p.z));
    for (j=-6.0; j<=6.0; j+=0.2)
    {
      p = ham(i, j);
      lineto(X(p.x, p.y, p.z), Y(p.x, p.y, p.z));
    }
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");

  mat();
  getch();
  closegraph();
}