/* Check Disk */
#include <stdio.h>
#include <dos.h>

typedef unsigned char BYTE;
typedef unsigned WORD;

typedef struct tagdiskinfo {
  char signature;
  WORD skip;
  char vendor[8];
  WORD bytepersector;
  BYTE sectorpercluster;
  WORD reservedsectors;
  BYTE fatcopies;
  WORD rootentries;
  WORD totalsectors;
  BYTE media;
  WORD sectorperfat;
  WORD sectorpertrack;
  WORD heads;
  WORD hiddensectors;
  char loader [482];
} DISKINFO;

DISKINFO diskinfo;
char readbuffer[512];
char writebuffer[512];
int numbadsector;

void check(int disknum, int sector)
{
  int thu, ketqua;
  thu = 0;
  do {
    ketqua = absread(disknum, 1, sector, readbuffer);
  } while (ketqua != 0 && thu < 5);
  if (thu >= 5)
    numbadsector++;
}

void main(int argc, char *argv[])
{
  int disknum, i, x, y;

  if (argc < 2)
    printf("\nCach dung : CHKDSK <o dia>");
  else
  {
    disknum = toupper(argv[1][0]) - 'A';
    if (disknum > 1)
      printf("\nCHKDSK chi lam viec len dia mem");
    else
      if (absread(disknum, 1, 0, &diskinfo)!= 0)
        printf("Khong the doc boot record cua o %c", 'A' + disknum);
      else
      {
        printf("\n\n\nDang tien hanh kiem tra o dia %c\n", disknum+'A');
        x = wherex();
        y = wherey();
        numbadsector = 0;
        for (i=0; i<diskinfo.totalsectors; i++)
        {
          gotoxy(x, y);
          cprintf("%3.0f%%", (float)(i+1)*100/diskinfo.totalsectors);
          check(disknum, i);
        }
        if (numbadsector > 0)
          printf("Tong so bad sector = %d", numbadsector);
        printf("\nCHKDSK completed.");
      }
  }
  getch();
}