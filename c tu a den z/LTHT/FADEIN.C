/* Fadein */
#include <stdio.h>
#include <dos.h>

void main()
{
  unsigned char palettes[768];
  unsigned char dump[768];
  int i, j;

  outportb(0x3C7, 0);
  for (i=0; i<768; i++)
  {
    palettes[i] = inportb(0x3C9);
    dump[i] = palettes[i];
  }
  printf("\nNhan mot phim bat ky de bat dau FADE");
  getch();
  for (j=0; j<256; j++)
  {
    for (i=0; i<768; i++)
      if (dump[i] > 0)
        dump[i]--;
    outportb(0x3C8, 0);
    for (i=0; i<768; i++)
      outportb(0x3C9, dump[i]);
    delay(10);
  }
  outportb(0x3C8, 0);
  for (i=0; i<768; i++)
    outportb(0x3C9, palettes[i]);
  printf("\nNhan phim bat ky de ket thuc");
  getch();
}