/* Bai tap 2_43 - Ve Mat Yen ngua */
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

typedef struct {
  double x, y, z;
} Point3D;

Point3D ham(double u, double v)
{
  Point3D p;

  p.x = A*v*tan(u);
  p.y = B*v*1/tan(u);
  p.z = v*v;
  return p;
}

void mat()
{
  double i, j;
  Point3D p;

  for (i=-10; i<=10; i+=0.1)
  {
    p = ham(i, -10);
    moveto(X(p.x, p.y, p.z), Y(p.x, p.y, p.z));
    for (j=-10; j<=10; j+=0.1)
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