/* Prime Rosette */
#include <conio.h>
#include <graphics.h>
#include <math.h>

#define MAX 15
#define RADIUS (getmaxy()/2-10)
#define xc (getmaxx()/2)
#define yc (getmaxy()/2)

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293

typedef struct tagpoint{
  double x, y;
} POINT;

void prosette(int n)
{
  int i, j;
  POINT p[MAX];
  double angle = 0.0;

  for (i=0; i<n; i++)
  {
    p[i].x = RADIUS * sin(angle);
    p[i].y = RADIUS * cos(angle);
    angle += RADS*360/n;
  }
/*
  setcolor(WHITE);
  moveto(xc+p[0].x, yc-p[0].y);
  for (i=1; i<n; i++)
   lineto(xc+p[i].x, yc-p[i].y);
  lineto(xc+p[0].x, yc-p[0].y);
*/
  setcolor(YELLOW);
  for (i=0; i<n-1; i++)
   for (j=i+1; j<n; j++)
     if (j-i>1 && ((i!=0) || (j!=n-1)))
       line(xc+p[i].x, yc-p[i].y, xc+p[j].x, yc-p[j].y);
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  int n;

  printf("\nCho biet so canh (5..%d): ", MAX);
  do {
    scanf("%d", &n);
  } while (n < 5 || n > MAX);

  initgraph(&gr_drive, &gr_mode, "");
  prosette(n);
  getch();
  closegraph();
}