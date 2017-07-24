/* Bai tap 1_99 - Minh hoa phep nhan tay */
#include <stdio.h>

void nhantay(unsigned long sobn, unsigned long son)
{
  unsigned long k, n;
  int i=0;
  char s[20];
  printf("\n%20ld\n", sobn);
  ltoa(son, s, 10);
  for (i=0; i<18-strlen(s); i++)
    printf(" ");
  printf("X %s", s);
  printf("\n         ------------");
  n = son;
  i = 0;
  while (n>0)
  {
    k = n%10;
    n /= 10;
    k *= sobn;
    ltoa(k, s, 10);
    printf("\n");
    gotoxy(21 - strlen(s) - i, wherey());
    cprintf("%s", s);
    i++;
  }
  ltoa(sobn*son, s, 10);
  printf("\n         ------------\n");
  gotoxy(21 - strlen(s), wherey());
  cprintf("%s", s);
}

void main()
{
  unsigned long sobinhan, sonhan;

  printf("\Nhap so bi nhan : ");
  scanf("%ld", &sobinhan);
  printf("\Nhap so nhan : ");
  scanf("%ld", &sonhan);
  nhantay(sobinhan, sonhan);
  getch();
}