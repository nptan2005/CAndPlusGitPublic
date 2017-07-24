/* Bai tap 4_7 - PC Configuration */
#include <conio.h>
#include <dos.h>
#include <io.h>

void printconfig()
{
  union REGS regs;

  clrscr();
  if (peekb(0xFFFF, 0xE) == (char)0xFC)
    printf("\nKieu may     : AT");
  int86(0x12, &regs, &regs);
  printf("\nMemory       : %d KB", regs.x.ax);
  regs.h.ah = 0x88;
  int86(0x15, &regs, &regs);
  printf("\nExtended     : %d KB", regs.x.ax);
  int86(0x11, &regs, &regs);
  printf("\nVideo mode   : " );
  switch(regs.x.ax & '0')
  {
    case 0 : printf("Khong dinh nghia"); break;
    case 16 : printf("40 x 25 color"); break;
    case 32 : printf("80 x 25 color"); break;
    case 48 : printf("80 x 25 mno"); break;
  }
  printf("\nDisk drives  : %d", (regs.x.ax >> 6 & 3) + 1);
  printf("\nRS232 Card   : %d", regs.x.ax >> 9 & 3);
  printf("\nPrinter Card : %d", regs.x.ax >> 14);
}

void main()
{
  printconfig();
  getch();
}