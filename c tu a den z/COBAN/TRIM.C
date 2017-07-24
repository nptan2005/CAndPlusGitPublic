/* Bai tap 9_3 - Viet thu tuc trim de loai bo cac khoang trong thua trong chuoi */
#include <stdio.h>
#include <string.h>
#include <conio.h>
#pragma warn -pia

char *trim(char *chuoi)
{
   char *p;
   while (p = strstr(chuoi, "  "))
     memmove(p, p+1, strlen(chuoi) - (p - chuoi));
   if (chuoi[0] == ' ')
     memmove(chuoi, chuoi+1, strlen(chuoi) - 1);
   if (chuoi[strlen(chuoi)-1] == ' ')
     chuoi[strlen(chuoi)-1] = 0;
   return chuoi;
}

void main()
{
   char chuoi[125];

   printf("\nNhap chuoi mau : ");
   textattr(0x1e);
   gets(chuoi);

   trim(chuoi);
   printf("\nChuoi sau khi da trim : ");
   textattr(0x1e);
   cputs(chuoi);
   getch();
}