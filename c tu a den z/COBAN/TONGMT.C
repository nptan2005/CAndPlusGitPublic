/* Tinh tong ma tran */
#include <stdio.h>

#define MAX 10

void in_ma_tran(int A[MAX][MAX], int n, int m, char id)
{
  int i, j;

  printf("\nMa tran %c : ", id);
  for (i=0; i<n; i++)
  {
    printf("\n");
    for(j=0; j<m; j++)
      printf("%3d ",A[i][j]);
  }
}

void nhap_so_nguyen(int *value, int min, int max, char id)
{
  do {
    printf("\nNhap gia tri %c (trong khoang %d den %d)", id, min, max);
    scanf("%d", value);
  } while (*value < min || *value > max);
}

void main()
{
  int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX], n, m, i, j;

  nhap_so_nguyen(&n, 2, MAX, 'n');
  nhap_so_nguyen(&m, 2, MAX, 'm');
  printf("\nNhap ma tran A : ");
  for (i=0; i<n; i++)
    for (j=0; j<m; j++)
    {
      printf("A[%d,%d] = ");
      scanf("%d", &(A[i][j]));
    }
  printf("\nNhap ma tran B : ");
  for (i=0; i<n; i++)
    for (j=0; j<m; j++)
    {
      printf("B[%d,%d] = ");
      scanf("%d", &(B[i][j]));
    }
  in_ma_tran(A, n, m, 'A');
  in_ma_tran(B, n, m, 'B');
  for (i=0; i<n; i++)
    for (j=0; j<m; j++)
      C[i][j] = A[i][j] + B[i][j];
  in_ma_tran(C, n, m, 'C');
  getch();
}