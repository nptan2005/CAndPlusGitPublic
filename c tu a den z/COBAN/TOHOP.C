/* Bai tap 3_2 - Ham tinh to hop chap K cua N */
#include <stdio.h>

unsigned long giaithua(int n)
{
   unsigned long ketqua = 1;
   int i;

   for (i=2; i<=n; i++)
     ketqua *= i;

   return ketqua;
}

unsigned long to_hop_chap(int k, int n)
{
   return giaithua(n) / (giaithua(k) * giaithua(n-k));
}

void main()
{
  int n, k;

  printf("\nNhap vao gia tri N va K : ");
  scanf("%d%d", &n, &k);

  printf("Top hop chap %d cua %d = %lu", k, n, to_hop_chap(k, n));
  getch();
}