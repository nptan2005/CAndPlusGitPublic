/* Bai tap 2_3 - Tinh tong binh phuong hai so nguyen */
#include <stdio.h>

void main()
{
  int a, b;

  printf("\nNhap hai so nguyen : ");
  scanf("%d%d", &a, &b);

  printf("Tong %dý + %dý = %d", a, b, a * a + b * b);
  getch();
}