/* Thiet lap ma tran don vi cap N */
#include <stdio.h>
#include <math.h>

#define MAX 10
float A[MAX][MAX];

void mt_dv(int n)
{
  int i, j;
  for (i=0; i<n; i++)
    for (j=0; j<=i; j++)
      if (i != j)
        A[i][j] = 0;
      else
        A[i][j] = 1;
}

void main()
{
  int n, i, j;

  printf("\nKiem tra xem mot tam giac co phai la doi xung hay khong?");
  printf("\nCho biet cap ma tran : ");
  scanf("%d%*c", &n);
  mt_dv(n);
  for (i=0; i<n; i++)
  {
    printf("\n");
    for (j=0; j<n; j++)
      printf("%3.0lf", A[i][j]);
  }
  getch();
}
