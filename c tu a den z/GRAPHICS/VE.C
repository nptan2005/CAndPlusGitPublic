/* Bai tap 2_15 - Ve bang cac phim mui ten */
#include <graphics.h>

void main()
{
  int gr_drive = DETECT, gr_mode;
  int x, y, maxx, maxy;
  char c;

  initgraph(&gr_drive, &gr_mode, "");
  maxx = getmaxx();
  maxy = getmaxy();
  x = maxx / 2;
  y = maxy / 2;
  putpixel(x, y, YELLOW);
  do {
    c = getch();
    if (c == 0)
    {
      c = getch();
      switch(c)
      {
        case 75 : if (x > 0)
                    putpixel(--x, y, YELLOW);
                  break;
        case 77 : if (x < maxx-1)
                    putpixel(++x, y, YELLOW);
                  break;
        case 72 : if (y > 0)
                    putpixel(x, --y, YELLOW);
                  break;
        case 80 : if (y < maxy-1)
                    putpixel(x, ++y, YELLOW);
                  break;
      }
    }
  } while (c != 27);

  closegraph();
}