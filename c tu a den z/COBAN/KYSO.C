/* Bai tap 2_4 - In chu so phan tram, chuc, don vi */
#include <stdio.h>

void main()
{
   int n, tram, chuc, donvi;

   printf("\nNhap vao mot so tu 100 - 999 : ");
   scanf("%d", &n);

   tram = n;
   donvi = tram % 10;
   tram /= 10;
   chuc = tram % 10;
   tram /= 10;

   printf("\nSo hang tram   = %d", tram);
   printf("\nSo hang chuc   = %d", chuc);
   printf("\nSo hang don vi = %d", donvi);

   getch();
}