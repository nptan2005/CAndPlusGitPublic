#include <stdio.h>

unsigned USCLN (unsigned n, unsigned m)
{
  while (n != 0 && m != 0)
    if (n>m)
      n -= m;
    else
      m -= n;
  if (n == 0)
    return m;
  else
    return n;
}

unsigned BSCNN (unsigned n, unsigned m)
{
  return n * m / USCLN(n, m);
}

void main()
{
  unsigned n, m;

  printf("\nNhap hai vao so nguyen duong : ");
  scanf("%u%u", &n, &m);
  printf("\nUSCLN cua %u va %u = %u", n, m, USCLN(n,m));
  printf("\nBSCNN cua %u va %u = %u", n, m, BSCNN(n,m));
  getch();
}