/* Cuon dong chu ngang man hinh */
#include <stdio.h>

void main()
{
  char qcao[81], i=0, len;

  textattr(0x1e);
  printf("\nNhap vao dong quang cao : ");
  gets(qcao);
  len = strlen(qcao);
  while (!kbhit())
  {
    movetext(2, 1, 80, 1, 1, 1);
    gotoxy(80, 1);
    cprintf("%c", qcao[i++]);
    delay(100);
    i %= len;
  }
  getch();
}