/* Bai tap 5_1 - In bang cuu chuong */
#include <stdio.h>
#include <conio.h>
#include <string.h>

void main()
{
  int i, j;
  char chuoi[] = "B A N G   C U U   C H U O N G";
  char ten[10][5] = {"","","Hai", "Ba", "Bon", "Nam",
                     "Sau", "Bay", "Tam", "Chin"};
  clrscr();
  textcolor(YELLOW);
  gotoxy((80 - strlen(chuoi)) / 2, 1);
  cprintf("%s\n\n", chuoi);

  for (i=2; i<=9; i++)
  {
    gotoxy(10*(i-2) + (10 - strlen(ten[i]))/2, 4);
    textcolor(i);
    cprintf("%s", ten[i]);
  }
  for (j=1; j<=10; j++)
    for (i=2; i<=9; i++)
    {
      gotoxy(10*(i-2) + 1, j+4);
      textcolor(i);
      cprintf("%dx%2d = %2d", i, j, i*j);
    }
  getch();
}