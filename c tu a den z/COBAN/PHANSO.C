/* Phan so */
#include <stdio.h>

int USCLN(int a, int b)
{
  a = abs(a);
  b = abs(b);
  while (a != 0 && b != 0)
    if (a > b)
      a -= b;
    else
      b -= a;
  if (a == 0)
    return b;
  else
    return a;
}

int BSCNN(int a, int b)
{
   return a * b / USCLN(a, b);
}

typedef struct tagphanso {
  int tuso, mauso;
} PHANSO;

PHANSO uocluoc(PHANSO a)
{
  PHANSO c;
  c.tuso = a.tuso / USCLN(a.tuso, a.mauso);
  c.mauso = a.mauso / USCLN(a.tuso, a.mauso);
  return c;
}

PHANSO cong(PHANSO a, PHANSO b)
{
  PHANSO c;
  c.tuso = a.tuso * b.mauso + a.mauso * b.tuso;
  c.mauso = a.mauso * b.mauso;
  c = uocluoc(c);
  return c;
}

PHANSO tru(PHANSO a, PHANSO b)
{
  PHANSO c;
  c.tuso = a.tuso * b.mauso - a.mauso * b.tuso;
  c.mauso = a.mauso * b.mauso;
  c = uocluoc(c);
  return c;
}

PHANSO nhan(PHANSO a, PHANSO b)
{
  PHANSO c;
  c.tuso = a.tuso * b.tuso;
  c.mauso = a.mauso * b.mauso;
  c = uocluoc(c);
  return c;
}

PHANSO chia(PHANSO a, PHANSO b)
{
  PHANSO c;
  c.tuso = a.tuso * b.mauso;
  c.mauso = a.mauso * b.tuso;
  c = uocluoc(c);
  return c;
}

void print(PHANSO a)
{
  printf("%d/%d", a.tuso, a.mauso);
}

void main()
{
  PHANSO a, b, c;

  printf("\nNhap phan so a : ");
  scanf("%d%d", &a.tuso, &a.mauso);
  printf("\nNhap phan so b : ");
  scanf("%d%d", &b.tuso, &b.mauso);

  printf("\nToi gian a ta duoc : ");
  a = uocluoc(a);
  print(a);
  printf("\nToi gian b ta duoc : ");
  b = uocluoc(b);
  print(b);
  printf("\nTong cua hai phan so = ");
  c = cong(a, b);
  print(c);
  printf("\nHieu cua hai phan so = ");
  c = tru(a, b);
  print(c);
  printf("\nTich cua hai phan so = ");
  c = nhan(a, b);
  print(c);
  printf("\nThuong cua hai phan so = ");
  c = chia(a, b);
  print(c);
  getch();
}
