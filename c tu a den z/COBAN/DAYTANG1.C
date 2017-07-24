#include <stdio.h>

void main()
{
  int a[10], i, maxstart, maxend, maxlen, tmpstart, tmpend, tmplen;

  printf("\nNhap vao 10 phan tu nguyen cua day :");
  for (i=0; i<10; i++)
    scanf("%d", &a[i]);
  printf("Day da cho :\n");
  for (i=0; i<10; i++)
    printf("%6d", a[i]);

  maxstart = maxend = tmpstart = tmpend = 0;
  maxlen = tmplen = 1;
  for (i=1; i< 10; i++)
  {
     if (a[i] < a[tmpend])
     {
       if (maxlen < tmplen)
       {
         maxstart = tmpstart;
         maxend = tmpend;
         maxlen = tmplen;
       }
       tmpstart = tmpend = i;
       tmplen = 1;
     }
     else
     {
       tmplen++;
       tmpend++;
     }
  }
  if (maxlen < tmplen)
  {
     maxstart = tmpstart;
     maxend = tmpend;
  }
  printf("\nDay tang co so phan tu nhieu nhat la : \n");
  for (i=maxstart; i<=maxend; i++)
    printf("%6d", a[i]);
  getch();
}