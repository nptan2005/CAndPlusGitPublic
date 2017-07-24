#include <stdio.h>
#include <math.h>

double giaithua(double n)
{
   double i, ketqua=1;

   for (i=2; i<=n; i++)
     ketqua *= i;
   return ketqua;
}

void main()
{
  double ketqua, epsilon, x, n = 1;

  printf("\nNhap gia tri x (radian) : ");
  scanf("%lf", &x);
  ketqua = x;
  do {
    epsilon = pow(x, 2*n+1) / giaithua(2*n+1);
    ketqua += pow(-1, n) * epsilon;
    n++;
  } while (fabs(epsilon) > 0.0001);

  printf("\nKet qua tinh theo cong thuc = %10.8lf", ketqua);
  printf("\nKet qua tinh theo ham = %10.8lf", sin(x));
  getch();
}