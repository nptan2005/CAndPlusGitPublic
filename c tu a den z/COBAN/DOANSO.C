/* Doan so */
#include <stdio.h>

void main()
{
  int n, k = 128, i = 0, solan = 0;
  char c;

  printf("\nBan hay nghi mot so trong dau. So do phai nho hon 100.");
  delay(1000);
  printf("Xong chua! Roi ban hay tra loi nhung cau hoi sau day cua toi.");
  printf("\nToi se tim ra con so ma ban doan.");

  do {
    n = (k+i)/2;
    solan++;
    printf("\nLan doan thu %d.", solan);
    printf("\nCo phai so ban nghi la %d (Dung, Nho hon, Lon hon) ? ", n);
    do {
      c = toupper(getch());
    } while (c != 'D' && c != 'N' && c != 'L');
    switch (c)
    {
      case 'L' :  i = n;
                  break;
      case 'N' :  k = n;
                  break;
      case 'D' :  printf("\nTai khong?");
                  break;
    }
  } while (c != 'D');
  getch();
}