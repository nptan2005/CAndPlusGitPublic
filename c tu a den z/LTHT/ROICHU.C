/* Chuong trinh lam roi chu mot cach ngau nhien */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

char far *video;

void main()
{
  unsigned x, y, offset;
  char c;

  video = (char far *)MK_FP(0xB800, 0);
  randomize();
  do {
    x = random(80);
    y = random(25);
    offset = (y*80 + x) * 2;
    if (video[offset] != 32)
    {
       c = video[offset];
       while (video[offset + 160] == 32 && y<24)
       {
         video[offset] = 32;
         y++ ;
         offset = (y*80 + x) * 2;
         video[offset] = c;
         delay(50);
       }
    }
  } while (!kbhit());
}