/* Bai tap 1_91 - The hien cac gia tri bit cua so */
#include <stdio.h>

void main()
{
  unsigned int mang[24], i;
  int bit[16], k, index;
  printf("\nNhap vao 23 gia tri nguyen : ");
  for (i=0; i<23; i++)
    scanf("%d",&mang[i]);
  printf("       FEDCBA9876543210");
  for (i=0; i<23; i++)
  {
     k = mang[i];
     for (index = 0; index < 16; index++)
       bit[index] = 0;
     index = 15;
     while (k)
     {
       bit[index--] = k%2;
       k /= 2;
     }
     printf("\n%5d  ",mang[i]);
     for (index=0; index<16; index++)
       if (bit[index] == 1)
         printf("*");
       else
         printf("-");
  }
  getch();
}