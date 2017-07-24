#include <stdio.h>

void main()
{
  int a[10], i, maxstart, maxend, maxtotal, tmpstart, tmpend, tmptotal;

  printf("\nNhap vao 10 phan tu nguyen cua day :");
  for (i=0; i<10; i++)
    scanf("%d", &a[i]);
  printf("Day da cho :\n");
  for (i=0; i<10; i++)
    printf("%6d", a[i]);

  maxstart = maxend = tmpstart = tmpend = 0;
  maxtotal = tmptotal = a[0];
  for (i=1; i< 10; i++)
  {
     if (a[i] < a[tmpend])
     {
       if (maxtotal < tmptotal)
       {
         maxstart = tmpstart;
         maxend = tmpend;
         maxtotal = tmptotal;
       }
       tmpstart = tmpend = i;
       tmptotal = a[i];
     }
     else
     {
       tmptotal += a[i];
       tmpend++;
     }
  }
  if (maxtotal < tmptotal)
  {
     maxstart = tmpstart;
     maxend = tmpend;
  }
  printf("\nDay tang co tong nhieu nhat la : \n");
  for (i=maxstart; i<=maxend; i++)
    printf("%6d", a[i]);
  getch();
}