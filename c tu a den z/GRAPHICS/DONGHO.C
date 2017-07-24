/* Bai tap 2_21 - Dong ho mat kim */
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <dos.h>

/* he so doi tu do sang radian */
#define RADS 0.017453293
#define CIRCLE 200

double xc, yc;
int gio, phut, giay;

void ve_kim_gio(int color)
{
  double angle;

  setcolor(color);
  angle = ((double)360 * gio / 12 + (double)phut / 2 - 90.0) * RADS;
  moveto(xc - 20.0 * cos(angle), yc - 20.0 * sin(angle));
  lineto(xc - 10.0 * cos(angle + M_PI / 2), yc - 10.0 * sin(angle + M_PI/2));
  lineto(xc + 110.0 * cos(angle), yc + 110.0 * sin(angle));
  lineto(xc + 10.0 * cos(angle + M_PI / 2), yc + 10.0 * sin(angle + M_PI/2));
  lineto(xc - 20.0 * cos(angle), yc - 20.0 * sin(angle));
}

void ve_kim_phut(int color)
{
  double angle;

  setcolor(color);
  angle = ((double)360 * phut / 60 + (double)giay / 10 - 90.0) * RADS;
  moveto(xc - 30.0 * cos(angle), yc - 30.0 * sin(angle));
  lineto(xc - 8.0 * cos(angle + M_PI / 2), yc - 8.0 * sin(angle + M_PI/2));
  lineto(xc + 140.0 * cos(angle), yc + 140.0 * sin(angle));
  lineto(xc + 8.0 * cos(angle + M_PI / 2), yc + 8.0 * sin(angle + M_PI/2));
  lineto(xc - 30.0 * cos(angle), yc - 30.0 * sin(angle));
}

void ve_kim_giay(int color)
{
  double angle;

  setcolor(color);
  angle = ((double)360 * (giay - 3) / 60) * RADS;
  moveto(xc - 40.0 * cos(angle), yc - 40.0 * sin(angle));
  lineto(xc + 150.0 * cos(angle), yc + 150.0 * sin(angle));
  setfillstyle(SOLID_FILL, color);
  fillellipse(xc, yc, 3, 3);
}

void ve_mat_dong_ho()
{
  int i, j;

  setcolor(YELLOW);
  circle(xc, yc, CIRCLE);
  setlinestyle(SOLID_LINE, 0, 3);
  for (i=0; i<12; i++)
    if (i%3 == 0)
    {
      line(xc + (CIRCLE - 2) * sin(RADS * (30 * i - 1)), yc + (CIRCLE - 2) * cos(RADS * (30 * i - 1)),
           xc + (CIRCLE - 24) * sin(RADS * (30 * i - 1)), yc + (CIRCLE - 24) * cos(RADS * (30 * i - 1)));
      line(xc + (CIRCLE - 2) * sin(RADS * (30 * i + 1)), yc + (CIRCLE - 2) * cos(RADS * (30 * i + 1)),
           xc + (CIRCLE - 24) * sin(RADS * (30 * i + 1)), yc + (CIRCLE - 24) * cos(RADS * (30 * i + 1)));
    }
    else
      line(xc + (CIRCLE - 2) * sin(RADS * (30 * i)), yc + (CIRCLE - 2) * cos(RADS * (30 * i)),
           xc + (CIRCLE - 24) * sin(RADS * (30 * i)), yc + (CIRCLE - 24) * cos(RADS * (30 * i)));
}

void run()
{
  struct time timep;
  ve_mat_dong_ho();
  gettime(&timep);
  gio = timep.ti_hour;
  phut = timep.ti_min;
  giay = timep.ti_sec;
  setlinestyle(SOLID_LINE, 0, 0);
  do {
    ve_kim_gio(YELLOW);
    ve_kim_phut(GREEN);
    ve_kim_giay(RED);
    delay(990);
    sound(1000);
    delay(10);
    nosound();
    ve_kim_giay(BLACK);
    ve_kim_phut(BLACK);
    ve_kim_gio(BLACK);
    giay++;
    if (giay >= 60)
    {
      giay %= 60;
      phut++;
      if (phut >= 60)
      {
        phut %= 60;
        gio++;
        if (gio >= 12)
          gio %= 12;
      }
    }
  } while (!kbhit());
}

void main()
{
  int gr_drive = DETECT, gr_mode;

  initgraph(&gr_drive, &gr_mode, "");
  xc = getmaxx() / 2;
  yc = getmaxy() / 2;
  run();
  getch();
  closegraph();
}