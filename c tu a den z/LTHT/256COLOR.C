/* 256 Color */
#include <stdio.h>
#include <dos.h>

#define VIDEO_INT 0x10

typedef unsigned char BYTE;

BYTE far *video = (BYTE far*)MK_FP(0xA000, 0);

void setmode(int mode)
{
  asm {
    mov ax, mode
    int VIDEO_INT
  }
}

void setpixel(int row, int col, BYTE color)
{
   video[row*320+col] = color;
}

void drawhscreen()
{
  int i, j;

  for (i=0; i<200; i++)
    for (j=0; j<320; j++)
      setpixel(i, j, i);
}

void drawvscreen()
{
  int i, j;

  for (i=0; i<200; i++)
    for (j=0; j<320; j++)
      setpixel(i, j, j);
}

void main()
{
  setmode(0x13);
  drawhscreen();
  getch();
  drawvscreen();
  getch();
  setmode(3);
}