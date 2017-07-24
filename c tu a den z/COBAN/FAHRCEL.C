#include <stdio.h>

void main()
{
  double fahrenheit, celsius;

  printf("\nNhap gia tri do Fahrenheit : ");
  scanf("%lf", &fahrenheit);
  if (fahrenheit != 32.0)
  {
    celsius = 5.0 * (fahrenheit-32.0) / 9.0 ;
    printf("Do Celsius tuong ung = %5.2lf", celsius);
  }
  getch();
}