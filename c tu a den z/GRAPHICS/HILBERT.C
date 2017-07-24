/* Bai tap 2_28 - Chuong trinh ve duong Hilbert */
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
    D(i-1); linerel(-h, 0);
    A(i-1); linerel(0, -h);
    A(i-1); linerel(h, 0);
    B(i-1);
  }
}

void B(int i)
{
  if (i>=0)
  {
    C(i-1); linerel(0, h);
    B(i-1); linerel(h, 0);
    B(i-1); linerel(0, -h);
    A(i-1);
  }
}

void C(int i)
{
  if (i>=0)
  {
    B(i-1); linerel(h, 0);
    C(i-1); linerel(0, h);
    C(i-1); linerel(-h, 0);
    D(i-1);
  }
}

void D(int i)
{
  if (i>=0)
  {
    A(i-1); linerel(0, -h);
    D(i-1); linerel(-h, 0);
    D(i-1); linerel(0, h);
    C(i-1);
  }
}

void Hilbert()
{
  h = getmaxx() / 99;
  moveto(getmaxx() - 130, getmaxy() - 50);
  A(5);
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());

  Hilbert();
  getch();

  closegraph();
}