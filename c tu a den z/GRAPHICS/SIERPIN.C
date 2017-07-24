/* Bai tap 2_29 - Chuong trinh ve duong Sierpinski */
#include <conio.h>
#include <graphics.h>

int h;

void A (int);
void B (int);
void C (int);
void D (int);

void A(int i)
{
  if (i>=0)
  {
    A(i-1); linerel(h, -h);
    B(i-1); linerel(2*h, 0);
    D(i-1); linerel(h, h);
    A(i-1);
  }
}

void B(int i)
{
  if (i>=0)
  {
    B(i-1); linerel(-h, -h);
    C(i-1); linerel(0, -2*h);
    A(i-1); linerel(h, -h);
    B(i-1);
  }
}

void C(int i)
{
  if (i>=0)
  {
    C(i-1); linerel(-h, h);
    D(i-1); linerel(-2*h, 0);
    B(i-1); linerel(-h, -h);
    C(i-1);
  }
}

void D(int i)
{
  if (i>=0)
  {
    D(i-1); linerel(h, h);
    A(i-1); linerel(0, 2*h);
    C(i-1); linerel(-h, h);
    D(i-1);
  }
}

void Sierpinski()
{
  h = getmaxx() / 200;
  moveto(125, getmaxy()-50);
  A(4); linerel(h, -h);
  B(4); linerel(-h, -h);
  C(4); linerel(-h, h);
  D(4); linerel(h, h);
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());

  Sierpinski();
  getch();

  closegraph();
}