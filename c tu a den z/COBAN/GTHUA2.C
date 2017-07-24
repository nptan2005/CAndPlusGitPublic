/* Bai tap 1_20 - Tinh n!! */
#include <stdio.h>

void main()
{
  int n, start, i;
  unsigned long gthua = 1;

  printf("\nNhap gia tri N : ");
  scanf("%d", &n);
  if (n%2 == 0)
    start = 2;
  else
    start = 1;
  for (i=start; i<=n; i = i+2)
    gthua *= i;
  printf("\n%d!! = %ld", n, gthua);
  getch();
}