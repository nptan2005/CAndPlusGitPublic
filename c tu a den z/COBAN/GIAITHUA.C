/* Bai tap 3_1 - Ham tinh N! */
#include <stdio.h>

unsigned long giaithua(int n)
{
   unsigned long ketqua = 1;
   int i;

   for (i=2; i<=n; i++)
     ketqua *= i;

   return ketqua;
}

void main()
{
  int n;

  printf("\nNhap vao gia tri N : ");
  scanf("%d", &n);

  printf("%d! = %lu", n, giaithua(n));
  getch();
}