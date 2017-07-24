/* Thiet lap ma tran chuyen vi */
#include <stdio.h>
#include <math.h>

#define MAX 10
double A[MAX][MAX], B[MAX][MAX];

void mt_cv(int n)
{
  int i, j;
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      B[i][j] = A[j][i];
}

void main()
{
  int n, i, j;

  printf("\nKiem tra xem mot tam giac co phai la doi xung hay khong?");
  printf("\nCho biet cap ma tran : ");
  scanf("%d%*c", &n);
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
    {
      printf("A[%d][%d] = ", i, j);
      scanf("%lf", &A[i][j]);
    }
  printf("\nMa tran A = ");
  for (i=0; i<n; i++)
  {
    printf("\n");
    for (j=0; j<n; j++)
      printf("%3.0lf", A[i][j]);
  }
  mt_cv(n);
  printf("\nMa tran chuyen vi cua no = ");
  for (i=0; i<n; i++)
  {
    printf("\n");
    for (j=0; j<n; j++)
      printf("%3.0lf", B[i][j]);
  }
  getch();
}
