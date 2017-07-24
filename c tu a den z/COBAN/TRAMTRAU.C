/* Bai tap 1_94 - Bai toan tram trau */
/* Giai bai toan co :
   Tram trau tram co
   Trau dung an nam
   Trau nam an ba
   Trau gia an mot
*/

#include <stdio.h>
#include <conio.h>

void main()
{
  int tdung, tnam, tgia, phuongan=0;

  for (tdung = 1; tdung <= 98; tdung ++)
    for (tnam = 1; tnam < 99 - tdung; tnam ++)
      for (tgia = 1; tgia < 99 - (tdung + tnam); tgia++)
        if ((tdung*5 + tnam*3 + tgia) == 100)
        {
           printf("\nTrau dung : %5d ; Trau nam : %5d ; Trau gia : %5d",
                  tdung, tnam, tgia);
           phuongan++;
        }
  printf("\nTong cong co %d phuong an.", phuongan);
  getch();
}