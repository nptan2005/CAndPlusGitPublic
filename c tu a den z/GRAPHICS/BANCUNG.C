/* Skeleton */
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>
#include <stdlib.h>

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293
#define NUMBALL 5

#define INTR 0X1C    /* Ngat thoi gian */
#ifdef __cplusplus
    #define __CPPARGS ...
#else
    #define __CPPARGS
#endif

void interrupt ( *oldhandler)(__CPPARGS);
int count=0;

void interrupt handler(__CPPARGS)
{
   count++;
   oldhandler();
}

/* Bien toan cuc */
int numhit = 0;
int banhcon = NUMBALL;
int yten, xten;
int xbong, ybong;

void drawhit()
{
  char s[3];
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, BLACK);
  bar(65, getmaxy()-19, 90, getmaxy()-1);
  sprintf(s, "%d", numhit);
  setcolor(GREEN);
  outtextxy(68, getmaxy()-13, s);
}

void drawbong(int color, int huong)
{
  setcolor(color);
  setfillstyle(SOLID_FILL, color);
  fillellipse(xbong, ybong, 6, 8);
  if (huong)
  {
    line(xbong, ybong+10, xbong-4, ybong+12);
    line(xbong, ybong+9, xbong-4, ybong+12);
  }
  else
  {
    line(xbong, ybong+10, xbong+4, ybong+12);
    line(xbong, ybong+9, xbong+4, ybong+12);
  }
}

void drawcon()
{
  char s[3];
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, BLACK);
  bar(140, getmaxy()-19, 180, getmaxy()-1);
  sprintf(s, "%d", banhcon);
  setcolor(GREEN);
  outtextxy(145, getmaxy()-13, s);
}

void drawten(int color)
{
  setcolor(color);
  line(xten, yten, xten+13, yten);
  line(xten+9, yten-3, xten+13, yten);
  line(xten+9, yten+3, xten+13, yten);
}

void run()
{
  char c, ban;
  int huong, tocdo;
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());
  line(0, getmaxy()-20, getmaxx(), getmaxy()-20);
  outtextxy(10, getmaxy()-13, "Trung :");
  outtextxy(100, getmaxy()-13, "Con :");
  drawhit();
  yten = 5;
  xten = 3;
  drawten(WHITE);
  ban = 0;
  ybong = getmaxy() - 40;
  xbong = getmaxx() - 10;
  huong = 1;
  drawbong(RED, huong);
  drawcon();
  randomize();
  tocdo = random(3) + 1;
  do {
    if (kbhit() && !ban)
    {
      c = getch();
      if (c == 0)
        c = getch();
      drawten(BLACK);
      switch (c)
      {
        case 'H' : if (yten > 5)
                    yten -= 5;
                  break;
        case 'P' : if (yten < getmaxy()-25)
                    yten += 5;
                  break;
        case 32  : ban = 1;
      }
      drawten(WHITE);
    }
    if (ban)
    {
      drawten(BLACK);
      xten +=3;
      drawten(WHITE);
      delay(10);
      if ((abs(xbong-xten-13)<4 && abs(ybong-yten)<8))
      {
        drawbong(BLACK, huong);
        ban = 0;
        drawten(BLACK);
        xten = 3;
        drawten(WHITE);
        numhit ++;
        drawhit();
        ybong = getmaxy() - 40;
        xbong = getmaxx() - 10;
        tocdo = random(3) + 1;
        drawbong(RED, huong);
        banhcon--;
        drawcon();
        count = 0;
      }
      else if (xten >= getmaxx() - 16)
      {
        ban = 0;
        drawten(BLACK);
        xten = 3;
        drawten(WHITE);
      }
    }
    if (count > 1)
    {
      count = 0;
      drawbong(BLACK, huong);
      ybong -= tocdo;
      if (huong)
        huong = 0;
      else
        huong = 1;
      drawbong(RED, huong);
    }
    if (ybong < 10)
    {
      drawbong(BLACK, huong);
      ybong = getmaxy() - 40;
      xbong = getmaxx() - 10;
      drawbong(RED, huong);
      banhcon--;
      drawcon();
      count = 0;
      tocdo = random(3) + 1;
    }
  } while (c != 27 && banhcon > 0);
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  oldhandler = getvect(INTR);
  setvect(INTR, handler);
  initgraph(&gr_drive, &gr_mode, "");
  run();
  getch();
  closegraph();
  setvect(INTR, oldhandler);
}