/* Bai tap 4_1 - Giai phuong trinh bac hai AXý + BX + C = 0 */
#include <stdio.h>
#include <math.h>

void main()
{
  float a, b, c, delta;

  printf("\nGiai phuong trinh bac hai AXý + BX + C = 0");
  printf("\nCho biet ba he so A B C : ");
  scanf("%f%f%f", &a, &b, &c);

  delta = b * b - 4 * a * c;
  if (delta<0)
    printf("Phuong trinh vo nghiem");
  else if (delta == 0)
      printf("Phuong trinh co nghiem kep x1 = x2 = %f", -b/(2*a));
  else
  {
    printf("Phuong trinh co hai nghiem phan biet\nx1 = %f", (-b + sqrt(delta))/(2*a));
    printf("\nx2 = %f", (-b - sqrt(delta))/(2*a));
  }
  getch();
}