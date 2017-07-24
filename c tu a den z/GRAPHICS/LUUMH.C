/* Luu man hinh do hoa vao 1 file */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <alloc.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <io.h>
#include <dos.h>

char filename[] = "graph.dat";

void main()
{
  int gr_drive = DETECT, gr_mode, i, j, k, l, r, m, maxx, maxy;
  int filehandle, bytes;
  void far *buffer;

  initgraph(&gr_drive, &gr_mode, "");
  randomize();
  maxx = getmaxx();
  maxy = getmaxy();
  for (m=0; m<10; m++)
  {
    i = random(maxx);
    j = random(maxy);
    k = random(maxx);
    l = random(maxy);
    r = random(15) + 1;
    setcolor(r);
    rectangle(i, j, k, l);
  }

  for (m=0; m<10; m++)
  {
    i = random(maxx);
    j = random(maxy);
    l = random(maxy / 10);
    r = random(15) + 1;
    k = random(15) + 1;
    setcolor(r);
    setfillstyle(SOLID_FILL, k);
    fillellipse(i, j, l, l);
  }
  if (_dos_open(filename,O_CREAT | O_BINARY, &filehandle) != 0)
  {
    k = (maxx+1) / 10;
    l = (maxy+1) / 10;
    m = imagesize(0, 0, k-1, l-1);
    if ((buffer = farmalloc(m)) == NULL)
    {
      closegraph();
      printf("\nKhong du bo nho");
      exit(1);
    }
    _dos_write(filehandle, &m, sizeof (int), &bytes);
    _dos_write(filehandle, &k, sizeof (int), &bytes);
    _dos_write(filehandle, &l, sizeof (int), &bytes);
    for (i=0; i<10; i++)
    {
      getimage(i*k, i*l, (i+1)*k-1, (i+1)*l-1, buffer);
      _dos_write(filehandle, buffer, m, &bytes);
    }
    farfree(buffer);
    _dos_close(filehandle);
  }
  getch();
  closegraph();
}