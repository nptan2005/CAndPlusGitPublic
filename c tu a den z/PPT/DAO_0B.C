/* Tim ma tran dao bang phep khu GAUSS - JORDAN khong dung ma tran phu B */
#include <stdio.h>
#include <math.h>

#define MAX 10
double A[MAX][MAX];

void in_A(int n)
{
  int i, j;
  printf("\nMa tran A :");
  for (i=0; i<n; i++)
  {
    printf("\n");
    for (j=0; j<n; j++)
      printf("%7.3lf", A[i][j]);
  }
}

void gauss_jordan(int n)
{
  int i=0, j, done=0, m, k;
  double max, c, b;
  printf("\nTinh dinh thuc cua ma tran A");
  while (!done)
  {
    if (A[i][i] == 0)
    {
      done = 1;
      printf("\nKhong dung phuong phap nay duoc!.");
    }
    if (A[i][i] != 0)
    {
      c = 1/A[i][i];
      for (j=0; j<n; j++)
        A[i][j] = A[i][j] * c;
      A[i][i] = c;
      for (k=0; k<n; k++)
        if (k != i)
        {
          b= A[k][i];
          for (j=0; j<n; j++)
            if (i == j)
              A[k][j] = - b*c;
            else
              A[k][j] = A[k][j] - A[i][j]*b;
        }
    }
    i++;
    if (i>=n)
      done = 1;
  }
  if (i>=n)
    in_A(n);
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
  in_A(n);
  gauss_jordan(n);

  getch();
}
