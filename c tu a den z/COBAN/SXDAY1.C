#include <stdio.h>

#define MAX 100

void main()
{
  int day[MAX], i, n, j, tam;

  printf("\nCho biet so phan tu cua day : ");
  scanf("%d", &n);
  printf("Nhap vao cac phan tu : ");
  for (i=0; i<n; i++)
    scanf("%d", &day[i]);
  for (i=0; i<n-1; i++)
    for (j=i+1; j<n; j++)
      if (day[j] < day[i])
      {
        tam = day[i];
        day[i] = day[j];
        day[j] = tam;
      }
  printf("\nSau khi sap xep : ");
  for (i=0; i<n; i++)
    printf("%d ", day[i]);
  getch();
}