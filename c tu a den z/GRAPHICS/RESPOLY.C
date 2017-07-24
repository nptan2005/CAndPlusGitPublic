#include <stdio.h>
#include <dos.h>
#include <graphics.h>

#define MAX 100

void main()
{
  int gr_drive = DETECT, gr_mode;
  int n = 0, i, k;
  struct pointtype pt[MAX];
  char filename[] = "POLY.DAT";
  FILE *fp;

  initgraph(&gr_drive, &gr_mode, "");
  if ((fp = fopen(filename, "rb")) == NULL)
    printf("\nKhong the mo tap tin %s.", filename);
  else
  {
    fread(&n, sizeof(int), 1, fp);
    fread(pt, sizeof(struct pointtype), n, fp);
    fclose(fp);
    printf("\nCong viec hoan tat.");
  }
  circle(pt[0].x, pt[0].y, 3);
  moveto(pt[0].x, pt[0].y);
  for (i=1; i<n; i++)
    lineto(pt[i].x, pt[i].y);
  lineto(pt[0].x, pt[0].y);
  getch();
  closegraph();
}