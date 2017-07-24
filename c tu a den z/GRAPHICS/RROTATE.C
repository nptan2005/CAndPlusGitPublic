/* Rectangle rotate */
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
#include <dos.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293

void rectangle_rotate(int xc, int yc, int width, int height)
{
  float x1, y1, x2, y2, x3, y3, x4, y4, angle;
  float oldx1, oldy1, oldx2, oldy2, oldx3, oldy3, oldx4, oldy4;

  x2 = x3 = xc + (float)width / 2;
  x1 = x4 = xc - (float)width / 2;
  y1 = y2 = yc - (float)height / 2;
  y3 = y4 = yc + (float)height / 2;
  angle = 3 * RADS;
  do {
    setcolor(random(15) + 1);
    moveto(x1, y1);
    lineto(x2, y2);
    lineto(x3, y3);
    lineto(x4, y4);
    lineto(x1, y1);
    delay(100);
    setcolor(BLACK);
    moveto(x1, y1);
    lineto(x2, y2);
    lineto(x3, y3);
    lineto(x4, y4);
    lineto(x1, y1);
    oldx1 = x1;
    oldy1 = y1;
    x1 = ((oldx1 - xc) * cos(angle)) + ((oldy1 - yc) * sin(angle)) + xc;
    y1 = ((oldy1 - yc) * cos(angle)) - ((oldx1 - xc) * sin(angle)) + yc;
    oldx2 = x2;
    oldy2 = y2;
    x2 = ((oldx2 - xc) * cos(angle)) + ((oldy2 - yc) * sin(angle)) + xc;
    y2 = ((oldy2 - yc) * cos(angle)) - ((oldx2 - xc) * sin(angle)) + yc;
    oldx3 = x3;
    oldy3 = y3;
    x3 = ((oldx3 - xc) * cos(angle)) + ((oldy3 - yc) * sin(angle)) + xc;
    y3 = ((oldy3 - yc) * cos(angle)) - ((oldx3 - xc) * sin(angle)) + yc;
    oldx4 = x4;
    oldy4 = y4;
    x4 = ((oldx4 - xc) * cos(angle)) + ((oldy4 - yc) * sin(angle)) + xc;
    y4 = ((oldy4 - yc) * cos(angle)) - ((oldx4 - xc) * sin(angle)) + yc;
  } while (!kbhit());

}

void main()
{
  int gr_drive = DETECT, gr_mode;
  int xc, yc, width, height;

  initgraph(&gr_drive, &gr_mode, "");
  randomize();
  xc = getmaxx() / 2;
  yc = getmaxy() / 2;
  width = random(100) + 200;
  height = random(100) + 100;
  printf("Width  = %d", width);
  printf("\nHeight = %d", height);
  rectangle_rotate(xc, yc, width, height);

  getch();
  closegraph();
}