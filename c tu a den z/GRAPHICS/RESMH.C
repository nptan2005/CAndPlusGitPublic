/* Lay man hinh do hoa tu 1 file */
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
  if (_dos_open(filename,O_RDONLY | O_BINARY, &filehandle) != 0)
  {
    _dos_read(filehandle, &m, sizeof (int), &bytes);
    _dos_read(filehandle, &k, sizeof (int), &bytes);
    _dos_read(filehandle, &l, sizeof (int), &bytes);
    if ((buffer = farmalloc(m)) == NULL)
    {
      closegraph();
      printf("\nKhong du bo nho");
      exit(1);
    }
    for (i=0; i<10; i++)
    {
      _dos_read(filehandle, buffer, m, &bytes);
      putimage(i*k, i*l, buffer, COPY_PUT);
    }
    _dos_close(filehandle);
    farfree(buffer);
  }
  getch();
  closegraph();
}