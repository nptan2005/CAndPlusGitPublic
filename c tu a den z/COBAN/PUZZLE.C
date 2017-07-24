/* Bai tap 1_49 - Chuong trinh Puzzle 15 so */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define XSTART 30

int board[4][4];
int xspace, yspace;

void khoitao()
{
  int i, j;
  for (i=0; i<4; i++)
    for (j=0; j<4; j++)
      board[i][j] = i*4 + j + 1;
  board[3][3] = 0;
}

void veboard()
{
  int i, j;
  textattr(14);
  clrscr();
  gotoxy(XSTART, 2);
  cprintf("ษออออหออออหออออหออออป");
  for (i=0; i<4; i++)
  {
    gotoxy(XSTART, 2*i+3);
    cprintf("บ    บ    บ    บ    บ");
    gotoxy(XSTART, 2*i+4);
    cprintf("ฬออออฮออออฮออออฮออออน");
  }
  gotoxy(XSTART, 10);
  cprintf("ศออออสออออสออออสออออผ");
  for(i=0; i<4; i++)
    for (j=0; j<4; j++)
    {
      gotoxy(XSTART+1 + j*5, i*2+3);
      cprintf("%3d", board[i][j]);
    }
  gotoxy(XSTART+16, 9);
  cprintf("   ");
  gotoxy(XSTART, 12);
  cprintf("Nhan S de bat dau.");
  gotoxy(XSTART, 13);
  cprintf("ESC de ket thuc.");
  xspace = 3;
  yspace = 3;
}

void dichtrai()
{
  if (xspace < 3 )
  {
    board[yspace][xspace] = board[yspace][xspace+1];
    board[yspace][xspace+1] = 0;
    gotoxy(XSTART+1 + xspace*5, yspace*2+3);
    cprintf("%3d", board[yspace][xspace]);
    xspace++;
    gotoxy(XSTART+1 + xspace*5, yspace*2+3);
    cprintf("   ");
  }
}

void dichphai()
{
  if (xspace > 0 )
  {
    board[yspace][xspace] = board[yspace][xspace-1];
    board[yspace][xspace-1] = 0;
    gotoxy(XSTART+1 + xspace*5, yspace*2+3);
    cprintf("%3d", board[yspace][xspace]);
    xspace--;
    gotoxy(XSTART+1 + xspace*5, yspace*2+3);
    cprintf("   ");
  }
}

void dichlen()
{
  if (yspace < 3 )
  {
    board[yspace][xspace] = board[yspace+1][xspace];
    board[yspace+1][xspace] = 0;
    gotoxy(XSTART+1 + xspace*5, yspace*2+3);
    cprintf("%3d", board[yspace][xspace]);
    yspace++;
    gotoxy(XSTART+1 + xspace*5, yspace*2+3);
    cprintf("   ");
  }
}

void dichxuong()
{
  if (yspace > 0 )
  {
    board[yspace][xspace] = board[yspace-1][xspace];
    board[yspace-1][xspace] = 0;
    gotoxy(XSTART+1 + xspace*5, yspace*2+3);
    cprintf("%3d", board[yspace][xspace]);
    yspace--;
    gotoxy(XSTART+1 + xspace*5, yspace*2+3);
    cprintf("   ");
  }
}

int test()
{
  int i, j;

  for (i=0; i<4; i++)
    for (j=0; j<4; j++)
      if (i!=yspace || j!=xspace)
        if (board[i][j] != i*4 + j + 1)
          return 0;
  textattr(15);
  gotoxy(XSTART, 14);
  cprintf("Hoan ho, ban da thang");
  getch();
  return 1;
}

void run()
{
  int done = 0, sobuoc = 0, i, n = 0;
  char c;
  randomize();
  while (n < 100)
  {
    i = random(4);
    switch(i)
    {
       case(0) : dichtrai();
                 break;
       case(1) : dichphai();
                 break;
       case(2) : dichlen();
                 break;
       case(3) : dichxuong();
                 break;
    }
    n++;
  }
  gotoxy(XSTART, 12);
  cprintf("%c %c %c %c de di chuyen.", 24, 25, 26, 27);
  do {
    c = getch();
    if (c == 0)
      c = getch();
    switch(c)
    {
      case 27 : done = 1;
                break;
      case 75 : dichtrai();
                break;
      case 77 : dichphai();
                break;
      case 72 : dichlen();
                break;
      case 80 : dichxuong();
                break;
    }
    sobuoc++;
    gotoxy(XSTART, 11);
    cprintf("So buoc : %d", sobuoc);
    if (!done)
      done = test();
  } while (!done);
}
void main()
{
   char c;

   khoitao();
   veboard();
   do {
    c = toupper(getch());
   } while (c != 27 && c != 'S');
   if (c == 'S')
     run();
}