/* Bai tap 1_89 - In cac gia tri cua mot mang vuong theo chieu kim dong ho */
#include <stdio.h>
#include <conio.h>
#include <dos.h>

void main()
{
  int m, n, w, hang, cot, chanhangtang, chanhanggiam, chancottang, chancotgiam;
  int matran[12][12], tang, giam;

  printf("\n\nChuong trinh in ma tran dac biet.");
  do {
    printf("\nNhap so hang cua ma tran (3 <= n <= 12) : ");
    scanf("%d%*c",&n);
  } while (! (n >=3 && n<=12) );

  do {
    printf("\nNhap so cot cua ma tran (3 <= m <= 12) : ");
    scanf("%d%*c",&m);
  } while (! (m >=3 && m<=12) );

/* Nhap ma tran */
  for (hang=0; hang <n; hang++)
    for (cot=0; cot<m; cot++)
    {
      printf("phan tu [%02d][%02d] = ",hang,cot);
      scanf("%d",&matran[hang][cot]);
    }
  hang = cot = 0;
  chanhangtang = n-1;
  chancottang  = m-1;
  chanhanggiam = chancotgiam = 0;
  /*
     tang co 4 gia tri :
       tang = 0 -> tang cot
       tang = 1 -> tang hang
       tang = 2 -> giam cot
       tang = 3 -> giam cot
  */
  tang = 0;
  clrscr();
  for (w=0; w<n*m; w++)
  {
     gotoxy(10 + cot * 4, 3 + hang);
     printf("%4d",matran[hang][cot]);
     delay(200);
     switch(tang)
     {
       case 0 : if (cot < chancottang)
                   cot++;
                else
                {
                  tang++;     // Chuyen sang tang hang
                  chanhanggiam++;
                  hang++;
                }
                break;
       case 1 : if (hang < chanhangtang)
                   hang++;
                else
                {
                  tang++;     // Chuyen sang giam cot
                  chancottang--;
                  cot--;
                }
                break;
       case 2 : if (cot > chancotgiam)
                   cot--;
                else
                {
                  tang++;     // Chuyen sang giam hang
                  chanhangtang--;
                  hang--;
                }
                break;
       case 3 : if (hang > chanhanggiam)
                   hang--;
                else
                {
                  tang=0;     // Chuyen sang tang cot
                  chancotgiam++;
                  cot++;
                }
                break;
     }
  }
  getch();
}