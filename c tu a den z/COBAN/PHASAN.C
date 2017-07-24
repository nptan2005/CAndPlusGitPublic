/* Bai tap 1_102 - Tro choi pha san */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int player[2], luot = 0, y;

void giam0()
{
  player[0]--;
  gotoxy(player[0]%5*2+1, y + player[0]/5);
  cprintf(" ");
  gotoxy(player[1] % 5*2 + 25, y + player[1]/5);
  cprintf("*");
  player[1]++;
}

void giam1()
{
  player[1]--;
  gotoxy(player[1]%5*2+25, y + player[1]/5);
  cprintf(" ");
  gotoxy(player[0] % 5*2 + 1, y + player[0]/5);
  cprintf("*");
  player[0]++;
}

void main()
{
  int i, n, k, dong, tudong = 0;
  char c;

  randomize();
  player[0] = player[1] = 20;

  clrscr();
  printf("Tro choi tung dong tien sap ngua.");
  printf("\nHai nguoi choi A va B se lan luot tung dong tien");
  printf("\nNeu den luot nguoi nao ma tung ra dong sap thi");
  printf("\nNguoi kia se bi mat tien va nguoc lai.");
  printf("\nTro choi se ket thuc neu mot nguoi het tien hoac nhan ESC.\n\n");
  printf("\n    A    \t\t    B\n");
  y = wherey();
  for (i=0; i<4; i++)
    printf("* * * * *\t\t* * * * *\n");
  gotoxy(1,y+11);
  cprintf("Nhan phim bat ky de di hoac T de choi tu dong");
  do {
    gotoxy(1,y+10);
    cprintf("Den luot %c di :   ", luot + 'A');
    if (tudong)
    {
      delay(100);
      if (kbhit())
        c = getch();
    }
    else
    {
      c = toupper(getch());
      if (c == 'T')
        tudong = 1;
    }
    if (c != 27)
    {
       n = random(100);
       dong = random(2);
       for (k=0; k<n; k++)
       {
         if (dong == 1)
           dong = 0;
         else
           dong = 1;
         gotoxy(18,y+10);
         cprintf("%d", dong);
         delay(10);
       }
       if (dong == 0)
       {
         if (luot == 1)
           giam1();
         else
          giam0();
       }
       else
       {
         if (luot == 1)
           giam0();
         else
           giam1();
       }
       if (luot == 0)
         luot = 1;
       else
         luot = 0;
    }
  } while (player[0] > 0 && player[1] > 0 && c != 27);
  gotoxy(1,y+12);
  if (player[0] ==0)
    cprintf("A da het tien roi!");
  else if (player[1] ==0)
    cprintf("B da het tien roi!");
  else
    cprintf("Khong bai bac la tot!!!");
  getch();
}