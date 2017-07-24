/* Pinball trong text mode */
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>

char far *video = MK_FP(0xB800, 0);

void writechar(int x, int y, char c)
{
  video[y*160+x*2] = c;
}

void main()
{
  int xball, yball, dx, dy;

  textattr(0x1E);
  clrscr();
  randomize();
  xball = random(80);
  yball = random(25);
  do {
    dx = random(3) - 1;
  } while (dx == 0);
  do {
    dy = random(3) - 1;
  } while (dy == 0);
  do {
    writechar(xball, yball, 4);
    delay(100);
    writechar(xball, yball, 32);
    xball += dx;
    yball += dy;
    if (xball <= 0 || xball >=79)
      dx = -dx;
    if (yball <= 0 || yball >=24)
      dy = -dy;
  } while (!kbhit());
}