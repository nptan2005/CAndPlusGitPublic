/* Giai he phuong trinh tuyen tinh bang phep khu GAUSS - JORDAN
void B va X la ma tran N x 1 */
#include <stdio.h>
#include <math.h>

#define MAX 10
double A[MAX][MAX], B[MAX], X[MAX];

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
        c = B[i];
        B[i] = B[m];
        B[m] = c;
      }
      if (m == i)
        done = 1;
    }
    if (A[i][i] != 0)
    {
      c = 1/A[i][i];
      for (j=i; j<n; j++)
        A[i][j] = A[i][j] * c;
      B[i] = B[i] * c;
      for (k=0; k<n; k++)
        if (k != i)
        {
          c= A[k][i];
          for (j=i; j<n; j++)
            A[k][j] = A[k][j] - A[i][j]*c;
          B[k] = B[k] - B[i] * c;
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
    for (j=0; j<n; j++)
      X[j] = B[j];
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
    printf("%10.5lf", B[i]);
  }
}

void in_X(int n)
{
  int i, j;
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
    for (j=0; j<n; j++)
    {
      printf("A[%d][%d] = ", i, j);
      scanf("%lf", &A[i][j]);
    }
  printf("\nNhap ma tran B :\n");
  for (i=0; i<n; i++)
  {
    printf("B[%d] = ", i);
    scanf("%lf", &B[i]);
  }
  in_A(n);
  in_B(n);
  gauss_jordan(n);

  in_X(n);
  getch();
}
