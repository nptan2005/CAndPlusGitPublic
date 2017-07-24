/* Bai tap 1_16 - Tinh xem so N co phai la so nguyen to khong? */
#include <stdio.h>
#include <math.h>

void main()
{
  int N, i, OK = 1;

  printf("\nNhap gia tri N : ");
  scanf("%d", &N);
  for (i=2; i<(int)sqrt(N); i++)
    if (N%i == 0)
    {
      OK = 0;
      break;
    }
  if (OK)
   printf("\nSo %d la so nguyen to.", N);
  else
   printf("\nSo %d khong phai la so nguyen to.", N);
  getch();
}