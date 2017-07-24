#include <stdio.h>

void main()
{
  int n, a[100], i, x;

  printf("\nNhap vao so luong phan tu cua mang : ");
  scanf("%d", &n);
  printf("Nhap vao cac phan tu cua mang : ");
  for (i=0; i<n; i++)
    scanf("%d", &a[i]);
  printf("\nNhap vao gia tri x : ");
  scanf("%d", &x);
  printf("\nCac phan tu lon hon %d gom co : ", x);
  printf("\nChi so    Gia tri");
  for (i=0; i<n; i++)
    if (a[i] > x)
      printf("\n%4d       %6d", i, a[i]);

  getch();
}