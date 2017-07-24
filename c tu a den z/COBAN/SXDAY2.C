/* Nhap co sap xep */
#include <stdio.h>
#include <mem.h>

#define MAX 100

void main()
{
  int day[MAX], n, i, j, tam;

  printf("\nCho biet so phan tu cua day : ");
  scanf("%d", &n);
  printf("Nhap vao cac phan tu : ");
  for (i=0; i<n; i++)
  {
    scanf("%d", &tam);
    j = 0;
    while (j<i && day[j]<tam)
      j++;
    if (j<i)
      memmove(&day[j+1], &day[j], (i-j)*sizeof(int));
    day[j] = tam;
  }
  printf("\nSau khi nhap : ");
  for (i=0; i<n; i++)
    printf("%d ", day[i]);
  getch();
}