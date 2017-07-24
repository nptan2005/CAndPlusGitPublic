#include <stdio.h>

void main()
{
  int num, tram, chuc, donvi, count = 0;

  for (num = 100; num < 1000; num++)
  {
    donvi = num % 10;
    chuc  = (num / 10) % 10;
    tram  = num / 100;
    if (donvi * donvi * donvi + chuc * chuc * chuc + tram * tram * tram == num)
    {
       printf("\nSo %d thoa man", num);
       count++;
    }
  }
  printf("\nTong cong co %d so thoa man yeu cau", count);
}