/* Bai tap 2_94 - Minh hoa mot trai banh nay */
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293
#define MASS 1.0

double x, y, omega, k, theta, a ;

double ham(double x)
{
  return a * fabs(sin(omega*x+theta)) * exp(-k*x);
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  randomize();
  initgraph(&gr_drive, &gr_mode, "");
  line(0, getmaxy()-96, getmaxx(), getmaxy()-96);
  setfillstyle(SOLID_FILL, RED);
  setcolor(RED);
  do {
    x = 0.0;
    omega = M_PI-0.1;
    k = random(50) / 100;
    theta = M_PI/(random(20)+1);
    a = random(100) + 100.0;
    y = ham(x);
    fillellipse(x*100, getmaxy()-100-y, 4, 4);
    do {
      setfillstyle(SOLID_FILL, BLACK);
      setcolor(BLACK);
      fillellipse(x*100, getmaxy()-100-y, 4, 4);
      x+=0.001;
      y = ham(x);
      setfillstyle(SOLID_FILL, RED);
      setcolor(RED);
      fillellipse(x*100, getmaxy()-100-y, 4, 4);
      delay(1);
      k += 0.0001;
    } while (!kbhit() && x*100<getmaxx()+5);
  } while (!kbhit());

  getch();
  closegraph();
}