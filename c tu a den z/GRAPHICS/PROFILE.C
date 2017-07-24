/* Bai tap 2_41 - Ve Profile */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293
#define RADIUS 100

#define xc (getmaxx()/2)
#define yc (getmaxy()/2 + 150)
#define UX 20
#define UY 20
#define UZ 20
#define OX (0.8*M_PI)
#define OY (0.2*M_PI)
#define X(x,y,z) (xc+(x)*UX*cos(OX)+(y)*UY*cos(OY))
#define Y(x,y,z) (yc+(x)*UX*sin(OX)+(y)*UY*sin(OY)-(z)*UZ)

typedef struct {
  double x, y, z;
} Point3D;

#define MAXPOINTS 9

Point3D profile[MAXPOINTS] = {
  {0, 10, 0}, {5, 10, 0}, {5, 8, 0}, {6, 7, 0}, {6, 6, 0},
  {5,  5, 0}, {5,  2, 0}, {3, 0, 0}, {0, 0, 0}};

void Profile()
{
  double i, j;
  Point3D p, pro[MAXPOINTS];

  for (j=0.0; j<=2*M_PI; j+=0.1)
  {
    for (i=0; i<MAXPOINTS; i++)
    {
      p.x = profile[i].x * cos(j);
      p.y = profile[i].y;
      p.z = profile[i].x * sin(j);
      if (i==0)
        moveto(X(p.x, p.z, p.y), Y(p.x, p.z, p.y));
      else
        lineto(X(p.x, p.z, p.y), Y(p.x, p.z, p.y));
    }
  }
  for (i=0; i<MAXPOINTS; i++)
  for (j=0.0; j<=2*M_PI; j+=0.1)
  {
    p.x = profile[i].x * cos(j);
    p.y = profile[i].y;
    p.z = profile[i].x * sin(j);
    if (j==0)
      moveto(X(p.x, p.z, p.y), Y(p.x, p.z, p.y));
    else
      lineto(X(p.x, p.z, p.y), Y(p.x, p.z, p.y));
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");

  Profile();
  getch();
  closegraph();
}