/* Bai tap 9_1 - Dem so lan xuat hien cac ky tu trong chuoi */
#include <stdio.h>
#include <ctype.h>

void main()
{
  char chuoi[80];
  int i = 0, count = 0;

  printf("\nNhap vao mot chuoi bat ky : ");
  gets(chuoi);

  while (chuoi[i] != 0)
  {
    if (isalpha(chuoi[i++]))
      count++;
  }

  printf("So ky tu trong chuoi = %d", count);
  getch();
}