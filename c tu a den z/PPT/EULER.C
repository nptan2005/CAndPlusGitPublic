/* Giai gan dung phuong trinh vi phan cap mot bang phuong phap Euler */
#include <stdio.h>
#include <math.h>

#define MAX 1000

double f(double x, double y)
{
  return x * y / 2.0;
}

void main()
{
  double a, b, x[MAX], y[MAX], h;
  int n, i;

  printf("\nGiai gan dung phuong trinh vi phan cap mot bang phuong phap Euler.");
  printf("\nVi du giai he : y'= (x.y)/2");
  printf("\nGia tri diem dau a = ");
  scanf("%lf", &a);
  printf("Gia tri diem cuoi b = ");
  scanf("%lf", &b);
  printf("So diem chia n = ");
  scanf("%d", &n);
  printf("Gia tri ban dau Y[%6.2lf] = ");
  scanf("%lf", &y[0]);

  x[0] = a;
  h = (b-a) / n;
  for (i=1; i<n; i++)
  {
    x[i] = x[i-1] + h;
    y[i] = y[i-1] + h*f(x[i-1], y[i-1]);
  }

  printf("\nNghiem gan dung cua phuong trinh y' = (x.y)/2");
  printf("\ntren doan [%6.2lf,%6.2lf]", a, b);
  printf("\nGia tri dau Y[%6.2lf] = %lf", a, y[0]);
  printf("\nSo khoang chia n = %d", n);
  printf("\n       X             Y             y(x)");
  for (i=0; i<n; i++)
    printf("\n  %10.4lf    %10.4lf    %10.4lf", x[i], y[i], f(x[i],y[i]));
  getch();
}