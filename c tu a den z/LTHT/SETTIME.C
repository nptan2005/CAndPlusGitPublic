/* Bai tap 4_4 - Xem va dat ngay cho may */
#include <dos.h>

struct time timep;

int checktime(char *s)
{
  char shour[3], smin[3], ssec[3];
  if (s[2] != ':' || s[5] != ':')
    return 0; /* Khong dung khuon dang */
  shour[0] = s[0]; shour[1] = s[1]; shour[2] = 0;
  smin[0] = s[3]; smin[1] = s[4]; smin[2] = 0;
  ssec[0] = s[6]; ssec[1] = s[7]; ssec[2] = 0;
  timep.ti_hour = atoi(shour);
  timep.ti_min = atoi(smin);
  timep.ti_sec = atoi(ssec);
  settime(&timep);
  return 1;
}

void main()
{
  char s[11];
  int OK;
  gettime(&timep);
  printf("\nBay gio la %02d:%02d:%02d", timep.ti_hour, timep.ti_min, timep.ti_sec);
  do {
    printf("\nNhap gio moi (hh:mm:ss): ");
    gets(s);
    if (strlen(s) > 0)
    {
      if ((OK = checktime(s)) == 0)
        printf("\nGio khong hop le");
    }
    else
      break;
  } while (!OK);
}
