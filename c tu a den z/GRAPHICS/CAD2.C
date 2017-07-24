/* Bai tap 2_89 - Chuong trinh CAD co effect */
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <math.h>
#include "mouse.inc"

#define MAXOBJECTS 100
#define _LINE 0
#define _CIRCLE 1
#define _ELLIPSE 2
#define _RECTANGLE 3
#define _SQUARE 4

typedef struct tagpoint {
  double x, y;
} POINT;

typedef struct tagline {
  int x1, y1, x2, y2;
} LINE;

typedef struct tagcircle {
  int xc, yc, radius;
} CIRCLE;

typedef struct tagellipse {
  int xc, yc, xradius, yradius;
} ELLIPSE;

typedef struct tagrectangle {
  int x1, y1, x2, y2;
} RECTANGLE;

typedef struct tagsquare {
  int x1, y1, x2, y2;
} SQUARE;

struct object {
  int type;
  union tagobj {
    LINE l;
    CIRCLE c;
    ELLIPSE e;
    RECTANGLE r;
    SQUARE s;
  } obj;
} doituong[MAXOBJECTS];

int x, y, i, numobj = 0;
unsigned char lbutton = 0, rbutton = 0;

const char *menu[10] = {
      "Line",
      "Circle",
      "Ellipse",
      "Rectangle",
      "Square",
      "-",
      "Open",
      "Save",
      "-",
      "Quit"
      };


void getmouse()
{
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
  } while (lbutton == 0 && rbutton == 0);
}

void clearmouse()
{
  while (lbutton || rbutton)
    get_mouse_button(&lbutton, &rbutton, &x, &y);
}

void message(char *s)
{
  struct viewporttype view;
  int color = getcolor();
  setcolor(BLACK);
  setfillstyle(SOLID_FILL, BLACK);
  getviewsettings(&view);
  setviewport(0, 0, getmaxx(), getmaxy(), 1);
  bar(1, getmaxy()-19, getmaxx() - 101, getmaxy()-2);
  setcolor(WHITE);
  outtextxy(4, getmaxy() - 12, s);
  setcolor(color);
  setviewport(view.left, view.top, view.right, view.bottom, view.clip);
}

void Line()
{
  int x1, y1, oldx,  oldy;
  message("Nhap chuot de chon hai diem dau mut de ve LINE");
  clearmouse();
  getmouse();
  oldx = x1 = x;
  oldy = y1 = y;
  setwritemode(XOR_PUT);
  setcolor(YELLOW);
  clearmouse();
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
    if (lbutton == 0 && rbutton == 0)
    {
      if (oldx != x || oldy != y)
      {
        hide_mouse();
        line(x1, y1, oldx, oldy);
        oldx = x;
        oldy = y;
        line(x1, y1, oldx, oldy);
        show_mouse();
      }
    }
  } while (lbutton == 0 && rbutton == 0);
  doituong[numobj].type = _LINE;
  doituong[numobj].obj.l.x1 = x1;
  doituong[numobj].obj.l.y1 = y1;
  doituong[numobj].obj.l.x2 = x;
  doituong[numobj].obj.l.y2 = y;
  numobj++;
  clearmouse();
  setwritemode(COPY_PUT);
}

void Circle()
{
  int x1, y1, radius, oldx, oldy;
  message("Nhap chuot de chon tam va hai ban kinh de ve ELLPISE");
  clearmouse();
  getmouse();
  oldx = x1 = x;
  oldy = y1 = y;
  setwritemode(XOR_PUT);
  circle(x1, y1, abs(oldx-x1));
  clearmouse();
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
    if (lbutton == 0 && rbutton == 0)
    {
      if (oldx != x || oldy != y)
      {
        hide_mouse();
        setcolor(BLACK);
        circle(x1, y1, abs(oldx-x1));
        oldx = x;
        oldy = y;
        setcolor(RED);
        circle(x1, y1, abs(oldx-x1));
        show_mouse();
      }
    }
  } while (lbutton == 0 && rbutton == 0);
  doituong[numobj].type = _CIRCLE;
  doituong[numobj].obj.c.xc = x1;
  doituong[numobj].obj.c.yc = y1;
  doituong[numobj].obj.c.radius = abs(oldx-x1);
  numobj++;
  clearmouse();
  setwritemode(COPY_PUT);
}

void Ellipse()
{
  int x1, y1, xradius, yradius, oldx, oldy;
  message("Nhap chuot de chon tam va ban kinh de ve CIRCLE");
  clearmouse();
  getmouse();
  oldx = x1 = x;
  oldy = y1 = y;
  setwritemode(XOR_PUT);
  ellipse(x1, y1, 0, 360, abs(oldx-x1), abs(oldy-y1));
  clearmouse();
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
    if (lbutton == 0 && rbutton == 0)
    {
      if (oldx != x || oldy != y)
      {
        hide_mouse();
        setcolor(BLACK);
        ellipse(x1, y1, 0, 360, abs(oldx-x1), abs(oldy-y1));
        oldx = x;
        oldy = y;
        setcolor(GREEN);
        ellipse(x1, y1, 0, 360, abs(oldx-x1), abs(oldy-y1));
        show_mouse();
      }
    }
  } while (lbutton == 0 && rbutton == 0);
  doituong[numobj].type = _ELLIPSE;
  doituong[numobj].obj.e.xc = x1;
  doituong[numobj].obj.e.yc = y1;
  doituong[numobj].obj.e.xradius = abs(oldx-x1);
  doituong[numobj].obj.e.yradius = abs(oldy-y1);
  numobj++;
  clearmouse();
  setwritemode(COPY_PUT);
}

void Rectangle()
{
  int x1, y1, oldx,  oldy;
  message("Nhap chuot de chon hai diem dau mut de ve LINE");
  clearmouse();
  getmouse();
  oldx = x1 = x;
  oldy = y1 = y;
  setwritemode(XOR_PUT);
  setcolor(WHITE);
  clearmouse();
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
    if (lbutton == 0 && rbutton == 0)
    {
      if (oldx != x || oldy != y)
      {
        hide_mouse();
        rectangle(x1, y1, oldx, oldy);
        oldx = x;
        oldy = y;
        rectangle(x1, y1, oldx, oldy);
        show_mouse();
      }
    }
  } while (lbutton == 0 && rbutton == 0);
  doituong[numobj].type = _RECTANGLE;
  doituong[numobj].obj.r.x1 = x1;
  doituong[numobj].obj.r.y1 = y1;
  doituong[numobj].obj.r.x2 = x;
  doituong[numobj].obj.r.y2 = y;
  numobj++;
  clearmouse();
  setwritemode(COPY_PUT);
}

void Square()
{
  int x1, y1, oldx,  oldy;
  message("Nhap chuot de chon hai diem dau mut de ve SQUARE");
  clearmouse();
  getmouse();
  oldx = x1 = x;
  oldy = y1 = y;
  setwritemode(XOR_PUT);
  setcolor(BLUE);
  clearmouse();
  do {
    get_mouse_button(&lbutton, &rbutton, &x, &y);
    if (lbutton == 0 && rbutton == 0)
    {
      if (oldx != x || oldy != y)
      {
        hide_mouse();
        if (oldx-x1 >= oldy-y1)
          rectangle(x1, y1, oldx, oldx-x1+y1);
        else
          rectangle(x1, y1, oldy-y1+x1, oldy);
        oldx = x;
        oldy = y;
        if (oldx-x1 >= oldy-y1)
          rectangle(x1, y1, oldx, oldx-x1+y1);
        else
          rectangle(x1, y1, oldy-y1+x1, oldy);
        show_mouse();
      }
    }
  } while (lbutton == 0 && rbutton == 0);
  doituong[numobj].type = _SQUARE;
  doituong[numobj].obj.s.x1 = x1;
  doituong[numobj].obj.s.y1 = y1;
  if (oldx-x1 >= oldy-y1)
  {
    doituong[numobj].obj.s.x2 = oldx;
    doituong[numobj].obj.s.y2 = oldx-x1+y1;
  }
  else
  {
    doituong[numobj].obj.s.x2 = oldy-y1+x1;
    doituong[numobj].obj.s.y2 = oldy;
  }
  numobj++;
  clearmouse();
  setwritemode(COPY_PUT);
}

void UpdateScreen()
{
  int i;
  setviewport(1, 1, getmaxx() - 101, getmaxy() - 21, 1);
  clearviewport();
  for (i=0; i<numobj; i++)
    switch (doituong[i].type)
    {
      case _LINE : setcolor(YELLOW);
                   line(doituong[i].obj.l.x1, doituong[i].obj.l.y1,
                        doituong[i].obj.l.x2, doituong[i].obj.l.y2);
                   break;
      case _CIRCLE : setcolor(RED);
                   circle(doituong[i].obj.c.xc, doituong[i].obj.c.yc,
                        doituong[i].obj.c.radius);
                   break;
      case _ELLIPSE : setcolor(GREEN);
                   ellipse(doituong[i].obj.e.xc, doituong[i].obj.e.yc, 0, 360,
                        doituong[i].obj.e.xradius, doituong[i].obj.e.yradius);
                   break;
      case _RECTANGLE : setcolor(WHITE);
                   rectangle(doituong[i].obj.r.x1, doituong[i].obj.r.y1,
                        doituong[i].obj.r.x2, doituong[i].obj.r.y2);
                   break;
      case _SQUARE : setcolor(BLUE);
                   rectangle(doituong[i].obj.s.x1, doituong[i].obj.s.y1,
                        doituong[i].obj.s.x2, doituong[i].obj.s.y2);
                   break;
    }
  setviewport(0, 0, getmaxx(), getmaxy(), 1);
}

void Save()
{
  const char filename[] = "CAD.DAT";
  FILE *fp;
  int i;

  if ((fp=fopen(filename, "w+b")) == NULL)
  {
    message("Khong the tao tap tin CAD.DAT");
    return;
  }
  fwrite(&numobj, sizeof(int), 1, fp);
  fwrite(&doituong, sizeof(struct object), numobj, fp);
  fclose(fp);
}

void Open()
{
  const char filename[] = "CAD.DAT";
  FILE *fp;
  int i;

  if ((fp=fopen(filename, "rb")) == NULL)
  {
    message("Khong the mo tap tin CAD.DAT");
    return;
  }
  fread(&numobj, sizeof(int), 1, fp);
  fread(&doituong, sizeof(struct object), numobj, fp);
  fclose(fp);
}

void run()
{
  int done = 0, i;
  do {
    getmouse();
    if (x >= getmaxx() - 90)
    {
      i = (y - 20) / 16;
      setviewport(1, 1, getmaxx() - 101, getmaxy() - 21, 1);
      switch (i)
      {
        case 0 : Line();
                 break;
        case 1 : Circle();
                 break;
        case 2 : Ellipse();
                 break;
        case 3 : Rectangle();
                 break;
        case 4 : Square();
                 break;
        case 6 : Open();
                 break;
        case 7 : Save();
                 break;
        case 9 : done = 1;
                 break;
      }
      setviewport(0, 0, getmaxx(), getmaxy(), 1);
      UpdateScreen();
    }
    else
    {
    }
    clearmouse();
  } while (!done);
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  reset_mouse();
  show_mouse();
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());
  line(getmaxx() - 100, 0, getmaxx() - 100, getmaxy());
  line(0, getmaxy()-20, getmaxx() - 100, getmaxy()-20);
  for (i=0; i<10; i++)
    if (strcmp(menu[i], "-") == 0)
      line(getmaxx() - 90, 20 + i * 16, getmaxx() - 20, 20 + i * 16);
    else
      outtextxy(getmaxx() - 90, 20 + i * 16, menu[i]);
  show_mouse();
  run();
  closegraph();
}