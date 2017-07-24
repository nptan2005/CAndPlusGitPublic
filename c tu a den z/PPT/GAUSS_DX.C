/* Giai he phuong trinh tuyen tinh voi cac he so la ma tran doi xung
   bang phuong phap GAUSS */
#include <stdio.h>
#include <math.h>

#define MAX 10
double A[MAX][MAX], B[MAX], X[MAX];

void gauss_dx(int n)
{
  int i=0, j, done=0, m, k;
  double max, c;
  printf("\nTinh nghiem cua he phuong trinh");
  while (!done)
  {
    if (A[i][i] == 0)
    {
      done = 1;
      printf("\nCo phan tu tren duong cheo chinh bang 0");
    }
    if (A[i][i] != 0)
    {
// Con dang lam dang do
      c = 1/A[i][i];
      for (j=i; j<n; j++) // Co sua
        A[i][j] = A[i][j] * c;
      B[i] = B[i] * c;
      for (k=i+1; k<n; k++)
      {
        for (j=i+1; j<n; j++) // Co sua
          A[k][j] = A[k][j] - A[i][j]*A[k][i];
        B[k] = B[k] - B[i] * A[k][i];
        A[k][i] = 0;
      }
    }
    printf("\nLan khu hang %d", i);
    for (k=0; k<n; k++)
    {
      printf("\n");
      for (j=0; j<n; j++)
        printf("%10.5lf", A[k][j]);
      printf(" = %10.5lf", B[k]);
    }
    i++;
    if (i>=n)
      done = 1;
  }
  if (i >= n)
  {
   X[n-1] = B[n-1]/A[n-1][n-1];
   for (i=n-2; i>=0; i--)
   {
     X[i] = 0;
     for (j=n-1; j>i; j--)
       B[i] = B[i] - A[i][j] * X[j];
     X[i] = B[i]/A[i][j];
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
  printf("\nbang phuong phap khu GAUSS.");
  printf("\nCho biet cap ma tran : ");
  scanf("%d%*c", &n);
  printf("\nNhap ma tran A :\n");
  for (i=0; i<n; i++)
  {
    for (j=0; j<n; j++)
    {
      printf("A[%d][%d] = ", i, j);
      scanf("%lf", &A[i][j]);
    }
  }
  printf("\nNhap ma tran B :\n");
  for (i=0; i<n; i++)
  {
    printf("B[%d] = ", i);
    scanf("%lf", &B[i]);
  }
  in_A(n);
  in_B(n);
  gauss_dx(n);

  in_X(n);
  getch();
}
