/* Tron hai mang tang dan thanh 1 mang tang dan */
#include <stdio.h>

#define MAX 10

void main()
{
  int a[MAX], b[MAX], c[2*MAX], n1, n2, i, i1, i2;

  printf("\nCho biet so phan tu cua mang thu nhat : ");
  scanf("%d", &n1);
  printf("Nhap vao cac phan tu (tang dan) cua mang thu nhat : ");
  for (i=0; i<n1; i++)
    scanf("%d", &a[i]);
  printf("\nCho biet so phan tu cua mang thu hai : ");
  scanf("%d", &n2);
  printf("Nhap vao cac phan tu (tang dan) cua mang thu hai : ");
  for (i=0; i<n2; i++)
    scanf("%d", &b[i]);
  i1 = i2 = 0;
  for (i=0; i<n1 + n2; i++)
  {
    if (i1 >= n1 || i2 >= n2)
      break;
    if (a[i1] < b[i2])
      {
        c[i] = a[i1];
        i1++;
      }
      else
      {
        c[i] = b[i2];
        i2++;
      }
  }
  if (i1 < n1)
    while (i1 < n1)
      c[i++] = a[i1++];
  if (i2 < n2)
    while (i2 < n2)
      c[i++] = b[i2++];
  printf("\nCac phan tu cua mang tron : ");
  for (i=0; i<n1+n2; i++)
    printf("%d ", c[i]);
  getch();
}