/* Giai he phuong trinh tuyen tinh voi cac he so la ma tran tam giac tren */
#include <stdio.h>
#include <math.h>

#define MAX 10
double A[MAX][MAX], B[MAX], X[MAX];

void tg_tren(int n)
{
  int i, j;

  printf("\nTinh nghiem cua he phuong trinh");
  X[n-1] = B[n-1]/A[n-1][n-1];
  for (i=n-2; i>=0; i--)
  {
    X[i] = 0;
    for (j=n-1; j>i; j--)
      B[i] = B[i] - A[i][j] * X[j];
    X[i] = B[i]/A[i][j];
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

void in_B(int n)
{
  int i;
  printf("\nMa tran B :\n");
  for (i=0; i<n; i++)
    printf("%10.5lf", B[i]);
}

void in_X(int n)
{
  int i;
  printf("\nMa tran nghiem X :\n");
  for (i=0; i<n; i++)
    printf("%10.5lf", X[i]);
}

void main()
{
  int n, i, j;

  printf("Giai he phuong trinh tuyen tinh AX = B.");
  printf("\nvoi A la ma tran tam giac tren.");
  printf("\nCho biet cap ma tran : ");
  scanf("%d%*c", &n);
  printf("\nNhap ma tran A :\n");
  for (i=0; i<n; i++)
  {
    for (j=i; j<n; j++)
    {
      printf("\nA[%d][%d] = ", i, j);
      scanf("%lf", &A[i][j]);
    }
    for (j=0; j<i; j++)
      A[i][j] = 0;
  }
  printf("\nNhap ma tran B :\n");
  for (i=0; i<n; i++)
  {
    printf("\nB[%d] = ", i);
    scanf("%lf", &B[i]);
  }
  in_A(n);
  in_B(n);
  tg_tren(n);

  in_X(n);
  getch();
}
