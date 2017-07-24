/* Bai tap 4_3 - Hien thong tin ve BIOS */
#include <dos.h>
#include <mem.h>

unsigned char far *rom = MK_FP(0xFFFF, 0);

void main()
{
  char date[9], c[256];
  int i, len;

  for (i=0; i<8; i++)
    date[i] = rom[5+i];
  date[8] = 0;
  printf("\n\n\nThong tin ve BIOS");
  printf("\nNgay san xuat : %s", date);
  if (rom[14] == 0xFC)
    printf("\nKieu may      : AT");
  rom = MK_FP(0xF000, 0xE060);
  len = rom[0];
  for (i=0; i<len; i++)
    c[i] = rom[i+1];
  printf("\nManufacturer  : %s", c);
  getch();
}
