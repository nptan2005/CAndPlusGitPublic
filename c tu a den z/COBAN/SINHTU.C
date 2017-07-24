/* Bai tap 1_101 - Chuong trinh sinh tu ngau nhien */
#include <stdio.h>
#include <stdlib.h>

#define MAX 7
#define NUM 100

void main()
{
   int i, n, k;
   char s[MAX+1];

   randomize();
   printf("\n");
   for (n=0; n<NUM; n++)
   {
     s[0] = random('Z'-'A'+1) + 'A';
     k = random(MAX) + 1;
     for (i=1; i<k; i++)
      s[i] = random('z'-'a'+1) + 'a';
     s[i] = 0;
     printf("%-8s", s);
   }
   getch();
}