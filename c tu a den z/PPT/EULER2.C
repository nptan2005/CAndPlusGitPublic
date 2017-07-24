/* Giai gan dung he phuong trinh vi phan cap mot bang phuong phap Euler */
#include <stdio.h>
#include <math.h>

#define MAX 1000

double f1(double x, double y1, double y2, double y3)
{
  return (x + y1 + y2) * cos(2 * x + y3);
}

double f2(double x, double y1, double y2, double y3)
{
  return (x + y2 + y3) * cos(2 * x + y1);
}

double f3(double x, double y1, double y2, double y3)
{
  return (x + y1 + y3) * cos(2 * x + y2);
}

void main()
{
  double a, b, x, y[3][MAX], h, y1, y2, y3;
  int n, i;

  printf("\nGiai gan dung he phuong trinh vi phan cap mot bang phuong phap Euler.");
  printf("\nVi du giai he : y'= (x.y)/2");
  printf("\nGia tri diem dau a = ");
  scanf("%lf", &a);
  printf("Gia tri diem cuoi b = ");
  scanf("%lf", &b);
  printf("So diem chia n = ");
  scanf("%d", &n);
  printf("Gia tri ban dau Y[0][%6.2lf] = ");
  scanf("%lf", &y[0][0]);
  printf("Gia tri ban dau Y[1][%6.2lf] = ");
  scanf("%lf", &y[1][0]);
  printf("Gia tri ban dau Y[2][%6.2lf] = ");
  scanf("%lf", &y[2][0]);

  for (i=1; i<n; i++)
  {
    x = a + (i-1)*h;
    y1 = y[0][i-1];
    y2 = y[1][i-1];
    y3 = y[2][i-1];
    y[0][i] = y[0][i-1] + f1(x, y1, y2, y3);
    y[1][i] = y[1][i-1] + f2(x, y1, y2, y3);
    y[2][i] = y[2][i-1] + f3(x, y1, y2, y3);
  }

  printf("\nNghiem gan dung cua he phuong trinh");
  printf("\ntren doan [%6.2lf,%6.2lf]", a, b);
  printf("\nSo khoang chia n = %d", n);
  printf("\n       X             y1(x)'        y2(x)'        y3(x)'");
  for (i=0; i<n; i++)
  {
    printf("\n  %10.4lf    %10.4lf    %10.4lf    %10.4lf",
            a+i*h, y[0][i], y[1][i], y[2][i]);
  }
  getch();
}