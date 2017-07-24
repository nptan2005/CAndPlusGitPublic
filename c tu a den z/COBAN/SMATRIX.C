/* Bai tap 1_88 - Dien gia tri cho mot mang vuong theo chieu kim dong ho */
#include <stdio.h>

void main()
{
  int n, w, hang, cot, chanhangtang, chanhanggiam, chancottang, chancotgiam;
  int matran[12][12], tang, giam;

  printf("\n\nChuong trinh in ma tran dac biet.");
  do {
    printf("\nNhap kich thuoc cua ma tran (3 <= n <= 12) : ");
    scanf("%d%*c",&n);
  } while (! (n >=3 && n<=12) );
  hang = cot = 0;
  chanhangtang = chancottang = n-1;
  chanhanggiam = chancotgiam = 0;
  /*
     tang co 4 gia tri :
       tang = 0 -> tang cot
       tang = 1 -> tang hang
       tang = 2 -> giam cot
       tang = 3 -> giam cot
  */
  tang = 0;
  for (w=0; w<n*n; w++)
  {
     matran[hang][cot]= w + 1;
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
  for (hang=0; hang < n; hang++)
  {
    printf("\n");
    for (cot=0; cot < n; cot++)
      printf("%4d", matran[hang][cot]);
  }
  getch();
}