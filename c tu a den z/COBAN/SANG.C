/* Giai thuat sang Erastosthene */
#include <stdio.h>

void main()
{
  static int NT[1000], i, k;

  printf("\nCac so nguyen to nho hon 1000 :\n");
  for (i=2; i<1000; i++)
    if (NT[i] == 0)
    {
      k = 1;
      while (k*i<1000)
        NT[i*k++] = 1;
      printf("%4d ", i);
    }
  getch();
}