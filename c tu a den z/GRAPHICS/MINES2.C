/* Tro choi do min */
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include "mouse.inc"

#pragma warn -pro

#define WIDTH 16

#define MAXROW  8
#define MAXCOL  8
#define WALL    8
#define PANEL  20
#define MINES 10

#define UP   0
#define OPEN 1
#define MARK 2

int xlpanel, ylpanel, xbpanel, ybpanel;
int xleft, yleft;
int gameover;

typedef struct {
  int status;
  int number;
  int mine;
} BLOCK;

BLOCK block[MAXROW][MAXCOL];

void getrowcol(int x, int y, int *row, int *col)
{
  *row = (x - xleft) / WIDTH;
  *col = (y - yleft) / WIDTH;
}

void drawblock0(int row, int col)
{
  int x1, y1, x2, y2;
  setfillstyle(SOLID_FILL, LIGHTGRAY);
  setcolor(LIGHTGRAY);
  x1 = xleft + row * WIDTH;
  y1 = yleft + col * WIDTH;
  x2 = xleft + (row+1)* WIDTH - 1;
  y2 = yleft + (col+1) * WIDTH - 1;
  bar(x1, y1, x2, y2);
  setcolor(WHITE);
  line(x1, y1, x2-1, y1);
  line(x1, y1, x1, y2-1);
  setcolor(DARKGRAY);
  line(x2, y1+1, x2, y2);
  line(x1+1, y2, x2, y2);
}

void drawblock1(int row, int col)
{
  int x1, y1, x2, y2;
  char s[2];

  setfillstyle(SOLID_FILL, LIGHTGRAY);
  setcolor(LIGHTGRAY);
  x1 = xleft + row * WIDTH;
  y1 = yleft + col * WIDTH;
  x2 = xleft + (row+1)* WIDTH - 1;
  y2 = yleft + (col+1) * WIDTH - 1;
  bar(x1, y1, x2, y2);
  setcolor(DARKGRAY);
  line(x2, y1, x2, y2);
  line(x1, y2, x2, y2);
  if (block[row][col].number != 0)
  {
    itoa(block[row][col].number, s, 10);
    setcolor(block[row][col].number);
    outtextxy(x1+5, y1+4, s);
  }
}

void drawblock2(int row, int col)
{
  int x1, y1, x2, y2, poly[6];
  x1 = xleft + row * WIDTH;
  y1 = yleft + col * WIDTH;
  x2 = xleft + (row+1)* WIDTH - 1;
  y2 = yleft + (col+1) * WIDTH - 1;
  drawblock0(row, col);
  setcolor(BLACK);
  line(x1+(x2-x1)/2+4, y1+4, x1+(x2-x1)/2+4, y2-4);
  poly[0] = poly[2] = x1+(x2-x1)/2+4;
  poly[1] = y1+4;
  poly[3] = y1+8;
  poly[4] = x1+4;
  poly[5] = y1+8;
  setcolor(RED);
  setfillstyle(SOLID_FILL, RED);
  fillpoly(3, poly);
}

void drawblock3(int row, int col)
{
  int x1, y1;
  x1 = xleft + row * WIDTH;
  y1 = yleft + col * WIDTH;
  drawblock0(row, col);
  setcolor(BLACK);
  outtextxy(x1+5, y1+4, "*");
}

void drawblock(int row, int col)
{
  switch(block[row][col].status)
  {
    case UP : drawblock0(row, col);
             break;
    case OPEN : drawblock1(row, col);
             break;
    case MARK : drawblock2(row, col);
             break;
    case MINES : drawblock3(row, col);
             break;
  }
}

void toggle(int row, int col)
{
  if (row>=0 && row<MAXROW && col>=0 && col <MAXCOL && block[row][col].status == 0)
  {
    block[row][col].status = 1;
    drawblock(row,col);
    if (block[row][col].number == 0)
    {
      toggle(row-1, col-1);
      toggle(row-1, col);
      toggle(row-1, col+1);
      toggle(row+1, col-1);
      toggle(row+1, col);
      toggle(row+1, col-1);
      toggle(row, col-1);
      toggle(row, col+1);
    }
  }
}

void drawpanel()
{
  setfillstyle(SOLID_FILL, BLACK);
  setcolor(BLACK);
  bar(xlpanel, ylpanel, xbpanel, ybpanel);
}

void drawboard()
{
  int xc, yc, x1, y1, x2, y2, i, j, n, row, col;

  xc = getmaxx() / 2;
  yc = getmaxy() / 2;
  setfillstyle(SOLID_FILL, LIGHTGRAY);
  setcolor(LIGHTGRAY);
  x1 = xc-MAXCOL*WIDTH/2-WALL;
  y1 = yc-MAXROW*WIDTH/2-PANEL-WALL*2;
  x2 = xc+MAXCOL*WIDTH/2+WALL-1;
  y2 = yc+MAXROW*WIDTH/2+WALL-1;
  bar(x1, y1,x2,y2);
  setcolor(WHITE);
  line(x1, y1, x1, y2);
  line(x1, y1, x2, y1);
  line(x2-WALL+1, y1+PANEL+WALL*2-1, x2-WALL+1, y2-WALL+1);
  line(x1+WALL-1, y2-WALL+1, x2-WALL+1, y2-WALL+1);
  line(x2-WALL+1, y1+WALL-1, x2-WALL+1, y1+WALL+PANEL+1);
  line(x1+WALL-1, y1+WALL+PANEL+1, x2-WALL+1, y1+WALL+PANEL+1);
  setcolor(DARKGRAY);
  line(x2, y1, x2, y2);
  line(x1, y2, x2, y2);
  line(x1+WALL-1, y1+PANEL+WALL*2-1, x1+WALL-1, y2-WALL+1);
  line(x1+WALL-1, y1+PANEL+WALL*2-1, x2-WALL+1, y1+PANEL+WALL*2-1);
  line(x1+WALL-1, y1+WALL-1, x2-WALL+1, y1+WALL-1);
  line(x1+WALL-1, y1+WALL-1, x1+WALL-1, y1+WALL+PANEL+1);
  xlpanel = x1 + WALL;
  ylpanel = y1+WALL;
  xbpanel = x2-WALL;
  ybpanel = y1+WALL+PANEL;
  xleft = x1+WALL;
  yleft = y1+WALL*2+PANEL;
  drawpanel();
  randomize();
  for (i=0; i<MAXROW; i++)
    for (j=0; j<MAXCOL; j++)
    {
      block[i][j].status = 0;
      block[i][j].mine = 0;
      block[i][j].number = 0;
      drawblock(i, j);
    }
  n = 0;
  while (n<MINES)
  {
    row= random(MAXROW);
    col = random(MAXCOL);
    if (block[row][col].mine == 0)
    {
      block[row][col].mine = 1;
      if (row>0)
      {
        if (col>0)
          block[row-1][col-1].number++;
        block[row-1][col].number++;
        if (col<MAXCOL-1)
          block[row-1][col+1].number++;
      }
      if (row<MAXROW-1)
      {
        if (col>0)
          block[row+1][col-1].number++;
        block[row+1][col].number++;
        if (col<MAXCOL-1)
          block[row+1][col+1].number++;
      }
      if (col>0)
        block[row][col-1].number++;
      if (col<MAXCOL-1)
        block[row][col+1].number++;
      n++;
    }
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  int row, col;
  unsigned char lbutton, rbutton;
  int xmouse, ymouse;
  char sxmouse[6], symouse[6];

  initgraph(&gr_drive, &gr_mode, "E:/TC/BGI");
  reset_mouse();
  if (MOUSE_THERE)
  {
    drawboard();
	  show_mouse();
    gameover = 0;
    do {
      lbutton = rbutton = 0;
      do {
        get_mouse_button(&lbutton, &rbutton, &xmouse, &ymouse);
      } while (lbutton == 0 && rbutton == 0);
      hide_mouse();
      if (lbutton == 1 && rbutton == 1)
        gameover = 1;
      getrowcol(xmouse, ymouse, &row, &col);
      if (lbutton == 1)
      {
        if (block[row][col].status == UP)
          if (block[row][col].mine == 0)
            toggle(row,col);
          else
          {
            for (row=0; row<MAXROW; row++)
              for (col=0; col<MAXCOL; col++)
                if (block[row][col].mine == 1)
                {
                  block[row][col].status = MINES;
                  drawblock(row, col);
                }
            gameover=1;
            show_mouse();
            getch();
          }
      }
      else if (rbutton == 1)
      {
        switch(block[row][col].status)
        {
          case UP : block[row][col].status = MARK;
                    break;
          case MARK : block[row][col].status = UP;
                    break;
        }
        drawblock(row, col);
      }
      show_mouse();
      while (lbutton || rbutton)
        get_mouse_button(&lbutton, &rbutton, &xmouse, &ymouse);
    } while (!gameover);
  }
  else
  {
    printf("Khong co mouse!");
    getch();
  }
  closegraph();
}
