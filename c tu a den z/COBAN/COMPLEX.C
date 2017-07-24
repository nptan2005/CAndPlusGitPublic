/* Cau truc va cac ham thao tac len so phuc */
#include <math.h>

typedef struct tagcomplex {
  float thuc, ao;
} complex;

complex tong(complex a, complex b)
{
  complex c;
  c.thuc = a.thuc + b.thuc;
  c.ao   = a.ao + b.ao;
  return c;
}

complex hieu(complex a, complex b)
{
  complex c;
  c.thuc = a.thuc - b.thuc;
  c.ao   = a.ao - b.ao;
  return c;
}

complex tich(complex a, complex b)
{
  complex c;
  c.thuc = a.thuc*b.thuc - a.ao*b.ao;
  c.ao   = a.thuc*b.ao + a.ao*b.thuc;
  return c;
}

complex thuong(complex a, complex b)
{
  complex c;
  float tongbp;
  tongbp = b.thuc*b.thuc + b.ao*b.ao;
  c.thuc = (a.thuc*a.ao + b.thuc*b.ao)/tongbp;
  c.ao   = (a.ao*b.thuc - a.thuc*b.ao)/tongbp;
  return c;
}

float argument(complex a)
{
  return acos(a.thuc/sqrt(a.thuc*a.thuc + a.ao*a.ao));
}

float modul(complex a)
{
  return sqrt(a.thuc*a.thuc + a.ao*a.ao);
}

void print_complex(complex a)
{
  printf("%.2f + %.2fi", a.thuc, a.ao);
}

void main()
{
  complex a, b, c;
  printf("\nNhap he so thuc va phuc cua A : ");
  scanf("%f%f", &a.thuc, &a.ao);
  printf("\nNhap he so thuc va phuc cua B : ");
  scanf("%f%f", &b.thuc, &b.ao);
  printf("\nSo phuc A = ");
  print_complex(a);
  printf("\nSo phuc B = ");
  print_complex(b);
  printf("\nTong cua chung = ");
  c = tong(a, b);
  print_complex(c);
  printf("\nHieu cua chung = ");
  c = hieu(a, b);
  print_complex(c);
  printf("\nTich cua chung = ");
  c = tich(a, b);
  print_complex(c);
  printf("\nThuong cua chung = ");
  c = thuong(a, b);
  print_complex(c);
  printf("\nArgument cua a = %f", argument(a));
  printf("\nModul cua a = %f", modul(a));
  getch();
}