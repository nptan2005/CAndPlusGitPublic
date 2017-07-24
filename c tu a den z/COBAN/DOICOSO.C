/* Bai tap 2_9 - Doi so tu co so n sang gia tri so co so m */
#include <stdio.h>
#include <string.h>

char *doics(char *number, int n, int m)
{
  static char ketqua[17];
  char chuso[16] = "0123456789ABCDEF";
  int i = 0, giatri = 0, len;

  len = strlen(number);
  while(i<len) {
    giatri = giatri * n + (strchr(chuso, number[i]) - &chuso);
    i++;
  }
  i=16;
  ketqua[17] = 0;
  do {
    ketqua[i] = chuso[giatri % m];
    giatri /= m;
    i--;
  } while (giatri > 0);
  return (ketqua + i  + 1);
}

void main()
{
  unsigned n, m;
  char number[17], *ketqua;

  do {
    printf("\nNhap gia tri N (2 - 16) : ");
    scanf("%d", &n);
  } while (n<2 || n>16);
  getchar();
  printf("Gia tri thuoc he %d : ", n);
  gets(number);
  do {
    printf("Nhap gia tri M (2 - 16) : ");
    scanf("%d", &m);
  } while (m<2 || m>16);
  printf("Gia tri %s o co so %u co gia tri o co so %u la : ", number, n, m);
  ketqua = doics(number, n, m);
  puts(ketqua);
  getch();
}