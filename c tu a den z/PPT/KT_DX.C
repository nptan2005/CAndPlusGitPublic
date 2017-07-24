/* Kiem tra xem ma tran da cho co phai la doi xung hay khong */
#include <stdio.h>
#include <math.h>

#define MAX 10
float A[MAX][MAX];

int kt_dx(int n)
{
  int i, j;
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      if(A[i][j] != A[j][i])
        return 0;
  return 1;
}

void main()
{
  int n, i, j;

  printf("\nKiem tra xem mot tam giac co phai la doi xung hay khong?");
  printf("\nCho biet cap ma tran : ");
  scanf("%d%*c", &n);
  printf("\nNhap ma tran A :\n");
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
    {
      printf("\nA[%d][%d] = ", i, j);
      scanf("%f", &A[i][j]);
    }
  if (kt_dx(n))
    printf("Ma tran do la DOI XUNG");
  else
    printf("Ma tran do khong co DOI XUNG");

  getch();
}
