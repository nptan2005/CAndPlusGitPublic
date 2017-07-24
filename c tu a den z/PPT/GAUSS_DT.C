/* Tinh dinh thuc ma tran bang phuong phap GAUSS */
#include <stdio.h>
#include <math.h>

#define MAX 10
double A[MAX][MAX];

void gauss_dt(int n)
{
  int i=0, j, done=0, m, k;
  double max, c, d=1;
  printf("\nTinh Dinh thuc cua ma tran : ");
  while (!done)
  {
    if (A[i][i] == 0)
    {
      max = 0;
      m = i;
      for (k=i+1; k<n; k++)
        if (max < fabs(A[k][i]))
        {
          m = k;
          max = fabs(A[k][i]);
        }
      if (m != i)
      {
        d = -d;
        for (j=i+1; j<n; j++)
        {
          c = A[i][j];
          A[i][j] = A[m][j];
          A[m][j] = c;
        }
      }
      if (m == i)
      {
        done = 1;
        printf("\nMa tran suy bien!");
        d = 0;
      }
    }
    if (A[i][i] != 0)
    {
      c = 1/A[i][i];
      for (j=i+1; j<n; j++)
        A[i][j] = A[i][j] * c;
      for (k=i+1; k<n; k++)
      {
        for (j=i+1; j<n; j++)
          A[k][j] = A[k][j] - A[i][j]*A[k][i];
      }
    }
    printf("\nLam khu hang %d", i);
    for (k=0; k<n; k++)
    {
      printf("\n");
      for (j=0; j<n; j++)
        printf("%10.5lf", A[k][j]);
    }
    i++;
    if (i>=n)
      done = 1;
  }
  if (i >= n)
  {
    for (i=0; i<n; i++)
      d = d * A[i][i];
    printf("\nDinh thuc cua ma tran = %lf", d);
  }
}

void in_A(int n)
{
  int i, j;
  printf("\nMa tran A :");
  for (i=0; i<n; i++)
  {
    printf("\n");
    for (j=0; j<n; j++)
      printf("%10.5lf", A[i][j]);
  }
}

void main()
{
  int n, i, j;

  printf("Tinh dinh thuc ma tran vuong cap N");
  printf("\nbang phuong phap khu GAUSS.");
  printf("\nCho biet cap ma tran : ");
  scanf("%d%*c", &n);
  printf("\nNhap ma tran A :\n");
  for (i=0; i<n; i++)
  {
    for (j=0; j<n; j++)
    {
      printf("\nA[%d][%d] = ", i, j);
      scanf("%lf", &A[i][j]);
    }
  }
  in_A(n);

  gauss_dt(n);

  getch();
}
