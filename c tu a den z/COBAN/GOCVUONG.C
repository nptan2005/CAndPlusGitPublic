/* Bai tap 2_6 - Cho biet goc thuoc goc vuong nao */
#include <stdio.h>

void main()
{
  int goc;

  printf("\nNhap vao gia tri goc : ");
  scanf("%d", &goc);

  printf("Goc do thuoc goc vuong thu %d", (goc/90)%4 + 1);
  getch();
}