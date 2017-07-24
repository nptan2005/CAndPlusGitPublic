/* Kiem tra xem ma tran da cho co phai la tam giac duoi hay khong */
#include <stdio.h>
#include <math.h>

#define MAX 10
float A[MAX][MAX];

int kt_tgd(int n)
{
  int i, j;
  for (i=0; i<n; i++)
    for (j=i+1; j<n; j++)
      if(A[i][j] != 0)
        return 0;
  return 1;
}

void main()
{
  int n, i, j;

  printf("\nKiem tra xem mot tam giac co phai la tam giac duoi hay khong?");
  printf("\nCho biet cap ma tran : ");
  scanf("%d%*c", &n);
  printf("\nNhap ma tran A :\n");
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
    {
      printf("\nA[%d][%d] = ", i, j);
      scanf("%f", &A[i][j]);
    }
  if (kt_tgd(n))
    printf("Ma tran do la TAM GIAC DUOI");
  else
    printf("Ma tran do khong phai la TAM GIAC DUOI");

  getch();
}
