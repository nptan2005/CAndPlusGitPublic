/* Bai tap 4_57 - Luu man hinh tam thoi vao mot trang trong */
#include <dos.h>
#include <stdlib.h>
#include <mem.h>

unsigned char far *src = MK_FP(0xB800, 0);
unsigned char far *dst = MK_FP(0xB900, 0);

void main()
{
  int i;

  for (i=0; i<4000; i++)
    dst[i] = src[i];
  printf("\nNhan phim bat ky de tiep tuc");
  getch();
  randomize();
  for (i=0; i<4000; i++)
    printf("%c", random(26)+'A');
  printf("\nNhan phim bat ky de tiep tuc");
  getch();
  for (i=0; i<4000; i++)
    src[i] = dst[i];
  getch();
}