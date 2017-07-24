/* Bai tap  - CHung minh dang thuc An Casi*/
#include <stdio.h>

unsigned long vetrai(unsigned long n)
{
  unsigned long tmp=0, i;
  for (i=1; i<=n; i++)
    tmp += i*i*i*i;
  return tmp;
}

unsigned long vephai(unsigned long n)
{
  unsigned long tmp;
  tmp = (long)6*n*n*n*n*n + (long)15*n*n*n*n + (long)10*n*n*n - n;
  tmp = tmp / (long)30 ;
  return tmp;
}

void main()
{
  unsigned long tong1, tong2, n;

  for (n=1; n<=50; n++)
  {
    tong1 = vetrai(n);
    tong2 = vephai(n);
    if (tong1 == tong2)
    {
      printf("\nSo %d thoa man dang thuc An Casi. ", n);
      printf("Tong1 = %ld - Tong2 = %ld", tong1, tong2);
    }
    else
    {
      printf("\nSo %d khong thoa man dang thuc An Casi. ", n);
      printf("Tong1 = %ld - Tong2 = %ld", tong1, tong2);
    }
  }
  getch();
}