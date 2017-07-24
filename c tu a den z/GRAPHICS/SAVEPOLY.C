#include <stdio.h>
#include <dos.h>
#include <graphics.h>
#include "mouse.inc"

#define MAX 100

void main()
{
  int gr_drive = DETECT, gr_mode;
  int x, y, n=0;
  unsigned char lbutton, rbutton = 0;
  struct pointtype pt[MAX];
  char filename[] = "POLY.DAT";
  FILE *fp;

  initgraph(&gr_drive, &gr_mode, "");
  rectangle(0, 0, getmaxx(), getmaxy());
  printf("\nNhan nut trai de them dinh. \nNhan nut phai de cham dut.");
  reset_mouse();
  while (n<MAX && rbutton == 0)
  {
    while (lbutton == 1 || rbutton == 1)
      get_mouse_button(&lbutton, &rbutton, &x, &y);
    show_mouse();
    do {
      get_mouse_button(&lbutton, &rbutton, &x, &y);
    } while (lbutton == 0 && rbutton == 0);
    hide_mouse();
    if (lbutton == 1)
    {
      pt[n].x = x;
      pt[n].y = y;
      if (n == 0)
      {
        circle(x, y, 3);
        moveto(x, y);
      }
      else
        lineto(x, y);
      n++;
    }
  }
  lineto(pt[0].x, pt[0].y);
  if ((fp = fopen(filename, "w+b")) == NULL)
    printf("\nKhong the tao tap tin %s.", filename);
  else
  {
    fwrite(&n, sizeof(int), 1, fp);
    fwrite(&pt, sizeof(struct pointtype), n, fp);
    fclose(fp);
    printf("\nCong viec hoan tat.");
  }
  getch();
  closegraph();
  while (lbutton == 1 || rbutton == 1)
    get_mouse_button(&lbutton, &rbutton, &x, &y);
}