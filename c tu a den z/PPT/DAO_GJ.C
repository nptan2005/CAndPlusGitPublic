/* Tinh ma tran dao bang phep khu GAUSS - JORDAN */
#include <stdio.h>
#include <math.h>

#define MAX 10
double A[MAX][MAX], B[MAX][MAX], X[MAX][MAX];

void gauss_jordan(int n)
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
          max = fabs(A[k][i]);
        }
      if (m != i)
      {
        for (j=i; j<n; j++)
        {
          c = A[i][j];
          A[i][j] = A[m][j];
          A[m][j] = c;
        }
        for (j=0; j<n; j++)
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
      for (j=i; j<n; j++)
        A[i][j] = A[i][j] * c;
      for (j=0; j<n; j++)
        B[i][j] = B[i][j] * c;
      for (k=0; k<n; k++)
        if (k != i)
        {
          c= A[k][i];
          for (j=i; j<n; j++)
            A[k][j] = A[k][j] - A[i][j]*c;
          for (j=0; j<n; j++)
            B[k][j] = B[k][j] - B[i][j] * c;
        }
    }
    printf("\nLan khu hang %d", i);
    for (k=0; k<n; k++)
    {
      printf("\n");
      for (j=0; j<n; j++)
        printf("%10.5lf", A[k][j]);
      for (j=0; j<n; j++)
        printf(" = %10.5lf", B[k][j]);
    }
    i++;
    if (i>=n)
      done = 1;
  }
  if (i >= n)
    for (j=0; j<n; j++)
      for (k=0; k<n; k++)
        X[j][k] = B[j][k];
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

void in_B(int n)
{
  int i, j;
  printf("\nMa tran B :\n");
  for (i=0; i<n; i++)
  {
    printf("\n");
    for (j=0; j<n; j++)
      printf("%10.5lf", B[i][j]);
  }
}

void in_X(int n)
{
  int i, j;
  printf("\nMa tran dao :\n");
  for (i=0; i<n; i++)
  {
    printf("\n");
    for (j=0; j<n; j++)
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
  printf("\nNhap ma tran A :\n");
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
    {
      printf("A[%d][%d] = ", i, j);
      scanf("%lf", &A[i][j]);
    }
  printf("\nMa tran B la ma tran don vi :\n");
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      if (i==j)
        B[i][j]= 1;
      else
        B[i][j]= 0;
  in_A(n);
  in_B(n);
  gauss_jordan(n);

  in_X(n);
  getch();
}
