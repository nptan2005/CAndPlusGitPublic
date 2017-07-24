/* Bai tap 1_21 - In day so Fibonanci */
#include <stdio.h>

void main()
{
  int n, i, fib1 = 1, fib2 = 1, fib = 2;

  printf("\nNhap gia tri N : ");
  scanf("%d", &n);
  printf("%d %d ", fib1, fib2);
  while (fib1+fib2 < n)
  {
    fib = fib1 + fib2;
    printf("%d ", fib);
    fib2 = fib1;
    fib1 = fib;
  }
  getch();
}