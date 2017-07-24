/* Bai tap 2_26 - Chuong trinh ve duong Sierpinski Gasket */
#include <conio.h>
#include <graphics.h>
#include <math.h>

typedef struct POINT {
  int x, y;
} POINT ;

POINT A, B, C;

void Sierpinski_Gasket(POINT A, POINT B, POINT C, int n)
{
  POINT AB, BC, CA;

  line(A.x, A.y, B.x, B.y);
  line(A.x, A.y, C.x, C.y);
  line(C.x, C.y, B.x, B.y);

  if (n>0)
  {
    AB.x = (A.x + B.x) / 2;
    AB.y = (A.y + B.y) / 2;
    BC.x = (C.x + B.x) / 2;
    BC.y = (C.y + B.y) / 2;
    CA.x = (C.x + A.x) / 2;
    CA.y = (C.y + A.y) / 2;
    Sierpinski_Gasket(A, AB, CA, n-1);
    Sierpinski_Gasket(AB, B, BC, n-1);
    Sierpinski_Gasket(CA, BC, C, n-1);
  }
}

void main()
{
  int gr_drive = DETECT, gr_mode;
  double temp;

  initgraph(&gr_drive, &gr_mode, "");
  setcolor(YELLOW);
  rectangle(0, 0, getmaxx(), getmaxy());

  A.x = getmaxx() / 2;
  A.y = 10;
  B.x = A.x - (265);
  B.y = C.y = 10 + (int)((double)530 * sqrt(3)) / 2;
  C.x = A.x + (265);

  Sierpinski_Gasket(A, B, C, 5);
  getch();

  closegraph();
}