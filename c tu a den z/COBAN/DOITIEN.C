/* Bai tap 5_3 - Tim phuong an doi tien */
#include <stdio.h>

#define TONGSOTIEN 300000
void main()
{
   long i, j, k, l, m, count=0, soluong = 0;

   for (i=0; i<=TONGSOTIEN/1000; i++)
     for (j=0; j<=TONGSOTIEN/2000; j++)
       for (k=0; k<=TONGSOTIEN/5000; k++)
         for (l=0; l<=TONGSOTIEN/10000; l++)
           for (m=0; m<=TONGSOTIEN/20000; m++)
           {
             if ((i*1000  + j*2000 + k*5000 + l*10000 + m*20000) == TONGSOTIEN)
                printf("\n%5ld - %5ld%5ld%5ld%5ld%5ld", ++count, i, j, k, l, m);
            soluong++;
            }
   printf("so luong = %ld", soluong);
   getch();
}