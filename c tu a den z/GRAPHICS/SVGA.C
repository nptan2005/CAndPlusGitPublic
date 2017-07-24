/* SVGA */
#include <conio.h>
#include <graphics.h>
#include <math.h>

/* 1 / sqrt(2) */
#define FCT 0.7071067
/* he so doi tu do sang radian */
#define RADS 0.017453293

int huge detectVGA(void)
{
   int driver, mode, sugmode = 0;

   detectgraph(&driver, &mode);
   if (driver == VGA)
      return sugmode;
   else
      return grError;
}

void main()
{
  int gr_drive, gr_mode, i;

  gr_drive = installuserdriver("svga256", detectVGA);
  gr_mode  = 2; /* 640 x 480 - 256 color */
  initgraph(&gr_drive, &gr_mode, "");

  for (i=0; i<480; i++)
  {
    setcolor(i);
    line(0, i, 639,  i);
  }
  printf("%d", getmaxx()+1);
  printf("\n%d", getmaxy()+1);
  getch();
  closegraph();
}
