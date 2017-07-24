/* Bai tap 9_5 - Tim so tu trong chuoi */
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
   int i = 0, count = 0;

   printf("\nNhap chuoi mau : ");
   textattr(0x1e);
   gets(chuoi);

   trim(chuoi);
   if (strlen(chuoi))
   {
     while(chuoi[i] != 0)
       if (chuoi[i++] == ' ')
         count++;
     count++;
   }
   printf("\nSo tu co trong chuoi : %d", count);
   getch();
}