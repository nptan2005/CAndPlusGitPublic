/* Bai tap 4_4 - Xem va dat ngay cho may */
#include <dos.h>

struct date datep;

int checkdate(char *s)
{
  char sday[3], smon[3], syear[5];
  int day, mon, year;
  if (s[2] != '-' || s[5] != '-')
    return 0; /* Khong dung khuon dang */
  sday[0] = s[0]; sday[1] = s[1]; sday[2] = 0;
  smon[0] = s[3]; smon[1] = s[4]; smon[2] = 0;
  syear[0] = s[6]; syear[1] = s[7]; syear[2] = s[8]; syear[3] = s[9]; syear[4] = 0;
  day = atoi(sday);
  mon = atoi(smon);
  year = atoi(syear);
  if (day == 0 || mon == 0 || year == 0)
    return 0;
  datep.da_day = day;
  datep.da_mon = mon;
  datep.da_year = year;
  setdate(&datep);
  return 1;
}

void main()
{
  char s[11];
  int OK;
  getdate(&datep);
  printf("\nHom nay la %02d-%02d-%04d", datep.da_day, datep.da_mon, datep.da_year);
  do {
    printf("\nNhap ngay moi (dd-mm-yyyy): ");
    gets(s);
    if (strlen(s) > 0)
    {
      if ((OK = checkdate(s)) == 0)
        printf("\nNgay khong hop le");
    }
    else
      break;
  } while (!OK);
}
