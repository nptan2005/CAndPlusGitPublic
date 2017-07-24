/* Tinh ma tran dao bang phuong phap CHOLESKY */
#include <stdio.h>
#include <math.h>

#define MAX 10
double A[MAX][MAX], B[MAX][MAX], X[MAX][MAX];

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
  printf("\nMa tran nghiem X :\n");
  for (i=0; i<n; i++)
  {
    printf("\n");
    for (j=0; j<n; j++)
      printf("%10.5lf", X[i][j]);
  }
}

void cholesky(int n)
{
  int i=0, j, done=0, m, k;
  double max, c;
  printf("\nTinh nghiem cua he phuong trinh");
  for (i=0; i<n; i++)
  {
    if (A[i][i] <= 0)
    {
      done = 1;
      printf("\nKhong the tinh duoc vi co phan tu tren duong cheo chinh < 0.");
    }
    if (A[i][i] > 0)
    {
      c = 0;
      for (j=0; j<i; j++)
        c += A[i][j] * A[i][j];
      A[i][i] = sqrt(A[i][i]-c);
      for (j=i+1; j<n; j++)
      {
        c = 0;
        for (k=0; k<i; k++)
          c += A[i][k]*A[j][k];
        A[i][j] = A[j][i] = (A[i][j]-c) / A[i][i];
      }

    }
  }
  while (!done)
  {
    printf("\nMa tran L : ");
    for (i=0; i<n; i++)
    {
      printf("\n");
      for (j=0; j<=i; j++)
        printf("%7.3lf", A[i][j]);
    }
    printf("\nTinh nghiem Y = LB\n");
    for (k=0; k<n; k++)
    {
      X[0][k] = B[0][k]/A[0][0];
      for (i=1; i<n; i++)
      {
        X[i][k] = 0;
        for (j=0; j<i; j++)
          B[i][k] = B[i][k] - A[i][j] * X[j][k];
        X[i][k] = B[i][k]/A[i][j];
      }
    }
    printf("\nNghiem trung gian :\n");
    for (k=0; k<n; k++)
      for (i=0; i<n; i++)
      {
        B[i][k] = X[i][k];
      }
    in_B(n);
    printf("\nTinh nghiem X = UY\n");
    for (k=0; k<n; k++)
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
    done = 1;
  }
}

void main()
{
  int n, i, j, p;

  printf("Giai he phuong trinh tuyen tinh AX = B.");
  printf("\nbang phuong phap CHOLESKY.");
  printf("\nCho biet cap ma tran : ");
  scanf("%d%*c", &n);
  printf("\nNhap phan ma tran duoi cua A :\n");
  for (i=0; i<n; i++)
    for (j=0; j<=i; j++)
    {
      printf("A[%d][%d] = A[%d][%d] = ", i, j, j, i);
      scanf("%lf", &A[i][j]);
      A[j][i] = A[i][j];
    }
  printf("\nThiet lap ma tran B :\n");
  for (i=0; i<n; i++)
    for (j=0; j<=i; j++)
      if (i != j)
        B[i][j] = 0;
      else
        B[i][j] = 1;

  in_A(n);
  in_B(n);
  cholesky(n);

  printf("\nMa tran dao cua A :\n");
  in_X(n);
  getch();
}
