/* Bai tap 2_14 - Minh hoa chuyen dong cua mot banh xe lan */
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <math.h>

#pragma warn -pro

float t = 0.0;
float x, y;

void vebanhxe()
{
  int x1, y1, x2, y2;
  circle(x, y, 20);

  x1 = x - 20 * cos(t);
  y1 = y - 20 * sin(t);
  x2 = x + 20 * cos(t);
  y2 = y + 20 * sin(t);
  line(x1, y1, x2, y2);

}

void main()
{
  int gd = DETECT, gm ;

  initgraph(&gd, &gm, "");

  line(0, 321, getmaxx(), 321);
  x = 100;
  y = 300;

  while (!kbhit())
  {
    setcolor(YELLOW);
    vebanhxe();
    delay(10);
    setcolor(BLACK);
    vebanhxe();
    t += 0.05;
    x += 1 ;
    if (x > getmaxx() + 20)
      x = 0; 
  }
  getch();
  closegraph();
}