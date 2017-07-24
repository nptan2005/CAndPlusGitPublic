/* Bat tap 4_39 - Giai ma FAT 12 */
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
BYTE fat[18*512];
long totalbyte;

int diskread(int start)
{
  union REGS regs;
  WORD tmp;

  tmp = _SP;
  regs.h.al = 0;
  regs.x.cx = 1;
  regs.x.dx = start;
  (BYTE *)regs.x.bx = sector;
  int86(0x25, &regs, &regs);
  _SP = tmp;
  return regs.x.ax;
}

int readFAT(int start, int end)
{
  union REGS regs;
  WORD tmp;

  tmp = _SP;
  regs.h.al = 0;
  regs.x.cx = end - start;
  regs.x.dx = start;
  (BYTE *)regs.x.bx = fat;
  int86(0x25, &regs, &regs);
  _SP = tmp;
  return regs.x.ax;
}

void inFAT(int byte)
{
  byte &= 0xfff;
  switch(byte)
  {
    case 0x000 : printf("NONE  "); break;
    case 0xff7 : printf("<BAD> "); break;
    case 0xff8 :
    case 0xff9 :
    case 0xffa :
    case 0xffb :
    case 0xffc :
    case 0xffd :
    case 0xffe :
    case 0xfff : printf("<EOF> "); break;
    default    : printf("%4d  ", byte); break;
  }
}

void writeFAT()
{
  int hang;
  long offset = 0;
  int byte1, byte2, byte3, i;
  do {
    clrscr();
    hang = 0;
    do {
      printf("\n");
      for (i=0; i<6; i++)
      {
        if (offset < totalbyte)
        {
          byte1 = fat[offset];
          byte2 = fat[offset+1];
          byte3 = fat[offset+2];
          offset += 3;
          byte1 += (byte2 << 8);
          byte1 &= 0xFFF;
          byte3  <<= 8;
          byte3 += byte2;
          byte3 >>= 4;
          inFAT(byte1);
          inFAT(byte3);
        }
        else
          break;
      }
      hang++;
    } while (hang < 23 && offset < totalbyte);
    printf("\nNhan phim bat ky de tiep tuc");
    getch();
  } while (offset < totalbyte);
}

void main()
{
  int start, end, i;

  diskread(0); /* Doc boot sector */
  memcpy(&diskinfo, &sector, sizeof(DISKINFO));
  start = 1; /* Sector sau boot sector */
  end   = diskinfo.reservedsectors + diskinfo.sectorperfat;
  totalbyte = (long)512 * (long)diskinfo.sectorperfat;
  readFAT(start, end);
  writeFAT();
}