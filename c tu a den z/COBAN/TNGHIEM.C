/* Bai tap 1_48 - Chuong trinh trac nghiem don gian */
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX 100

typedef struct tagcauhoi {
  char *cauhoi, *traloi[4];
  int caudung;
} CAUHOI;

CAUHOI cautn[MAX];
int socau = 0;
int socaudung = 0;

char nhapcautraloi()
{
  char c;
  do {
    c = toupper(getch());
  } while (c <'A' || c>'D');
  textattr(2);
  cprintf("%c", c);
  return c - 'A';
}

void tracnghiem()
{
  int cauhientai= 0, i;
  char c;
  do {
    clrscr();
    textattr(1);
    cprintf("%s\n\r", cautn[cauhientai].cauhoi);
    textattr(14);
    for (i=0; i<4; i++)
      cprintf("\r%c. %s", i+'A', cautn[cauhientai].traloi[i]);
    textattr(15);
    cprintf("\n\r\n\rChon cau : ");
    c = nhapcautraloi();
    if (c == cautn[cauhientai].caudung)
    {
      cprintf("\n\rDung roi!");
      delay(500);
      socaudung ++;
    }
    cauhientai++;
  } while (cauhientai<socau);
}

void main()
{
  FILE *fp;
  int i, j;
  char tmp[255];

  if ((fp = fopen("TNGHIEM.DAT", "r")) == NULL)
    printf("\nKhong tim thay tap tin TNGHIEM.DAT");
  else
  {
    fscanf(fp, "%d%*c", &socau);
    for (i=0; i<socau; i++)
    {
      fgets(tmp, 255, fp);
      cautn[i].cauhoi = strdup(tmp);
      for (j=0; j<4; j++)
      {
        fgets(tmp, 255, fp);
        cautn[i].traloi[j] = strdup(tmp);
      }
      fscanf(fp, "%d%*c", &cautn[i].caudung);
    }
    fclose(fp);
    tracnghiem();
    textattr(14);
    cprintf("\n\r\n\rKet qua : ");
    textattr(2);
    cprintf("%.2f", (float)socaudung*10 / socau);
  }
  getch();
}