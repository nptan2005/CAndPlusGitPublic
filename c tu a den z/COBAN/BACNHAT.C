/* Bai tap 4_1 - Giai phuong trinh bac nhat AX + B = 0 */
#include <stdio.h>

void main()
{
  float a, b;

  printf("\nGiai phuong trinh bac nhat AX + B = 0");
  printf("\nCho biet ba he so A B : ");
  scanf("%f%f", &a, &b);

  if (a==0)
    if (b!=0)
      printf("Phuong trinh vo nghiem");
    else
      printf("Phuong trinh co nghiem khong xac dinh");
  else
    printf("Dap so cua phuong trinh tren = %f", -b/a);
  getch();
}