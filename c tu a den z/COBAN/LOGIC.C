/* Bai tap 1_86 - Tro choi Logic */
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>
#include<stdio.h>
int day[7] = {-1,-1,-1,-1,-1,-1,-1};
int sonhap[4];
int somay[4];
int solanthu;
int timthay;

void khoitao()
{
  char tieude[] = "L O G I C    G A M E";
  int j, i, dich;
  textmode(C40);
  clrscr();
  textcolor(YELLOW);
  dich = (40 - strlen(tieude)) / 2;
  for (i=strlen(tieude)-1; i>=0; i--)
  {
    movetext(1,3,39,3,2,3);
    gotoxy(1,3);
    putch(tieude[i]);
    delay(40);
  }
  for (i=1; i<=dich; i++)
  {
    movetext(1,3,39,3,2,3);
    gotoxy(1,3);
    putch(' ');
    delay(40);
  }
  randomize();
  for (i=0; i<4; i++)
  {
    do {
      j = random(6)+1;
    } while (day[j] != -1);
    day[j] = i;
    somay[i] = j;
   // printf ("%d",&j);
  }
  gotoxy(14,5);         cprintf("ÉÍÍÍÍÍÍÑÍÍÍÍÍÍ»");
  for (i=0; i<6; i++)
  {
    gotoxy(14,5+i*2+1); cprintf("º      ³      º");
    gotoxy(14,5+i*2+2); cprintf("ÇÄÄÄÄÄÄÅÄÄÄÄÄÄ¶");
  }
  gotoxy(14,17);        cprintf("ÈÍÍÍÍÍÍÏÍÍÍÍÍÍ¼");
  solanthu = 1;
  timthay = 0;
  textcolor(WHITE);
  gotoxy(1, 25);
  cprintf("Nhap chuoi 4 so khac nhau tu 1 den 6");
}

void nhapso()
{
  char c;
  int i;

  for (i=0; i<4; i++)
    sonhap[i]=0;
  gotoxy(16,5+solanthu*2-1);
  do {
    c = getch();
    switch(c)
    {
      case '1' :
      case '2' :
      case '3' :
      case '4' :
      case '5' :
      case '6' : textcolor(c-39);
		 cprintf("%c",c);
		 sonhap[wherex()-16-1] = c - 48;
		 if (wherex()==20)
		   gotoxy(wherex()-1, wherey());
		 break;
      case 0   :
		 c = getch();
		 switch(c)
		 {
		   case 75 : if (wherex()>16)
			       gotoxy(wherex()-1,wherey());
			     break;
		   case 77 : if (wherex()<19)
			       gotoxy(wherex()+1,wherey());
			     break;
		 }
		 break;
      default :  sound(880);
		 delay(100);
		 nosound();
    }
  } while (!((c=='\r') && (sonhap[0] != 0) && (sonhap[1] != 0)
		   && (sonhap[2] != 0) && (sonhap[3] != 0)));
}

void kiemtra()
{
  int diem = 0, i;
  for (i=0; i<4; i++)
    if (day[sonhap[i]] != -1)
       if (day[sonhap[i]] == i)
	  diem += 10;
       else
	  diem ++;
  if (diem==40)
    timthay=1;
  else
  {
    int sotrung, sotrat;
    sotrung=diem / 10;
    sotrat = diem % 10;
    textcolor(GREEN);
    gotoxy(23,5+solanthu*2-1);
    for (i=1; i<=sotrung; i++)
      cprintf("+");
    textcolor(WHITE);
    for (i=1; i<=sotrat; i++)
      cprintf("-");
    solanthu ++;
  }
}

void main()
{
  int i;

  khoitao();
  do {
    nhapso();
    kiemtra();
  } while ((solanthu <= 6) && (timthay==0));
  if (timthay==1)
  {
    textcolor(YELLOW+BLINK);
    gotoxy(1,23);
    cprintf("Ban da thang.");
  }
  else
  {
    textcolor(GREEN+BLINK);
    gotoxy(1,23);
    cprintf("Ban da thua.");
    textcolor(YELLOW);
  }
  cprintf(" Ket qua dung = ");
  for (i=0; i<4; i++)
  {
    textcolor(somay[i]+9+BLINK);
    cprintf("%c",somay[i]+48);
  }
  getch();
}
