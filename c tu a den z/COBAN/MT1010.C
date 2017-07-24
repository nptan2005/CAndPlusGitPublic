/* Bai tap 6_1 */
#include <conio.h>
#include <stdlib.h>

void main()
{
   int matran[10][10];
   int i, j, tonghang[10], tongcot[10], tongdcc=0, count=0;

   /* Khoi tao mang ngau nhien */
   randomize();
   for (i=0; i<10; i++)
     for (j=0; j<10; j++)
       matran[i][j] = random(10) + 1;

   /* Tinh tong cac hang */
   for (i=0; i<10; i++)
   {
     tonghang[i] = 0;
     for (j=0; j<10; j++)
       tonghang[i] += matran[i][j];
   }
   /* Tinh tong cac cot */
   for (j=0; j<10; j++)
   {
     tongcot[j] = 0;
     for (i=0; i<10; i++)
       tongcot[i] += matran[i][j];
   }
   /* Tinh tong duong cheo chinh */
   for (i=0; i<10; i++)
     tongdcc += matran[i][i];

   /* Dem so luong cac phan tu co gia tri nho hon 6 */
   for (i=0; i<10; i++)
     for (j=0; j<10; j++)
       if (matran[i][j] < 6)
	 count++;

   /* In ma tran va cac gia tri cua chung */
   clrscr();
   for (i=0; i<10; i++)
   {
     textcolor(WHITE);
     for (j=0; j<10; j++)
       cprintf ("%4d", matran[i][j]);
     textcolor(YELLOW);
     cprintf("%4d\n\r", tonghang[i]);
   }
   textcolor(LIGHTBLUE);
   for (j=0; j<10; j++)
     cprintf("%4d", tongcot[j]);
   textcolor(LIGHTGREEN);
   cprintf("%4d", tongdcc);
   textcolor(WHITE);
   cprintf("\n\r\n\rTong cac phan tu nho hon 6 = %3d", count);

   getch();
}