/* Bai tap 1_92 - In hinh tam giac dac */
#include <stdio.h>
#include <conio.h>

void main()
{
  int n, i, j;

  printf("\nNhap chieu cao cua hinh tam giac : ");
  scanf("%d", &n);

  for (i=0; i<n; i++)
  {
    for (j=n-1; j>i; j--)
      printf(" ");
    for (j=0; j<i*2+1; j++)
      printf("*");
    printf("\n");
  }

  getch();
}