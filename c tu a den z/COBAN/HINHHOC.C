/* Bai tap 1_15 - Tinh dien tich cac hinh hoc */
#include <stdio.h>
#include <conio.h>
#include <math.h>

int menu()
{
  int c;
  printf("\n----- Menu -----");
  printf("\n1. Hinh tam giac");
  printf("\n2. Hinh tron");
  printf("\n3. Hinh vuong");
  printf("\n4. Hinh chu nhat");
  printf("\n0. Thoat");
  printf("\n----------------");
  printf("\nChon muc : ");
  do {
    c = getch();
  } while (c>'4' || c<'0');
  putc(c, stdout);
  return c -'0';
}

void hinhtamgiac()
{
  int a, b, c;
  float p;

  printf("\n\nNhap vao ba canh tam giac : ");
  scanf("%d%d%d", &a, &b, &c);
  printf("\nChu vi tam giac = %d", a+b+c);
  p = (float)(a + b + c)/2;
  printf("\nDien tich tam giac = %lf", sqrt(p*(p-a)*(p-b)*(p-c)));
  getch();
}

void hinhtron()
{
  int r;

  printf("\n\nNhap vao ban kinh hinh tron : ");
  scanf("%d", &r);
  printf("\nChu vi hinh tron = %f", 2 * M_PI * r);
  printf("\nDien tich hinh tron = %f", M_PI * r * r);
  getch();
}

void hinhvuong()
{
  int a;

  printf("\n\nNhap vao canh hinh vuong : ");
  scanf("%d", &a);
  printf("\nChu vi hinh tron = %d", 4 * a);
  printf("\nDien tich hinh vuong = %d", a * a);
  getch();
}

void hinhchunhat()
{
  int a, b;

  printf("\n\nNhap vao cac canh hinh chu nhat : ");
  scanf("%d%d", &a, &b);
  printf("\nChu vi hinh chu nhat = %d", 2 * (a+b));
  printf("\nDien tich hinh chu nhat = %d", b * a);
  getch();
}

void main()
{
  int chon;
  do {
    chon = menu();
    switch(chon)
    {
      case 1 : hinhtamgiac();
               break;
      case 2 : hinhtron();
               break;
      case 3 : hinhvuong();
               break;
      case 4 : hinhchunhat();
               break;
    }
  } while (chon != 0);
}