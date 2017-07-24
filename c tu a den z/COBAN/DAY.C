/* Bai tap 1_100 - Tinh thu cua ngay */
#include <stdio.h>

struct date
{
   int     month;
   int    day;
   int    year;
} date_1;

long int funct1 (int y,int m)
{
  long int result;
     if ( m <= 2 )
       y -= 1;
     result = y;
     return (result);
}

long int funct2 (int m)
    {
     long int result;
     if ( m <= 2 )
       result = m + 13;
     else
       result = m + 1;
       return(result);
    }

long int day_count (int m, int d, int y)
    {
     long int number;
     number = 1461 *  funct1(y,m) / 4 + 153 * funct2(m) / 5 + d;

     return (number);
    }

void main ()
{
    long int number_of_days1;
    int day_of_week;

    printf ("Nhap vao mot ngay (dd mm yyyy), vd  12 03 1999  \n");
    scanf ("%d %d %d", &date_1.day, &date_1.month, &date_1.year);
    number_of_days1 = day_count (date_1.month, date_1.day, date_1.year);
    printf ("\nNgay la : " );

    day_of_week = (number_of_days1 - 621049) % 7;
    switch (day_of_week)
      {
        case 0 :
            printf ("Chu Nhat,");
            break;
        case 1 :
            printf ("Thu Hai,");
            break;
        case 2 :
            printf ("Thu Ba,");
            break;
        case 3 :
            printf ("Thu Tu,");
            break;
        case 4 :
            printf ("Thu Nam,");
            break;
        case 5 :
            printf ("Thu Sau,");
            break;
        case 6 :
            printf ("Thu Bay,");
            break;
      }
  getch();
}
