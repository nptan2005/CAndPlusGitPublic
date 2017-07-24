/* Giai he phuong trinh tuyen tinh bang phuong phap khu GAUSS
voi B va X la ma tran N x P */
#include <stdio.h>
#include <math.h>

#define MAX 10
double A[MAX][MAX], B[MAX][MAX], X[MAX][MAX];

void gauss(int n, int p)
{
  int i=0, j, done=0, m, k;
  double max, c;
  printf("\nTinh nghiem cua he phuong trinh");
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
          max = fabs(A[k][i]); // Co sua
        }
      if (m != i)
      {
        for (j=i; j<n; j++)
        {
          c = A[i][j];
          A[i][j] = A[m][j];
          A[m][j] = c;
        }
        for (j=0; j<p; j++)
        {
          c = B[i][j];
          B[i][j] = B[m][j];
          B[m][j] = c;
        }
      }
      if (m == i)
        done = 1;
    }
    if (A[i][i] != 0)
    {
      c = 1/A[i][i];
      for (j=i; j<n; j++) // Co sua
        A[i][j] = A[i][j] * c;
      for (j=0; j<p; j++)
        B[i][j] = B[i][j] * c;
      for (k=i+1; k<n; k++)
      {
        for (j=i+1; j<n; j++) // Co sua
          A[k][j] = A[k][j] - A[i][j]*A[k][i];
        for (j=0; j<p; j++)
          B[k][j] = B[k][j] - B[i][j] * A[k][i];
        A[k][i] = 0;
      }
    }
    printf("\nLan khu hang %d", i);
    for (k=0; k<n; k++)
    {
      printf("\n");
      for (j=0; j<n; j++)
        printf("%10.5lf ", A[k][j]);
      printf(" = ");
      for (j=0; j<p; j++)
        printf("%10.5lf ", B[k][j]);
    }
    i++;
    if (i>=n)
      done = 1;
  }
  if (i >= n)
  {
    for (k=0; k<p; k++)
    {
      X[n-1][k] = B[n-1][k]/A[n-1][n-1];
      for (i=n-2; i>=0; i--)
      {
        X[i][k] = 0;
        for (j=n-1; j>i; j--)
          B[i][k] = B[i][k] - A[i][j] * X[j][k];
        X[i][k] = B[i][k]/A[i][j];
      }
    }
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

void in_B(int n, int p)
{
  int i, j;
  printf("\nMa tran B :");
  for (i=0; i<n; i++)
  {
    printf("\n");
    for (j=0; j<p; j++)
      printf("%10.5lf", B[i][j]);
  }
}

void in_X(int n, int p)
{
  int i, j;
  printf("\nMa tran X :");
  for (i=0; i<n; i++)
  {
    printf("\n");
    for (j=0; j<p; j++)
      printf("%10.5lf", X[i][j]);
  }
}

void main()
{
  int n, i, j, p;

  printf("Giai he phuong trinh tuyen tinh AX = B.");
  printf("\nbang phuong phap khu GAUSS.");
  printf("\nCho biet cap ma tran : ");
  scanf("%d%*c", &n);
  printf("\nCho biet bac cua B : ");
  scanf("%d%*c", &p);
  printf("\nNhap ma tran A :\n");
  for (i=0; i<n; i++)
  {
    for (j=0; j<n; j++)
    {
      printf("\nA[%d][%d] = ", i, j);
      scanf("%lf", &A[i][j]);
    }
  }
  printf("\nNhap ma tran B :\n");
  for (i=0; i<n; i++)
  {
    for (j=0; j<p; j++)
    {
      printf("\nB[%d][%d] = ", i, j);
      scanf("%lf", &B[i][j]);
    }
  }

  in_A(n);
  in_B(n, p);
  gauss(n, p);

  in_X(n, p);
  getch();
}
