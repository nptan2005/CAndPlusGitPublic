/* Bai tap 1_93 - In tat ca cac uoc so cua so n */
#include <stdio.h>
#include <conio.h>

void main()
{
  int n, i;

  printf("Cho gia tri N = ");
  scanf("%d", &n);

  printf("Cac uoc so cua %d la :\n", n);
  for (i=1; i<n; i++)
    if ((n % i) == 0)
      printf("%5d", i);
  getch();
}