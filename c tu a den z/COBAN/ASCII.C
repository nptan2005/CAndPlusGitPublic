/* Bai tap 5_4 - Bang ma ASCII */
#include <stdio.h>
#include <conio.h>

void main()
{
  int i, j;

  clrscr();
  printf("    ");
  for (j=0; j<16; j++)
    printf("%3d", j);
  for (i=2; i<16; i++)
    for (j=0; j<16; j++)
    {
       if (j == 0)
         printf("\n%2d  ", i);
       printf("  %c", i*16+j);
    }
  getch();
}