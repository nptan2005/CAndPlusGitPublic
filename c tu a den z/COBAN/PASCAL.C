#include <stdio.h>
#include <conio.h>
#define N 15

void main()
{
  int i, j, tgpascal[N], tmp[N];

  clrscr();
  tgpascal[0] = 1;
  for (i=1; i<N; i++)
    tgpascal[i] = 0;
  for (i=0; i<N; i++)
  {
     for (j=0; j<=i; j++)
       tmp[j] = tgpascal[j];
     printf("\n%5d", tmp[0]);
     for (j=1; j<=i; j++)
     {
       tmp[j] += tgpascal[j-1];
       printf("%5d", tmp[j]);
     }
     for (j=0; j<=i; j++)
       tgpascal[j] = tmp[j];
  }
  getch();
}