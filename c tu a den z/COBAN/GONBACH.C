/* Bai tap  - Bai toan Gonbach */
#include <stdio.h>

#define MAX 100

void main()
{
  unsigned long nguyento[MAX], i, j, l, k=0, n;

  for (i=1; i<MAX; i++)
    if (i%2 == 1)
    {
      for (j=2; j<i; j++)
        if (i%j == 0)
          break;
      if (j >= i)
        nguyento[k++] = i;
    }
  for (n=0; n<k; n++)
    for (i=0; i<k; i++)
      for (j=0; j<k; j++)
        for (l=0; l<k; l++)
          if (nguyento[i] + nguyento[j] + nguyento[l] == nguyento[n])
            printf("\n%ld = %ld + %ld + %ld", nguyento[n], nguyento[i],
                   nguyento[j], nguyento[l]);

  getch();
}