/* Bai tap 2_7 - In ra nam am lich tuong ung voi nam nhap vao */
#include <stdio.h>

void main()
{
  unsigned nam;
  char can[][5] = {"Giap", "At", "Binh", "Dinh", "Mau", "Ky",
                   "Canh", "Tan", "Nham", "Quy"};
  char chi[][5] = {"Ty", "Suu", "Dan", "Meo", "Thin", "Ty",
                   "Ngo", "Mao", "Than", "Dau", "Tuat", "Hoi"};

  printf("\nNhap nam can biet : ");
  scanf("%d", &nam);
  printf("Nam am lich cua %d la %s %s", nam, can[(nam+6)%10], chi[(nam+8)%12]);
  getch();
}