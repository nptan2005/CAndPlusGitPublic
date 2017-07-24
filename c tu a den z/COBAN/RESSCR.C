/* Bai tap 1_75 - Lay lai noi dung man hinh tu tap tin SCREEN.DAT */
#include <stdio.h>
#include <mem.h>
#include <dos.h>

void main()
{
   char far *video;
   int i;
   FILE *fp;

   video = (char far*)MK_FP(0xB800, 0);
   if ((fp = fopen("SCREEN.DAT", "r+b")) == NULL)
     printf("\nKhong the tao tap tin SCREEN.DAT");
   else
   {
     for (i=0; i<4000; i++)
       video[i] = fgetc(fp);
     fclose(fp);
   }
   getch();
}