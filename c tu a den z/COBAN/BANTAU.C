/* Bai tap 1_42 - Chuong trinh ban tau */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAXCOL 26
#define MAXROW 22
void drawboard()
{
  int i, j;
  textattr(0x1E);
  clrscr();
  gotoxy(4, 1);
  for (i=0; i<MAXCOL; i++)
    cprintf("%c ", 'A'+ i);
  gotoxy(2, 2);
  cprintf("%c",'и');
  for (i=0; i<MAXCOL; i++)
    cprintf("%s", "мя");
  cprintf("%s", "м╩");
  for (i=0; i<MAXROW; i++)
  {
    gotoxy(1, i+3);
    cprintf("%c%s",'A'+i, "г");
    for (j=0; j<MAXCOL; j++)
      cprintf("%s", "де");
    cprintf("%s", "д╤");
  }
  gotoxy(2, 3+MAXROW);
  cprintf("%c",'х');
  for (i=0; i<MAXCOL; i++)
    cprintf("%s", "мо");
  cprintf("%s", "м╪");
}

char nhaptoado(char min, char max)
{
  char c;
  do {
    c = toupper(getch());
  } while (c < min || c > max);
  putc(c, stdout);
  return c;
}

void main()
{
  char x, y, xplayer, yplayer, xcomp, ycomp, xc, yc;
  int done = 0, luot = 1, i, j, oldx, oldy;
  int board[MAXROW][MAXCOL];

  printf("\nNhap vao toa do X cua tau ban (A-Z): ");
  x = nhaptoado('A', 'V');
  printf("\nNhap vao toa do Y cua tau ban (A-V): ");
  y = nhaptoado('A', 'Z');
  drawboard();
  window((MAXCOL+3) * 2, 1, 80, 25);
  textattr(0x0E);
  clrscr();
  cprintf("Quy tac choi : ");
  cprintf("\n\rMuon ban o nao, ta nhaptoa do hang roi cot. Vidu AZ");
  cprintf(" de ban o o hang Acot Z.\n\rMoi di truoc :");
  randomize();
  do {
    xc = random(MAXROW)+'A';
  } while (xc == x);
  yc = random(MAXCOL)+'A';
  for (i=0; i<MAXROW; i++)
    for (j=0; j<MAXCOL; j++)
    board[i][j] = 0;
  do {
    cprintf("\n\r%d - ", luot);
    xplayer = nhaptoado('A','V');
    yplayer = nhaptoado('A','Z');
    oldx = wherex();
    oldy = wherey();
    window(1,1,80,25);
    gotoxy((yplayer-'A'+2) * 2, xplayer - 'A' + 3);
    cprintf("%c", 4);
    window((MAXCOL+3) * 2, 1, 80, 25);
    gotoxy(oldx, oldy);
    if (xplayer == xc && yplayer == yc)
    {
      textattr(2);
      cprintf("\n\rOi chet toi roi!");
      done = 1;
    }
    else
    {
      do {
        xcomp = random(MAXROW);
        ycomp = random(MAXCOL);
      } while (board[xcomp][ycomp] == 1);
      cprintf(" - %c%c", xcomp+'A', ycomp+'A');
      if (xcomp+'A' == x && ycomp+'A' == y)
      {
        textattr(3);
        cprintf("\n\rBan da chet!");
        done = 1;
      }
      board[xcomp][ycomp] = 1;
    }
    luot++;
  } while (!done);
  cprintf("\n\r\n\rNhan phim de ket thuc");
  getch();
  window(1, 1, 80, 25);
}