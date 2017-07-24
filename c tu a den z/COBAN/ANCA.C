/* Bai tap  - Bai toan Ancarokhi */
#include <stdio.h>

void main()
{
  int dai, rong;

  printf("\nBai toan Ancarokhi : Tim dien tich hinh chu nhat co chieu dai gap hai");
  printf("\nchieu rong va dien tich = chu vi");
  for (dai = 1; dai < 100; dai ++)
    for (rong=1; rong < 100; rong++)
      if (dai == 2 * rong && (dai + rong)*2 == dai*rong)
         printf("\nDai = %d; Rong = %d", dai, rong);
  getch();
}