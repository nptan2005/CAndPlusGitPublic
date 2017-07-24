/* Formak Disk */
#include <stdio.h>
#include <dos.h>
#include <ctype.h>

typedef unsigned char BYTE;
typedef unsigned int  WORD;

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
BYTE sector[512];
int disknum;

int diskread(int start)
{
  union REGS regs;
  WORD tmp;

  tmp = _SP;
  regs.h.al = disknum;
  regs.x.cx = 1;
  regs.x.dx = start;
  (BYTE *)regs.x.bx = sector;
  int86(0x25, &regs, &regs);
  _SP = tmp;
  return regs.x.ax;
}

int diskwrite(int start)
{
  union REGS regs;
  WORD tmp;

  tmp = _SP;
  regs.h.al = disknum;
  regs.x.cx = 1;
  regs.x.dx = start;
  (BYTE *)regs.x.bx = sector;
  int86(0x26, &regs, &regs);
  _SP = tmp;
  return regs.x.ax;
}

void main(int argc, char *argv[])
{
  int start, end, i;
  if (argc <2)
  {
    printf("\nCach dung : CFORMAT <O dia>");
    exit(1);
  }
  disknum = toupper(argv[1][0]) - 'A';
  if (disknum > 1)
  {
    printf("\nChuong trinh CFORMAT chi format dia mem :");
     exit(1);
  }
  diskread(0); /* Doc boot sector */
  memcpy(&diskinfo, &sector, sizeof(DISKINFO));
  start = 1; /* Sector sau boot sector */
  end   = diskinfo.reservedsectors +
          diskinfo.fatcopies * diskinfo.sectorperfat +
          diskinfo.rootentries / 16;
  memset(&sector, 0, 512);
  for (i=start; i<end; i++)
    diskwrite(i);
  printf("\nFormat hoan tat");
  getch();
}