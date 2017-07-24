/* Tong hai so chi gio */

void main()
{
  int gio1, phut1, giay1, gio2, phut2, giay2, gio3 = 0, phut3 = 0, giay3;

  printf("\nNhap vao gia tri chi gio thu nhat (hh:mm:gg): ");
  scanf("%d:%d:%d", &gio1, &phut1, &giay1);
  printf("\nNhap vao gia tri chi gio thu hai (hh:mm:gg): ");
  scanf("%d:%d:%d", &gio2, &phut2, &giay2);
  giay3 = giay1 + giay2;
  if (giay3 >=60)
  {
    giay3 %=60;
    phut3 = 1;
  }
  phut3 += phut1 + phut2;
  if (phut3 >=60)
  {
    phut3 %=60;
    gio3 = 1;
  }
  gio3 += gio1 + gio2;
  gio3 %= 24;
  printf("\nTong hai gia tri gio tren = %2d:%2d:%2d", gio3, phut3, giay3);
  getch();
}