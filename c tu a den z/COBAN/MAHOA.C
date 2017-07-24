/* Ma hoa dung XOR */
#include <stdio.h>

void main()
{
  char chuoi[50], khoa;
  int i, len;

  printf("\nNhap vao chuoi can ma hoa : ");
  gets(chuoi);
  printf("Cho biet khoa : ");
  khoa = getch();
  len = strlen(chuoi);
  for (i=0; i<len; i++)
    chuoi[i] ^= khoa;
  printf("\nChuoi da duoc ma hoa thanh : %s", chuoi);
  printf("\nNhan phim bat ky de giai ma.");
  getch();
  for (i=0; i<len; i++)
    chuoi[i] ^= khoa;
  printf("\nChuoi da duoc giai ma : %s", chuoi);

  getch();
}