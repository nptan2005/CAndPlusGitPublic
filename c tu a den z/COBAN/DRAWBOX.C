/* Bai tap 1_87 - Demo ve hop dung conio */
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

char doublebox[] ="ÉÍ»ºÈ¼";
char singlebox[] ="ÚÄ¿³ÀÙ";

void swap(int *x, int *y)
{
  int temp;
  temp = *y;
  *y = *x;
  *x = temp;
}
void drawbox(int x1, int y1, int x2, int y2, int type)
{
  char *boxtype;
  int i;
  if (type == 2)
     boxtype = doublebox;
  else
     boxtype = singlebox;
  gotoxy(x1,y1);
  cprintf("%c", boxtype[0]);
  for (i=x1 + 1; i < x2; i++)
    cprintf("%c", boxtype[1]);
  cprintf("%c", boxtype[2]);
  for (i=y1+1; i<y2; i++)
  {
    gotoxy(x1, i);
    cprintf("%c", boxtype[3]);
    gotoxy(x2, i);
    cprintf("%c", boxtype[3]);
  }
  gotoxy(x1,y2);
  cprintf("%c", boxtype[4]);
  for (i=x1 + 1; i < x2; i++)
    cprintf("%c", boxtype[1]);
  cprintf("%c", boxtype[5]);
}

void drawbox_color(int x1, int y1, int x2, int y2, int type, int color)
{
   if (x1>x2) swap(&x1, &x2);
   if (y1>y2) swap(&y1, &y2);
   textattr(color);
   window(x1, y1, x2, y2);
   clrscr();
   window(1,1,80,25);
   drawbox(x1, y1, x2, y2, type);
}

void main()
{
   int x1, y1, x2, y2, type, color;
   cprintf("\n\rDRAWBOX DEMO.\n\rPress any key to begin...");
   getch();
   randomize();
   while (!kbhit())
   {
      x1 = random(80);
      do {
        x2 = random(80);
      } while (x1 == x2);
      y1 = random(25);
      do {
        y2 = random(25);
      } while (y1 == y2);
      type = random(2) + 1;
      color = random(256);
      drawbox_color(x1,y1,x2,y2,type,color);
      delay(100);
   }
}