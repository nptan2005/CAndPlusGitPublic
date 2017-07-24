#include <stdio.h>
#include <dos.h>
#include <graphics.h>
#include "mouse.inc"

#define MAX 25
#define HEIGHT 16

int board[MAX][MAX];
int xleft, yleft;
int order;

void print_order()
{
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, BLACK);
  bar(xleft+MAX*HEIGHT+30, 40, xleft+MAX*HEIGHT+150, 60);
  switch(order)
  {
    case 0 :  setcolor(BLUE);
              outtextxy(xleft+MAX*HEIGHT+30, 40, "BLUE to move");
              break;
    case 1 :  setcolor(RED);
              outtextxy(xleft+MAX*HEIGHT+30, 40, "RED to move");
              break;
  }
}

void drawboard()
{
   int i, j;
   xleft = 10;
   yleft = (getmaxy() - MAX * HEIGHT) / 2;
   setcolor(YELLOW);
   for (i=0; i<=MAX; i++)
   {
     line(xleft, yleft + i*HEIGHT, xleft + MAX*HEIGHT, yleft + i*HEIGHT);
     line(xleft + i*HEIGHT, yleft, xleft + i*HEIGHT, yleft + MAX*HEIGHT);
   }
   rectangle(xleft-1, yleft-1,xleft+MAX*HEIGHT+1,yleft+MAX*HEIGHT+1);
   rectangle(xleft-2, yleft-2,xleft+MAX*HEIGHT+2,yleft+MAX*HEIGHT+2);
   order = 0;
   for (i=0; i<MAX; i++)
     for (j=0; j<MAX; j++)
       board[i][j] = -1;
}

void get_row_col(int x, int y, int *row, int *col)
{
  *col = (x - xleft) / HEIGHT;
  *row = (y - yleft) / HEIGHT;
}

int check(int row, int col)
{
  int i, j, tong = 0;
  for (i=-4; i<=4; i++)
    if (col + i >= 0 && col+i < MAX)
      if (board[row][col+i] == order)
        tong++;
      else
        break;
  if (tong >= 5)
    return 1;
  tong = 0;
  for (i=-4; i<=4; i++)
    if (row + i >= 0 && row+i < MAX)
      if (board[row+i][col] == order)
        tong++;
      else
        break;
  if (tong >= 5)
    return 1;
  tong = 0;
  for (i=-4; i<=4; i++)
    if (row + i >= 0 && row+i < MAX && col + i > 0 && col + i < MAX)
      if(board[row+i][col+i] == order)
        tong++;
      else
        break;
  if (tong >= 5)
    return 1;
  tong = 0;
  for (i=-4, j=4; i<=4; i++, j--)
    if (row + j > 0 && row+j < MAX && col + i > 0 && col + i < MAX)
      if (board[row+j][col+i] == order)
        tong++;
      else
        break;
  if (tong >= 5)
    return 1;
  return 0;
}

void print_win()
{
  switch(order)
  {
    case 0 : setcolor(BLUE);
             outtextxy(xleft+MAX*HEIGHT+30, 140, "BLUE winner");
             break;
    case 1 : setcolor(RED);
             outtextxy(xleft+MAX*HEIGHT+30, 140, "RED winner");
             break;
  }
  setcolor(YELLOW);
  outtextxy(xleft+MAX*HEIGHT+30, 160, "Game Over");
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  int x, y, gameover = 0;
  unsigned char lbutton, rbutton = 0;
  int row, col;

  initgraph(&gr_drive, &gr_mode, "");
  rectangle(0, 0, getmaxx(), getmaxy());
  drawboard();
  reset_mouse();
  while (!gameover)
  {
    print_order();
    while (lbutton == 1 || rbutton == 1)
      get_mouse_button(&lbutton, &rbutton, &x, &y);
    show_mouse();
    do {
      get_mouse_button(&lbutton, &rbutton, &x, &y);
    } while (lbutton == 0 && rbutton == 0);
    hide_mouse();
    if (lbutton == 1)
    {
       get_row_col(x, y, &row, &col);
       if (board[row][col]==-1 && row>=0 && col>=0 && row<MAX && col<MAX)
       {
         board[row][col] = order;
         if (check(row, col))
         {
           print_win();
           gameover = 1;
         }
         switch(order)
         {
            case 0 :  setcolor(BLUE);
                      outtextxy(col*HEIGHT+xleft+5, row*HEIGHT+yleft+5, "O");
                      order = 1;
                      break;
            case 1 :  setcolor(RED);
                      outtextxy(col*HEIGHT+xleft+5, row*HEIGHT+yleft+5, "X");
                      order = 0;
                      break;
         }
       }
    }
    if (rbutton == 1)
      gameover = 1;
  }
  show_mouse();
  getch();
  closegraph();
  while (lbutton == 1 || rbutton == 1)
    get_mouse_button(&lbutton, &rbutton, &x, &y);
}