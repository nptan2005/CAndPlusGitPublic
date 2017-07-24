/* Bai tap 2_8 - In so Hex tuong ung voi mot so nguyen duong */
#include <stdio.h>

void main()
{
  unsigned number;
  char hex[] = "0123456789ABCDEF";

  printf("\nNhap vao mot gia tri nguyen duong 16 bit : ");
  scanf("%u", &number);
  printf("Gia tri Hex tuong ung = %c%c%c%c",
          hex[number/0x1000], hex[(number/0x100)%0x10],
          hex[(number/0x10)%0x10], hex[number%0x10]);
  getch();
}