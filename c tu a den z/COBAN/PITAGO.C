/* Tim nhung gia tri nguyen x, y, z thoa xý + yý = zý */
#include <math.h>

void main()
{
  long x, y, z, count = 0;

  for (x=1; x<100; x++)
   for (y=1; y<100; y++)
   {
    z = sqrt(x*x+y*y);
    if (z*z == x*x + y*y)
    {
      printf("\n%6ld %6ld %6ld", x, y, z);
      count++;
    }
  }
  printf("\nTong cong co %ld cap so thoa man.", count);
  getch();
}