/* Bai tap 1_29 - Tinh so PI voi sai so 0.0001 */
#include <stdio.h>
#include <math.h>

void main()
{
  double PI = 1.0, n = 3.0;
  int i = 0;

  while (1.0/n > 0.0001)
  {
    if (i%2 == 0)
      PI -= 1.0/n;
    else
      PI += 1.0/n;
    n += 2;
    i++;
  }
  PI *= 4.0;
  printf("\nSo PI tinh toan duoc la : %lf", PI);
  printf("\nSo M_PI trong C         = %lf", M_PI);
  getch();
}