/* Star */
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>

#define VIDEO_INT 0x10
#define MAX 100

typedef unsigned char BYTE;
BYTE far *video = (BYTE far*)MK_FP(0xA000, 0);
struct tagstar {
  int status;
  int row, col;
  int tanggiam;
  int color;
} STAR[MAX];

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

void draw(struct tagstar s, BYTE color)
{
  int i, j;
  switch (s.status)
  {
    case 0 : for (i=-3; i<=3; i++)
             {
               setpixel(s.row + i, s.col + i, color);
               setpixel(s.row + i, s.col - i, color);
               setpixel(s.row, s.col + i, color);
               setpixel(s.row + i, s.col, color);
             }
             break;
    case 1 : for (i=-2; i<=2; i++)
             {
               setpixel(s.row + i, s.col + i, color);
               setpixel(s.row + i, s.col - i, color);
               setpixel(s.row, s.col + i, color);
               setpixel(s.row + i, s.col, color);
             }
             break;
    case 2 : for (i=-2; i<=2; i++)
             {
               setpixel(s.row, s.col + i, color);
               setpixel(s.row + i, s.col, color);
             }
             for (i=-1; i<=1; i++)
             {  setpixel(s.row + i, s.col + i, color);
               setpixel(s.row + i, s.col - i, color);
             }
    case 3 : for (i=-2; i<=2; i++)
             {
               setpixel(s.row, s.col + i, color);
               setpixel(s.row + i, s.col, color);
             }
    case 4 : for (i=-1; i<=1; i++)
             {
               setpixel(s.row, s.col + i, color);
               setpixel(s.row + i, s.col, color);
             }
             break;
    case 5 : setpixel(s.row, s.col, color);
             break;
    case 6 : setpixel(s.row, s.col, 8);
             break;
    case 7 : setpixel(s.row, s.col, 7);
             break;
  }
}

void star()
{
  int i;
  do {
    for (i=0; i<MAX; i++)
      draw(STAR[i], STAR[i].color);
    delay(100);
    for (i=0; i<MAX; i++)
    {
      draw(STAR[i], 0);
      if (STAR[i].tanggiam)
      {
        if (STAR[i].status < 7)
          STAR[i].status++;
        else
          STAR[i].tanggiam = 0;
      }
      else
      {
        if (STAR[i].status > 0)
          STAR[i].status--;
        else
          STAR[i].tanggiam = 1;
      }
    }
  } while (!kbhit());
}

void main()
{
  int i;
  randomize();
  for (i=0; i<MAX; i++)
  {
    STAR[i].status = random(8);
    STAR[i].row    = random(200);
    STAR[i].col    = random(320);
    STAR[i].tanggiam = random(2);
    STAR[i].color = random(255)+1;
  }
  setmode(0x13);
  star();
  getch();
  setmode(3);
}