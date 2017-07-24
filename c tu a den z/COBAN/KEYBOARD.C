/* Cho biet ma ban phim */
#include <stdio.h>

void main()
{
  char c;
  printf("\nNhap vao mot phim muon biet ma cua no. ESC de thoat\n");
  do {
    c = getch();
    if (c == 0)
    {
      c = getch();
      printf("\nMa mo rong : %d", c);
    }
    else
      printf("\nMa thuong : %d", c);
  } while (c != 27);
}