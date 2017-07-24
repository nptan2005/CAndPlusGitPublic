/* Tim so nguyen to nho hon N */
#include <stdio.h>

void main()
{
  int n, i, j;

  printf("\nNhap gia tri N : ");
  scanf("%d", &n);
  printf("\nCac so nguyen to nho hon n la : ");
  for (i=2; i<n; i++)
  {
    for (j=2; j<i; j++)
      if (i%j == 0)
        break;
    if (j == i)
      printf("%d ", i);
  }

  getch();
}