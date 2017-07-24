/* Quick format */
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
char buffer[512];

void main(int argc, char *argv[])
{
  int disknum, total, i;

  if (argc < 2)
    printf("\nCach dung : QFORMAT <o dia>");
  else
  {
    disknum = toupper(argv[1][0]) - 'A';
    if (disknum > 1)
      printf("\nQFORMAT chi lam viec len dia mem");
    else
      if (absread(disknum, 1, 0, &diskinfo)!= 0)
        printf("Khong the doc boot record cua o %c", 'A' + disknum);
      else
      {
        total = diskinfo.fatcopies * diskinfo.sectorperfat +
                diskinfo.rootentries / 32;
        memset(buffer, 0, 512);
        for (i=0; i<total; i++)
          abswrite(disknum, 1, 1+i, &buffer);
        printf("\nKet thuc QFORMAT.");
      }
  }
  getch();
}