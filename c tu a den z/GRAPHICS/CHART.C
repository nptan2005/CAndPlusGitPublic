/* Bai tap 2_18 - Chart */
#include <graphics.h>
#include <stdlib.h>

void main()
{
  int gr_drive = DETECT, gr_mode;
  int a[10], i, width;

  initgraph(&gr_drive, &gr_mode, "");
  randomize();
  for (i=0; i<10; i++)
    a[i] = random(300) + 10;
  width = (getmaxx() / 31) * 2;
  line(2, 0, 2, 402);
  line(2, 402, getmaxx(), 402);
  moveto(getmaxx()-12, 404);
  lineto(getmaxx(), 402);
  lineto(getmaxx()-12, 400);
  moveto(0, 12);
  lineto(2, 0);
  lineto(4, 12);
  outtextxy(getmaxx() - 24, 403, "x");
  outtextxy(8, 5, "y");
  outtextxy(2, 404, "0");
  for (i=0; i<10; i++)
  {
    bar3d(width / 2 + i * 3 * width / 2, 400,
          3 * width / 2 + i * 3 * width / 2, 400 - a[i], 3, 1);
  }
  getch();
  closegraph();
}