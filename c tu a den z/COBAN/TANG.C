#include <stdio.h>

void main()
{
  int a[10], i;

  printf("\nNhap vao 10 phan tu nguyen cua day : ");
  for (i=0; i<10; i++)
   scanf("%d", &a[i]);
  i = 1;
  while (a[i] >= a[i-1] && i<10)
    i++;
  if (i==10)
    printf("Day da cho la day tang");
  else
    printf("Day da cho khong la day tang");
  getch();
}