/* Bai tap 2_4 - Chuong trinh ve duong Rosettes */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293
/* So luong canh toi da */
#define MAX 20

typedef struct POINT {
  double x, y;
} POINT ;

void Rosettes(int n)
{
  int i, j, centerx, centery, angle;
  POINT P[MAX];

  centerx = getmaxx() / 2;
  centery = getmaxy() / 2;
  angle   = 360 / n;

  for (i=0; i<n; i++)
  {
    P[i].x = centerx + cos((i * angle - 90.0) * RADS ) * (centery - 10);
    P[i].y = centery + sin((i * angle - 90.0) * RADS ) * (centery - 10);
  }

  for (i=0; i<n-1; i++)
    for (j=1; j<n; j++)
      line(P[i].x, P[i].y, P[j].x, P[j].y);

}

void main()
{
  int gr_drive = DETECT, gr_mode, i;

  initgraph(&gr_drive, &gr_mode, "");
  setcolor(YELLOW);

  for (i=5; i<=MAX; i++)
  {
    cleardevice();
    rectangle(0, 0, getmaxx(), getmaxy());
    Rosettes(i);
    getch();
  }
  closegraph();
}