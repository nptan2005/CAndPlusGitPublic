/* Bai tap 1_31 - Tinh can bac hai theo phep lap Newton */
#include <stdio.h>
#include <math.h>

void main()
{
  double a, xn, ketqua;

  printf("\nNhap vao so muon tinh can bac hai : ");
  scanf("%lf", &a);
  xn = (a+1)/2;
  do {
    ketqua = xn;
    xn = 0.5 * (xn + a/xn);
  } while (fabs(xn-ketqua) > 0.0001);
  printf("\nKet qua = %lf", xn);
  getch();
}