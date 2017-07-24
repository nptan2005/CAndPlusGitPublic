/* Bai tap 1_74 - Luu noi dung man hinh vao tap tin SCREEN.DAT */
#include <stdio.h>
#include <mem.h>
#include <dos.h>

void main()
{
   char far *video;
   int i;
   FILE *fp;

   video = (char far*)MK_FP(0xB800, 0);
   if ((fp = fopen("SCREEN.DAT", "w+b")) == NULL)
     printf("\nKhong the tao tap tin SCREEN.DAT");
   else
   {
     i = 0;
     for (i=0; i<4000; i++)
       fputc(video[i], fp);
     fclose(fp);
     printf("\nCong viec hoan tat");
   }
   getch();
}