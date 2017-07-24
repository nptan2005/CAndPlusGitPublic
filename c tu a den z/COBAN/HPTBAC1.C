/* Giai he phuong trinh bac nhat */
#include <stdio.h>

void main()
{
  int a, b, c, d, e, f, dthuc;
  float x, y;

  printf("\nNhap vao cac he so a,b,c,d,e,f : ");
  scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
  dthuc = b*d - e*a;
  if (dthuc != 0)
  {
    y = (float)(c*d-a*f)/dthuc;
    x = (float)(b*f-c*e)/dthuc;
    printf("Nghiem x = %f, y = %f", x, y);
  }
  else
    printf("\nHe phuong trinh vo ngiem.");

  getch();
}