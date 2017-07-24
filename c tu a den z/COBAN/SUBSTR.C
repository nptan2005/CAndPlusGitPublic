/* Bai tap 9_2 - Thu tuc tim chuoi con trong mot chuoi */
#include <stdio.h>

void main()
{
   char chuoi_lon [125], chuoi_con [10];
   int i, j;

   printf("\nNhap vao chuoi lon : ");
   gets(chuoi_lon);
   printf("\nNhap vao chuoi can tim : ");
   gets(chuoi_con);

   i = 0;
   while (chuoi_lon[i] != 0)
   {
     j = 0;
     while (chuoi_lon[i++] == chuoi_con[j++] &&
            chuoi_lon[i-1] != 0 && chuoi_con[j-1] != 0)
     ;
     if (chuoi_lon[i-1] != 0 && chuoi_con[j-1] == 0)
       printf("\nTim thay tai vi tri %d", i-j);
   }
   getch();
}