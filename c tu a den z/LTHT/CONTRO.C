/* Minh hoa doi kich thuoc con tro */
#include <stdio.h>
#include <conio.h>
#include <dos.h>

#define VIDEOINT 0x10
typedef unsigned char BYTE;

char far *video = MK_FP(0xB800, 0);


void getcursor(BYTE *start, BYTE *end, BYTE *row, BYTE *col)
{
  asm {
    mov ah, 3
    mov bh, 0
    int VIDEOINT
  }
  *start = _CH;
  *end   = _CL;
  *row   = _DH;
  *col   = _DL;
}

void setcursor(BYTE start, BYTE end, BYTE row, BYTE col)
{
  asm {
    mov ah, 1
    mov bh, 0
    mov ch, start
    mov cl, end
    mov dh, row
    mov dl, col
    int VIDEOINT
  }
}

void main()
{
  BYTE start, end, chieu = 1, row, col;

  getcursor(&start, &end, &row, &col);
  do {
    setcursor(start, end, row, col);
    if (chieu)
    {
      if (start)
        start--;
      else
      {
        end--;
        if (end == 0)
          chieu = 0;
      }
    }
    else
    {
      if (end < 15)
        end++;
      else
      {
        start++;
        if (start == 15)
          chieu = 1;
      }
    }
    delay(100);
  } while (!kbhit());
}